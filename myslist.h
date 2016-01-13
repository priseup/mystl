#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#include "myiterator.h"
#include "myalloc.h"
#include "myalgo.h"

namespace my
{

template <class T>
struct slist_node
{
    T data;
    struct slist* next;
};

template <class T, class ref, class ptr>
struct slistit : public Iterator<input_tag, T, ref, ptr>
{
    typedef slitit Self;
    typedef Iterator<input_tag, T, ref, ptr> Baseit;
    typedef slistit<T, T&, T*> iterator;
    typedef slistit<T, const T&, const T*> const_iterator;

    typedef typename Baseit::reference reference;
    typedef typename Baseit::const_reference const_reference;
    typedef typename Baseit::pointer pointer;
    typedef typename Baseit::const_pointer const_pointer;
    
    slistit() : m_node(NULL) {}
    slistit(slist_node<T>* p) : m_node(p) {}
    slistit(const iterator& it) : m_node(it.m_node) {}

    Self& operator++()
    {
        m_node = m_node->next;
        return *this;
    }

    Self operator++(int)
    {
        Self tmp = *this;
        m_node = m_node->next;
        return tmp;
    }

    reference operator*()
    {
        return *m_node;
    }

    const_reference operator*() const
    {
        return *m_node;
    }

    pointer operator->()
    {
        return m_node;
    }

    const_pointer operator->() const
    {
        return m_node;
    }

    bool operator=(const Self& t) const
    {
        return m_node == t.m_node;
    }

    bool operator!=(const Self& t) const
    {
        return m_node != t.m_node;
    }

    slist_node<T>* m_node;
};

template <class T, class alloc = alloc_t<T> >
class slist
{
public:
    typedef slist Self;
    typedef typename alloc::reference reference;
    typedef typename alloc::const_reference const_reference;
    typedef typename alloc::pointer pointer;
    typedef typename alloc::const_pointer const_pointer;
    typedef typename alloc::size_type size_type;
    typedef typename AllocatorTraits<slist_node, alloc>::allocator_type allocator_type;

    typedef slistit<T, T&, T*> iterator;
    typedef slistit<T, const T&, const T*> const_iterator;
    typedef my_reverse_iterator<iterator> reverse_iterator;
    typedef my_reverse_iterator<const_iterator> const_reverse_iterator;

public:
    slist() {m_start.next = NULL;}
    slist(const Self& t)
    {}
    slist(size_type n)
    {}
    template <class InputIterator>
    slist(InputIterator first, InputIterator last)
    {}
    slist(size_type n, const T& x)
    {}
    ~slist()
    {}
    slist& operator=(const Self& t)
    {}

    iterator begin()
    {
        return m_start.next;
    }

    const_iterator begin() const
    {
        return m_start.next;
    }

    iterator end()
    {
        return NULL;
    }

    const_iterator end() const
    {
        return NULL;
    }

    reverse_iterator rbegin()
    {
        return end();
    }

    const_reverse_iterator begin() const
    {
        return end();
    }

    reverse_iterator rend()
    {
        return begin();
    }

    const_reverse_iterator rend() const
    {
        return begin();
    }

    reference front()
    {
        return m_start.next->data;
    }

    const_reference front() const
    {
        return m_start.next->data;
    }

    size_type size() const
    {
        size_type n = 0;
        pointer p = m_start.next;

        while (p != NULL)
        {
            n++;
            p = p->next;
        }

        return n;
    }

    bool empty() const
    {
        return m_start.next != NULL;
    }

    void swap(slist& t)
    {
        swap(m_star.next, t.m_start.next);
    }

    void assign(size_type n, const T& x)
    {
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last)
    {}

    void resize(size_type n, const T& x)
    {
        size_type old_size = size();
        if (old_size < n)
        {}
        else
        {}
    }

    void resize(size_type n)
    {
        resize(n, T());
    }

    void clear()
    {
        pointer p = m_start.next;

        while (p)
        {
            m_start.next = p->next;
            delete_node(p);
            p = m_start.next;
        }

        m_start.next = NULL;
    }

