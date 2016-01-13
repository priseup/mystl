#ifndef MYDEQUE_H
#define MYDEQUE_H

#include "myiterator.h"
#include "myalloc.h"
#include "myalgo.h"
#include "myconstruct.h"
#include <string.h>

namespace my
{

namespace
{
inline size_t buffsize(size_t n)
{
    return n < 512 ? size_t(512 / n) : size_t(1);
}
}

template <class T,
         class ref,
         class ptr>
struct dequeit : public Iterator<random_tag, T, ref, ptr>
{
    typedef dequeit self;
    typedef Iterator<random_tag, T, ref, ptr> BaseIt;
    typedef dequeit<T, T&, T*> iterator;
    typedef dequeit<T, const T&, const T*> const_iterator;

    typedef typename IteratorTraits<BaseIt>::pointer pointer;
    typedef typename IteratorTraits<BaseIt>::reference reference;
    typedef typename IteratorTraits<BaseIt>::difference_type difference_type;
    typedef typename IteratorTraits<BaseIt>::size_type size_type;

    dequeit() :
        m_map(NULL),
        m_cur(NULL),
        m_first(NULL),
        m_last(NULL) {}
    dequeit(const iterator &t) :
        m_map(t.m_map),
        m_cur(t.m_cur),
        m_first(t.m_first),
        m_last(t.m_last) {}
    dequeit(T* p, T** node):
        m_map(node),
        m_cur(p),
        m_first(*node),
        m_last(*node + buffer_size()) {}

    self& operator++()
    {
        ++m_cur;
        if (m_cur == m_last)
        {
            set_node(++m_map);
            m_cur = m_first;
        }
        return *this;
    }

    self operator++(int)
    {
        self t = *this;
        ++*this;
        return t;
    }

    self& operator--()
    {
        if (m_cur == m_first)
        {
            set_node(--m_map);
            m_cur = m_last;
        }
        --m_cur;
        return *this;
    }

    self operator--(int)
    {
        self t = *this;
        --*this;
        return t;
    }

    self operator-(int n)
    {
        self t = *this;
        t -= n;
        return t;
    }
    
    self operator+(int n)
    {
        self t = *this;
        t += n;
        return t;
    }

    self& operator-=(int n)
    {
        if (n > 0)
        {
            if (m_cur - m_first >= n)
                m_cur -= n;
            else
            {
                size_type old_distance = m_cur - m_first;
                n -= (old_distance + 1);
                size_type map_move = n / buffer_size() + 1;
                set_node(m_map - map_move);
                m_cur = m_last - 1 - n % buffer_size();
            }
        }
        else if (n < 0)
        {
            *this += -n;
        }

        return *this;
    }

    self& operator+=(int n)
    {
        if (n > 0)
        {
            if (m_last - m_cur > n)
                m_cur += n;
            else
            {
                size_type old_distance = m_last - m_cur;
                n -= old_distance;
                size_type map_move = n / buffer_size() + 1;
                set_node(m_map + map_move);
                m_cur = m_first + n % buffer_size();
            }
        }
        else if (n < 0)
        {
            *this -= -n;
        }
        return *this;
    }

    reference operator*()
    {
        return *m_cur;
    }

    reference operator*() const
    {
        return *m_cur;
    }

    reference operator[](size_type n)
    {
        return *(*this + n);
    }

    reference operator[](size_type n) const
    {
        return *(*this + n);
    }

    pointer operator->()
    {
        return m_cur;
    }

    pointer operator->() const
    {
        return m_cur;
    }

    difference_type operator-(const self& t) const
    {
        return difference_type((m_map - t.m_map - 1) * buffer_size())
                        + m_cur - m_first + t.m_last - t.m_cur;
    }

    bool operator==(const self& t) const
    {
        return m_cur == t.m_cur;
    }

    bool operator!=(const self& t) const
    {
        return !(*this == t);
    }

    bool operator>(const self& t) const
    {
        return m_map == t.m_map ?
                m_cur > t.m_cur : m_map > t.m_map;
    }

    bool operator>=(const self& t) const
    {
        return !(*this < t);
    }

