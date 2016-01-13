#ifndef vector_H
#define vector_H

#include "mytypetraits.h"
#include <assert.h>
#include "myiterator.h"
#include "myalloc.h"
#include "myalgo.h"
#include <string.h>
#include <stddef.h>

namespace my
{
template <class T, class alloc = alloc_t<T> >
class vector
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef vector self;

    typedef my_reverse_iterator<iterator> reverse_iterator;
    typedef my_reverse_iterator<const_iterator> const_reverse_iterator;

public:
    vector(size_type n)
    {
        m_begin = get_memory(n);
        if (m_begin == NULL)
            return ;

        fill_n(m_begin, n);
        m_finish = m_begin + n;
        m_end = m_begin + n;
    }

    vector(size_type n, const T& x)
    {
        vector_imple(n, x, true_type());
    }
    template <class Iterator>
    vector(Iterator first, Iterator last)
    {
        typedef typename IntegerTraits<Iterator>::is_integer _C;
        vector_imple(first, last, _C());
    }
    vector(const self &x)
    {
        size_type n = x.size();
        m_begin = get_memory(n);
        fill(m_begin, x.begin(), x.end());

        m_finish = m_begin + n;
        m_end = m_begin + n;
    }
    ~vector()
    {
        clear();
        aaa.dealloc(m_begin);

        m_begin = m_finish = m_end = NULL;
    }

    self& operator=(const self& x)
    {
        clear();
        aaa.dealloc(m_begin);

        m_begin = get_memory(x.size());
        if (is_builtin(T()))
            memcpy(m_begin, x.m_begin, x.size() * sizeof (T));
        else
            fill(m_begin, x.begin(), x.end());
        m_finish = m_begin + x.size();
        m_end = m_begin + x.size();
    }
//    self& operator=(self& x);

    void assign(size_type n, const value_type& value)
    {
        clear();
        m_begin = get_memory(n);

        typedef typename TypeTraits<value_type>::is_pod_type is_pod_data;

//        if (is_pod_data() == true_type())

        while (n--)
        {
            m_begin[n] = value;
        }
        m_finish = m_end = m_begin + n;
    }
//    void assign(initializer_list<value_type> il); /* what is initializer_list?? */

    alloc get_allocator() const
    {
        return aaa;
    }

//    front back end begin rbegin rend size max_size capacity empty reserve 
    pointer data()
    {
        return m_begin;
    }
    pointer data() const
    {
        return m_begin;
    }

//    template <class... Args>
//        void emplace_back(Args&&... args);
//    template <class... Args>
//        iterator emplace(iterator pos, Args&&... args);
//    void clear()
//    {
//        pointer p = m_begin;
//        for (; p != m_end; ++p)
//            alloc.destroy(p);
//
//        m_finish = m_begin;
//    }

    void resize(size_type new_size, const value_type& x)
    {
        size_type old_size = size();
        size_type _capacity = capacity();
        if (capacity() == new_size)
            return;
        if (capacity() > new_size)
        {
            if (is_builtin(T()))
            {
                if (old_size < new_size)  // enlarge
                {
                    for (iterator p = m_finish; p != m_begin + new_size; ++p)
                        *p = x;
                }
//                else    POD data shrink: just move the m_finish foward....
            }
            else
            {
                if (new_size < old_size)  // shrink
                {
                    erase(m_begin + new_size, m_finish);
                }
                else            // enlarge
                {
                    for (iterator p = m_finish; p != m_begin + new_size; ++p)
                        *p = x;
                }
            }
            m_finish = m_begin + new_size;
        }
        else    // capacity() < new_size
        {
            while (_capacity < new_size)
                _capacity *= 2;
            pointer ttt = aaa.alloc(_capacity);
            if (is_builtin(T()))
            {
                memcpy(ttt, m_begin, old_size * sizeof (value_type));
            }
            else
            {
                fill(ttt, m_begin, m_finish);
                clear();
            }
            for (pointer p = ttt + old_size; p != ttt + new_size; ++p)
                *p = x;
            aaa.dealloc(m_begin);
            m_begin = ttt;
            m_finish = m_begin + new_size;
            m_end = m_begin + _capacity;
        }
    }

    void shrink_to_fit();


    bool _invariants() const;

    vector()
    {
        m_begin = m_finish = m_end = 0;
    }

    iterator begin()
    {
        return m_begin;
    }

    const_iterator begin() const
    {
        return m_begin;
    }

    iterator end()
    {
        return m_finish;
    }

    const_iterator end() const
    {
        return m_finish;
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(m_finish);
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(m_finish);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(m_begin);
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(m_begin);
    }

    reference front()
    {
        return *m_begin;
    }

    const reference front() const
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

    void push_back()
    {
        insert(end(), T());
    }

    void push_back(const T &x)
    {
        insert(end(), x);
    }

    void pop_back()
    {
        aaa.destroy(--m_finish);
    }


    size_type size() const
    {
        return distance(m_begin, m_finish);
    }

    size_type capacity() const
    {
        return distance(m_begin, m_end);
    }

    void resize(size_type new_size)
    {
        resize(new_size, T());
    }

