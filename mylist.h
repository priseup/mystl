#ifndef LIST_H
#define LIST_H

#include "myiterator.h"
#include "myalloc.h"
#include "myalgo.h"

namespace my
{

template <class T>
struct node
{
    T data;
    struct node *prev;
    struct node *next;
};

template <class T,
         class reference,
         class pointer>
struct listit : public Iterator<binput_tag, T, reference, pointer>
{
    typedef listit self;
    // but why must typedef iterator && const_iterator....
    // if reference = T&, pointer = T*, self is OK ???
    typedef listit<T, T&, T*> iterator;
    typedef listit<T, const T&, const T*> const_iterator;

    listit() : m_node(0) {}
    listit(const iterator& t): m_node(t.m_node) {}
    listit(node<T> *p): m_node(p) {}

    self& operator++()
    {
        m_node = m_node->next;
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
        m_node = m_node->prev;
        return *this;
    }

    self operator--(int)
    {
        self t = *this;
        --*this;
        return t;
    }

    reference operator*()
    {
        return m_node->data;
    }

    pointer operator->()
    {
        return &(operator*());
    }

    bool operator!=(const self& t)
    {
        return m_node != t.m_node;
    }

public:
    node<T> *m_node;
};

//template <class T, class Alloc = alloc_t<T> > which is ok? with the following template<> define.
template <class T, class Alloc = alloc_t<node<T> > >
class list
{
public:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef size_t size_type;

    typedef listit<T, reference, pointer> iterator;
    typedef listit<T, const_reference, const_pointer> const_iterator;
    typedef my_reverse_iterator<iterator> reverse_iterator;
    typedef my_reverse_iterator<const_iterator> const_reverse_iterator;

    typedef list self;

    list(): m_size(0)
    {
        m_start = create_node(T());
        m_start->prev = m_start->next = m_start;
    }
    list(size_type n, const T& value)
    {
        list_imple(n, value, true_type());
    }
    explicit list(size_type n)
    {
        m_start = create_node(T());
        m_start->pre = m_start->next = m_start;

        insert(begin(), n, T());
    }
    list(const self& t)
    {
        m_start = create_node(T());
        m_start->pre = m_start->next = m_start;

        insert(begin(), t.begin(), t.end());
    }
    template <class InputIterator>
    list(InputIterator first, InputIterator last)
    {
        typedef typename IntegerTraits<InputIterator>::is_integer _C;
        list_imple(first, last, _C());
    }
    ~list()
    {
        clear();
        destroy(&m_start->data);
        m_alloc.dealloc(m_start);
    }

    iterator begin()
    {
        return iterator(m_start->next);
    }

    const_iterator begin() const
    {
        return const_iterator(m_start->next);
    }

    iterator end()
    {
        return iterator(m_start);
    }