    bool operator<(const self& t) const
    {
        return t > *this;
    }

    bool operator<=(const self& t) const
    {
        return !(*this > t);
    }

    void set_node(T** new_map)
    {
        m_map = new_map ;
        m_first = *m_map;
        m_last = m_first + buffer_size();
    }

    size_type buffer_size() const
    {
        return buffsize(sizeof (T));
    }

    T** m_map;
    T* m_cur;
    T* m_first;
    T* m_last;
};

template <class T, class Allocator = alloc_t<T> >
class deque
{
public:
    enum {MAPSIZE = 2};
    // types:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename AllocatorTraits<T*, Allocator>::allocator_type map_allocator_type;

    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

    typedef dequeit<T, reference, pointer>                   iterator;
    typedef dequeit<T, const_reference, const_pointer>       const_iterator;
    typedef my_reverse_iterator<iterator>          reverse_iterator;
    typedef my_reverse_iterator<const_iterator>    const_reverse_iterator;

    // construct/copy/destroy:
    deque() :
        m_mapsize(0),
        m_map(NULL) {}

    explicit deque(const allocator_type& a) :
        m_mapsize(0),
        m_map(NULL),
        m_node_alloc(a) {}

    explicit deque(size_type n)
    {
        deque_imple(n, T(), true_type());
    }
//    explicit deque(size_type n, const allocator_type& a); // C++14
    deque(size_type n, const value_type& v)
    {
        deque_imple(n, v, true_type());
    }
    
    deque(size_type n, const value_type& v, const allocator_type& a)
    {
        get_map_buffer_by_count(n, a);
        fill_aux(v);
    }
    template <class InputIterator>
    deque(InputIterator f, InputIterator l)
    {
        typedef typename IntegerTraits<InputIterator>::is_integer _C;
        deque_imple(f, l, _C());

    }
    template <class InputIterator>
    deque(InputIterator f, InputIterator l, const allocator_type& a)
    {
        size_type n = distance(f, l);
        get_map_buffer_by_count(n, a);

        fill_by_iterator(f, l);
   }

    deque(const deque& c)
    {
        get_map_buffer_by_count(c.size(), c.get_allocator());
        fill_by_iterator(c.begin(), c.end());
    }
//    deque(deque&& c)
//        (is_nothrow_move_constructible<allocator_type>::value);
//    deque(initializer_list<value_type> il, const Allocator& a = allocator_type());
    deque(const deque& c, const allocator_type& a)
    {
        get_map_buffer_by_count(c.size(), c.get_allocator());
        fill_by_iterator(c.begin(), c.end());
    }
//    deque(deque&& c, const allocator_type& a);
    ~deque()
    {
        deep_clear();
    }

    deque& operator=(const deque& c)
    {
        deep_clear();
        get_map_buffer_by_count(c.size(), c.get_allocator());
        fill_by_iterator(c.begin(), c.end());
    }
//    deque& operator=(deque&& c)
//        (
//             allocator_type::propagate_on_container_move_assignment::value &&
//             is_nothrow_move_assignable<allocator_type>::value);
//    deque& operator=(initializer_list<value_type> il);

    template <class InputIterator>
    void assign(InputIterator f, InputIterator l)
    {
        deep_clear();

        deque_imple(f, l, false_type());
    }
    void assign(size_type n, const value_type& v)
    {
        deep_clear();

        deque_imple(n, v, true_type());
    }
//    void assign(initializer_list<value_type> il);

    allocator_type get_allocator() const
    {
        return m_node_alloc;
    }

    // iterators:

    iterator       begin()
    {
        return m_begin;
    }
    const_iterator begin() const
    {
        return m_begin;
    }
    iterator       end()
    {
        return m_finish;
    }
    const_iterator end() const
    {
        return m_finish;
    }
    reverse_iterator       rbegin()
    {
        return reverse_iterator(m_finish);
    }
    const_reverse_iterator rbegin() const
    {
        return reverse_iterator(m_finish);
    }
    reverse_iterator       rend()
    {
        return reverse_iterator(m_begin);
    }
    const_reverse_iterator rend() const
    {
        return reverse_iterator(m_begin);
    }
    