    void reserve(size_type n)
    {
        if (capacity() < n)
        {
            size_type old_size = size();
            size_type _capacity = capacity();
            while (_capacity < n)
                _capacity *= 2;

            if (is_builtin(T()))
            {
                m_begin = aaa.realloc(m_begin, _capacity * sizeof (T));
            }
            else
            {
                pointer ttt = aaa.alloc(_capacity);
                fill(ttt, m_begin, m_finish);
                aaa.dealloc(m_begin);
                m_begin = ttt;
            }
            m_finish = m_begin + old_size;
            m_end = m_begin + _capacity;
        }
    }

    void clear()
    {
        typedef typename TypeTraits<T>::is_pod_type is_pod_data;
        clear_imple(is_pod_data());
    }

    bool empty() const
    {
        return m_begin == m_finish;
    }

    iterator insert(iterator pos, const value_type& x)
    {
        return insert_imple(pos-m_begin, x);
    }

    void insert(iterator pos, size_type n, const value_type& x)
    {
        while (n--)
        {
            insert(pos, x);
        }
    }

    iterator insert(iterator first, iterator last)
    {
        return insert(first, last-first, T());
    }

    template <class InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last)
    {
        my_reverse_iterator<InputIterator> rfirst(last);
        my_reverse_iterator<InputIterator> rlast(first);
        for (; rfirst != rlast; ++rfirst)
        {
            insert(pos, *rfirst);
        }
    }
//    iterator insert(iterator pos, initializer_list<value_type> il);

    iterator erase(iterator pos)
    {
        typedef typename TypeTraits<T>::is_pod_type is_pod_data;
        return erase_imple(pos, 1, is_pod_data());
    }

    iterator erase(iterator first, iterator last)
    {
        typedef typename TypeTraits<T>::is_pod_type is_pod_data;
        return erase_imple(first, last - first, is_pod_data());
    }

    reference at(size_type i)
    {
        return m_begin[i];
    }

    const reference at(size_type i) const
    {
        return m_begin[i];
    }

    reference operator[] (size_type i)
    {
//        assert(size() > i);
        return m_begin[i];
    }

    const reference operator[] (size_type i) const
    {
//        assert(size() > i);
        return m_begin[i];
    }

    void swap(self& v)
    {
        my::swap(m_begin, v.m_begin);
        my::swap(m_finish, v.m_finish);
        my::swap(m_end, v.m_end);
    }

private:
    template <class T1, class T2>
    void vector_imple(T1 n1, T2 n2, false_type)
    {
        size_type n = distance(n1, n2);
        m_begin = get_memory(n);
        if (m_begin == NULL)
            return ;

        fill(m_begin, n1, n2);
        m_finish = m_begin + n;
        m_end = m_begin + n;
    }

    template <class T1, class T2>
    void vector_imple(T1 n, T2 x, true_type)
    {
        m_begin = get_memory(n);
        if (m_begin == NULL)
            return ;

        for (size_type i = 0; i < n; i++)
            m_begin[i] = x;
        m_finish = m_begin + n;
        m_end = m_begin + n;
    }

    pointer get_memory(size_type n)
    {
        return aaa.alloc(n);
    }

    iterator insert_imple(size_type index, const value_type &x)
    {
        if (empty())
            reserve(1);
        else if (full())
            reserve(capacity() * 2);

        pointer p = m_begin + index;
        typedef typename TypeTraits<T>::is_pod_type is_pod_data;
        if (is_builtin(is_pod_data()))
        {
            if (p != m_finish)
                memmove(p + 1, p, sizeof (T) * (m_end-p));
        }
        else
        {
            if (p != m_finish)
                for (p = m_finish; p != m_begin + index; --p)
                {
                    *p = *(p - 1);
                    // 0 1 2 3 4 5 6 7 8 9
                }
        }
        construct(p, x); // *p = x; 
        ++m_finish;

        return p;
    }

    iterator erase_imple(iterator p, size_type count, false_type)
    {
        iterator p1 = p;
        for (; p + count != m_finish; ++p)
        {
            *p = *(p + count);
        }
        destroy(p, m_finish);
        m_finish -= count;

        return p1;
    }
    iterator erase_imple(iterator p, size_type count, true_type)
    {
        iterator p1 = p;
        memmove(p, p + count, (m_finish - p - count) * sizeof (value_type));
        m_finish -= count;

        return p1;
    }

    void clear_imple(false_type)
    {
        erase(m_begin, m_finish);
        m_end = m_finish = m_begin; 
    }
    void clear_imple(true_type)
    {
        m_end = m_finish = m_begin; 
    }

    bool full()
    {
        return (m_begin != m_finish && m_finish == m_end);
    }
private:
    pointer m_begin;
    pointer m_finish;
    pointer m_end;
    alloc aaa;
};

//operator >
//operator <
//operator >=
//operator <=
//operator ==
//operator !=
template <class T>
void swap(vector<T> &a, vector<T>&b)
{
    a.swap(b);
}

//template <bool, class alloc = alloc_t<bool> >
//vector
//{
//public:
//    vector() {};
//    ~vector() {};
//}

}   // namespace my

#endif /* end of include guard: vector_H */