    void reverse()
    {
        pointer before = NULL;
        pointer now = m_start.next;
        pointer after;

        while (now && now->next)
        {
            after = now->next;
            now->next = before;
            before = now;
            now = after;
            after = after->next;
        }
        now->next = before;
        
        m_start.next = now;
    }

    void unique()
    {
        pointer p = m_start.next;
        pointer tmp;
        while (p && p->next)
        {
            tmp = p; p = p->next;
            if (tmp->data == p->data)
            {
                delete_node(tmp);
            }
        }
    }

    void sort()
    {}

    void merge(slist& t)
    {}

    void push_front()
    {
        push_front(T());
    }
    void push_front(const T& x)
    {
        pointer tmp = create_node(x);
        tmp->next = m_start.next;
        m_start.next = tmp;
    }

    void pop_front()
    {
        pointer p = m_start.next;
        m_start = p->next;

        delete_node(p);
    }

    iterator erase(iterator it)
    {
        if (it == begin())
        {
            pop_front();
            return begin();
        }
        else
            return erase_after(find_prev(it));

    iterator erase(iterator it1, iterator it2)
    {
    }

    iterator erase_after(iterator it)
    {
        pointer p = it.m_node->next;
        it.m_node->next = p->next;

        delete_node(p);

        return it.m_node->next;
    }

    iterator find(const T& key)
    {
        pointer p = m_start.next;

        while (p && p->data != key)
            p->next;

        return p;
    }

    const_iterator find(const T& key) const
    {
        pointer p = m_start.next;

        while (p && p->data != key)
            p->next;

        return p;
    }

    iterator find_prev(const_iterator pos)
    {
        PointerContainer *p = &m_start;
        while (p && p->next != pos.m_node)
        {
            p = p->next;
        }

        return slist_node<T>(p);
    }

    const_iterator find_prev(const_iterator pos) const
    {
        PointerContainer *p = &m_start;
        while (p && p->next != pos.m_node)
        {
            p = p->next;
        }

        return slist_node<T>(p);
    }

    iterator insert_after(iterator it, const T& x)
    {
        pointer tmp = create_node(x);

        tmp->next = it.m_node->next;
        it.m_node->next = tmp;

        return tmp;
    }

    iterator insert(iterator it, const T& x)
    {
        if (it == begin())
        {
            push_front(x);
            return begin();
        }
        else
            return insert_after(find_prev(it), x);
    }

    void remove(const T& x)
    {}

    allocator_type& get_allocator() const
    {
        return m_alloc;
    }
private:
    pointer create_node()
    {
        pointer p = m_alloc.alloc(1);
        p->next = NULL;

        return p;
    }

    pointer create_node(const T& x)
    {
        pointer p = m_alloc.alloc(1);
        p->data = x;
        p->next = NULL;

        return p;
    }

    void delete_node(pointer p)
    {
        pointer p_prev = find_prev(p->data);
        p_prev->next = p->next;

        destroy(p);
        m_alloc.dealloc(p);
    }

private:
    struct PointerContainer
    {
        struct PointerContainer *next;
    };

    PointerContainer m_start;
    allocator_type m_alloc;
};

template <class T, class Alloc>
bool operator==(const slist<T, Alloc>& x, const slist<T, Alloc>& y)
{}

template <class T, class Alloc>
bool operator!=(const slist<T, Alloc>& x, const slist<T, Alloc>& y)
{}

template <class T, class Alloc>
bool operator>(const slist<T, Alloc>& x, const slist<T, Alloc>& y)
{}

template <class T, class Alloc>
bool operator>=(const slist<T, Alloc>& x, const slist<T, Alloc>& y)
{}

template <class T, class Alloc>
bool operator<(const slist<T, Alloc>& x, const slist<T, Alloc>& y)
{}

template <class T, class Alloc>
bool operator<=(const slist<T, Alloc>& x, const slist<T, Alloc>& y)
{}

template <class T, class Alloc>
void swap(const slist<T, Alloc>& x, const slist<T, Alloc>& y)
{
    x.swap(y);
}


}   // namespace my

#endif /* end of include guard: MYHASHTABLE_H */