    size_type size() const
    {
        return (size_type)(m_finish - m_begin);
    }
    size_type max_size() const 
    {
        return size_type(-1) / sizeof (T);
    }
    void resize(size_type n)
    {
        resize(n, T());
    }
    void resize(size_type n, const value_type& v)
    {
        if (size() < n)
        {
            erase(m_begin + n, m_finish);
        }
        else
        {
            size_type old_size = size();
            size_type new_map_size = n / buffer_size() + 1;
            if (new_map_size >= m_mapsize)
                map_realloc(new_map_size);

            size_type tmp = n - old_size;
            while (tmp--)
                push_back(v);
        }
    }

    void shrink_to_fit()
    {
    }

    bool empty() const
    {
        return m_begin.m_cur == m_finish.m_cur;
    }

    reference at(size_type i)
    {
        return *(m_begin + i);
    }
    const_reference at(size_type i) const
    {
        return *(m_begin + i);
    }
    reference front()
    {
        return *m_begin;
    }
    const_reference front() const
    {
        return *m_begin;
    }

    reference back()
    {
        return *(m_finish - 1);
    }
    const_reference back() const
    {
        return *(m_finish - 1);
    }

    // modifiers:
    void push_front(const value_type& x)
    {
        if (empty())
            initialize_empty_deque();

        if (is_map_realloc(true))
            map_realloc();

        if (is_first_buffer_full())
            alloc_buffer(true);

        --m_begin;
        construct(m_begin.m_cur, x);
    }

    // 不能调用insert_aux()函数，因为m_finish可能发生改变
    void push_back(const value_type& x)
    {
        if (empty())
            initialize_empty_deque();

        if (is_map_realloc(false))
            map_realloc();

        if (is_last_buffer_full())
            alloc_buffer(false);

        construct(m_finish.m_cur, x);
        ++m_finish;
    }
//    template <class... Args> void emplace_front(Args&&... args);
//    template <class... Args> void emplace_back(Args&&... args);
//    template <class... Args> iterator emplace(iterator p, Args&&... args);
    iterator insert(iterator p, const value_type& x)
    {
        if (p == m_begin)
        {
            push_front(x);
            return p;
        }

        return insert_aux(p, x);
    }

    iterator insert(iterator p)
    {
        return insert(p, T());
    }

//    iterator insert(iterator p, const value_type& v)
    void insert(iterator p, size_type n, const value_type& v)
    {
        while (n--)
            insert(p, v);
        
    }
    template <class InputIterator>
    void insert (iterator p, InputIterator f, InputIterator l)
    {
        my_reverse_iterator<InputIterator> rfirst(l);
        my_reverse_iterator<InputIterator> rlast(f);

        for (; rfirst != rlast; ++rfirst)
            insert(p, *rfirst);
    }
//    iterator insert(iterator p, initializer_list<value_type> il)
    void pop_front()
    {
        destroy(m_begin.m_cur);
        ++m_begin;

        if (m_begin.m_cur == m_begin.m_first)
            m_node_alloc.dealloc(*(m_begin.m_map-1));
    }
    void pop_back()
    {
        destroy(&*(--m_finish));
        if (m_finish.m_cur == m_finish.m_last - 1)
            m_node_alloc.dealloc(*(m_finish.m_map+1));
    }
    iterator erase(iterator p)
    {
        if (p == m_begin)
        {
            pop_front();
            return begin();
        }
        if (p == m_finish - 1)
        {
            pop_back();
            return end();
        }

        return erase_aux(p);
    }
    iterator erase_aux(iterator p)
    {
        destroy(&*p);
        for (iterator cur = p; cur < m_finish - 1; ++cur)
            *cur = *(cur + 1);
        --m_finish;
        if (m_finish.m_cur == m_finish.m_last - 1)
            m_node_alloc.dealloc(*(m_finish.m_map+1));
        return p;
    }
    iterator erase(iterator f, iterator l)
    {
        size_type n = distance(f, l);
        for (iterator cur = f; cur < m_finish - n; ++cur)
            *cur = *(cur + n);
        destroy(m_finish - n, m_finish);
        iterator new_finish = m_finish - n;
        iterator old_finish = m_finish;
        m_finish -= n;
        for (T** t = new_finish.m_map + 1; t < old_finish.m_map; ++t)
            m_node_alloc.dealloc(*t);
        if (new_finish.m_map != old_finish.m_map)
            m_node_alloc.dealloc(*old_finish.m_map);
        if (m_begin.m_map == m_finish.m_map)
            m_node_alloc.dealloc(*m_begin.m_map);

        return f;
    }
    void swap(deque& c)
    {
        swap(m_mapsize, c.m_mapsize);
        swap(m_map, c.m_map);
        swap(m_begin, c.m_begin);
        swap(m_finish, c.m_finish);
    }
    void clear() 
    {
        erase(begin(), end());
    }