    const_iterator end() const
    {
        return const_iterator(m_start);
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

    reference front()
    {
        return m_start->next->data;
    }

    const_reference front() const
    {
        return m_start->next->data;
    }

    reference back()
    {
        return m_start->prev->data;
    }

    const_reference back() const
    {
        return m_start->prev->data;
    }

    void push_front()
    {
        insert(begin());
    }

    void push_front(const T &x)
    {
        insert(begin(), x);
    }

    void push_back()
    {
        insert(end());
    }

    void push_back(const T &x)
    {
        insert(end(), x);
    }

    void pop_back()
    {
        erase(iterator(m_start->prev));
    }

    void pop_front()
    {
        erase(begin());
    }

    size_type size() const
    {
        return m_size;
    }

    size_type resize(size_type new_size)
    {
       if (m_size > new_size) 
       {
           node<T> *p = m_start->next;
           while (new_size--)
               p = p->next;

           erase(iterator(p), end());
       }
       else
       {
           size_type n = m_size-new_size;
           while (n--)
               push_back();
       }

       return  new_size;
    }

    void clear()
    {
        erase(begin(), end());
    }

    bool empty() const
    {
        return m_start == m_start->next;
//        return !m_size;
    }

    iterator insert(iterator pos, size_type n, const value_type &x)
    {
        iterator p;
        while (n > 0)
        {
            p = insert(pos, x);
            n--;
        }

        return p;
    }

    iterator insert(iterator pos)
    {
        return insert(pos, T());
    }

    template <class _InputIterator>
    iterator insert(iterator pos, _InputIterator first, _InputIterator last)
    {
        iterator p;
        for (; first != last; ++first)
            p = insert(pos, *first);
        return p;
    }

    iterator insert(iterator pos, const T& x)
    {
        node<T> *p = create_node(x);
        if (empty())
        {
            m_start->next = p;
            p->prev = m_start;
            m_start->prev = p;
            p->next = m_start;
        }
        else
        {
            pos.m_node->prev->next = p;
            p->prev = pos.m_node->prev;
            pos.m_node->prev = p;
            p->next = pos.m_node;
        }

        m_size++;
        return --pos;
    }

    iterator erase(iterator first, iterator last)
    {
//        iterator p;
        for (; first != last; ++first)
        {
//            p = erase(first);
            erase(first);
        }

        return first;
//        return p;
    }

    iterator erase(iterator pos)
    {
        if (empty())
            return iterator(NULL);
        else if (m_size == 1)
        {
            delete_node(m_start->next);
            m_size--;

            return iterator(m_start);
        }
        else
        {
            iterator p = pos;
            delete_node(pos.m_node);

            m_size--;
            return ++p;
        }
    }

    void assign(size_type n, const value_type &x)
    {
        clear();
        insert(begin(), n, x);
    }
    template <class _InputIterator>
    void assign(_InputIterator first, _InputIterator last)
    {
        clear();
        insert(begin(), first, last);
    }

    void emplace_front() {}
    void emplace_back() {}

    Alloc get_allocator()
    {
        return m_alloc;
    }

//    transfer elements from list to list
    void splice(iterator pos, list& x)
    {
        node<T> *before_pos = pos.m_node->prev;
        before_pos->next = x.m_start->next;
        x.m_start->next->prev = before_pos;

        x.m_start->prev->next = pos.m_node;
        pos.m_node->prev = x.m_start->prev;

        x.m_start->prev = x.m_start->next = x.m_start;
        m_size += x.m_size;
        x.m_size = 0;
    }

    void splice(iterator pos, list& x, iterator i)
    {
        i.m_node->prev->next = i.m_node->next;
        i.m_node->next->pre = i.m_node->prev;

        node<T> *before_pos = pos.m_node->prev;
        before_pos->next = i.m_node;
        i.m_node->prev = before_pos;

        i.m_node->next = pos.m_node;
        pos.m_node->prev = i.m_node;

        m_size++;
        x.m_size--;
    }
    void splice(iterator pos, list& x, iterator first, iterator last)
    {
        node<T>* last_node = last.m_node->prev;

        first.m_node->prev->next = last.m_node;
        last.m_node->prev = first.m_node->prev;

        node<T>* before_pos = pos.m_node->prev;
        before_pos->next = first.m_node;
        first.m_node->prev = before_pos;

        last_node->next = pos.m_node->next;
        pos.m_node->next->prev = last_node;

        size_type n = distance(first, last);
        m_size += n;
        x.m_size -= n;
    }

    void remove(const T& t)
    {
        for (iterator it = begin(); it != end(); ++it)
        {
            if (*it == t)
            {
                erase(it);
                break;
            }
        }
    }

    template <class predicate>
    void remove_if(predicate)
    {
    }

   /*remove duplicate values*/
    void unique()
    {
        for (iterator it = begin(); it != end();)
        {
            if (*it == *++it)
                erase(it);
        }
    }

    void sort()
    {
    }

    void reverse()
    {
        using my::swap;
        node<T>* p = m_start;
        do
        {
            swap(p->prev, p->next);
            p = p->next;
        } while (p != m_start);
    }

    void merge(self& x)
    {
        using my::swap;
//        splice(begin(), x);
        x.splice(begin(), *this);
//        swap(x);
    }

    void swap(self& t)
    {
        using my::swap;
        swap(m_start, t.m_start);
        swap(m_size, t.m_size);
    }

    self& operator= (const list& t)
    {
        erase(begin(), end());
        insert(begin(), t, t.begin(), t.end());
    }

private:
    template <class T1, class T2>
    void list_imple(T1 t1, T2 t2, true_type)
    {
        m_size = 0;
        m_start = create_node(T());
        m_start->prev = m_start->next = m_start;

        while (t1--)
            push_back(t2);
    }
    template <class T1, class T2>
    void list_imple(T1 t1, T2 t2, false_type)
    {
        m_size = 0;
        m_start = create_node(T());
        m_start->prev = m_start->next = m_start;

        insert(begin(), t1, t2);
    }

    node<T>* create_node(const T& x)
    {
        node<T> *p = m_alloc.alloc(1);
        construct(&p->data, x);
        p->next = p->prev = NULL;

        return p;
    }

    void delete_node(node<T> *p)
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        destroy(&p->data);
        m_alloc.dealloc(p);
    }

private:
    node<T> *m_start;
    size_type m_size;
    Alloc m_alloc;
};

template <class T>
void swap(list<T>& l1, list<T>& l2)
{
    l1.swap(l2);
}

}       // namespace my
#endif /* end of include guard: LIST_H */