    reference operator[](size_type n)
    {
        return m_begin[n];
    }
    const_reference operator[](size_type n) const
    {
        return m_begin[n];
    }
protected:
    template <class T1, class T2>
        void deque_imple(T1 t1, T2 t2, false_type)
        {
            size_type n = distance(t1, t2);
            get_map_buffer_by_count(n);

            fill_by_iterator(t1, t2);
        }
    template <class T1, class T2>
        void deque_imple(T1 t1, T2 t2, true_type)
        {
            get_map_buffer_by_count(t1);
            fill_aux(t2);
        }

    void deep_clear()
    {
        clear();
        m_map_alloc.dealloc(m_map);
        m_mapsize = 0;
    }

    template <class InputIterator>
    void fill_by_iterator(InputIterator f, InputIterator l)
    {
        for (iterator it = m_begin; f != l; ++f)
            *it++ = *f;
    }

    void get_map_buffer_by_count(size_type n, const allocator_type& a = allocator_type())
    {
        m_node_alloc = a;
        m_mapsize = MAPSIZE;
        while (m_mapsize <= n / buffer_size())
            m_mapsize *= 2;
        m_map = m_map_alloc.alloc(m_mapsize);
        size_type map_node_count = n / buffer_size() + 1;
        T** map_start = m_map + (m_mapsize - map_node_count) / 2;
        T** map_end = map_start + map_node_count;
        create_buffer(map_start, map_end);
        m_begin.set_node(map_start);
        m_finish.set_node(map_end - 1);
        m_begin.m_cur = m_begin.m_first;
        m_finish.m_cur = m_finish.m_first + n % buffer_size();    // m_finish.m_cur points to the position beyond the last element
    }

    size_type buffer_size() const
    {
        return buffsize(sizeof (T));
    }

    void create_buffer(T** first, T** last)
    {
        for (; first != last; ++first)
            *first = m_node_alloc.alloc(buffer_size());
    }

    void fill_aux(const T& x)
    {
        typedef typename TypeTraits<T>::is_pod_type is_pod_data;

        _fill_aux_imple(x, is_pod_data());
    }

    void _fill_aux_imple(const T& x, true_type)
    {
        for (T** map_cur = m_begin.m_map; map_cur < m_finish.m_map; ++map_cur)
            for (T* m_cur = *map_cur; m_cur < *map_cur + buffer_size(); ++m_cur)
                *m_cur = x;
        for (T* m_cur = m_finish.m_first; m_cur < m_finish.m_cur; ++m_cur)
            *m_cur = x;
    }
    void _fill_aux_imple(const T& x, false_type)
    {
        for (T** map_cur = m_begin.m_map; map_cur < m_finish.m_map; ++map_cur)
            for (T* m_cur = *map_cur; m_cur < *map_cur + buffer_size(); ++m_cur)
                *m_cur = x;
        for (T* m_cur = *m_finish; m_cur < m_finish.m_cur; ++m_cur)
            *m_cur = x;
    }

    bool is_map_begin()
    {
        return m_begin.m_map == m_map;
    }
    bool is_map_end()
    {
        return m_finish.m_map == m_map + m_mapsize - 1;
    }
    bool is_first_buffer_full()
    {
        return m_begin.m_cur == m_begin.m_first;
    }
    bool is_last_buffer_full()
    {
        return m_finish.m_cur == m_finish.m_last - 1;
    }

    // map_realloc is caused by front or back..
    bool is_map_realloc(bool is_front)
    {
        if (is_front)
            return is_map_begin() && is_first_buffer_full();
        else
            return is_map_end() && is_last_buffer_full();
    }

    void initialize_empty_deque()
    {
        m_mapsize ? m_mapsize : m_mapsize = MAPSIZE;
        m_map ? m_map : m_map = m_map_alloc.alloc(m_mapsize);
        T** map_start = m_map + (m_mapsize - 1) / 2 ;
        T** map_end = map_start + 1;
        create_buffer(map_start, map_end);
        m_begin.set_node(map_start);
        m_finish.set_node(map_end - 1);
        m_begin.m_cur = m_begin.m_first + buffer_size() / 2;
        m_finish.m_cur = m_finish.m_first + buffer_size() / 2;    // m_finish.m_cur points to the position beyond the last element
    }

    void map_realloc(size_type new_size = 2 * MAPSIZE) 
    {
        m_mapsize = new_size;
        size_type begin_distance = m_begin.m_cur - m_begin.m_first;
        size_type finish_distance = m_finish.m_cur - m_finish.m_first;
        T** pp = m_map_alloc.alloc(m_mapsize);
        size_type map_node_count = m_finish.m_map - m_begin.m_map + 1;
        T** new_begin = pp + (m_mapsize - map_node_count) / 2;
        T** new_end = new_begin + map_node_count;
        memcpy(new_begin, m_begin.m_map, map_node_count*sizeof(T**));

        m_begin.set_node(new_begin);
        m_finish.set_node(new_end - 1);
        m_begin.m_cur = m_begin.m_first + begin_distance;
        m_finish.m_cur = m_finish.m_first + finish_distance;

        m_map_alloc.dealloc(m_map);
        m_map = pp;
    }

    // bool parameter: indicates whether front or back should alloce the buffer
    // true: the front should do the alloc 
    // false: the back do it
    void alloc_buffer(bool is_front)
    {
        if (is_front)
        {
            *(m_begin.m_map - 1) = m_node_alloc.alloc(buffer_size());
        }
        else
        {
            *(m_finish.m_map + 1) = m_node_alloc.alloc(buffer_size());
        }
    }


    iterator insert_aux(iterator p, const value_type& x)
    {
        typedef typename IteratorTraits<iterator>::value_type _C;
        typedef typename TypeTraits<_C>::is_pod_type is_pod_data;

        if (empty())
            initialize_empty_deque();

        if (is_map_realloc(false))
            map_realloc();

        if (is_last_buffer_full())
            alloc_buffer(false);

        iterator it = m_finish;
        for (; it != p; --it)
            *it = *(it - 1);

        construct(it.m_cur, x);
        ++m_finish;
        return it;
    }

private:
    size_type m_mapsize;
    T** m_map;  // this is T* m_map[m_mapsize];
    
    iterator m_begin;
    iterator m_finish;

    allocator_type m_node_alloc;
    map_allocator_type m_map_alloc;
};

template <class T, class Allocator>
    bool operator==(const deque<T,Allocator>& x, const deque<T,Allocator>& y)
{
    return true;
}
template <class T, class Allocator>
    bool operator< (const deque<T,Allocator>& x, const deque<T,Allocator>& y)
{
    return true;
}
template <class T, class Allocator>
    bool operator!=(const deque<T,Allocator>& x, const deque<T,Allocator>& y)
{
    return true;
}
template <class T, class Allocator>
    bool operator> (const deque<T,Allocator>& x, const deque<T,Allocator>& y)
{
    return true;
}
template <class T, class Allocator>
    bool operator>=(const deque<T,Allocator>& x, const deque<T,Allocator>& y)
{
    return true;
}
template <class T, class Allocator>
    bool operator<=(const deque<T,Allocator>& x, const deque<T,Allocator>& y)
{
    return true;
}
// specialized algorithms:
template <class T, class Allocator>
void swap(deque<T, Allocator>& x, deque<T, Allocator>& y)
{
    x.swap(y);
}

}  // namespace my

#endif /* end of include guard: MYDEQUE_H */
