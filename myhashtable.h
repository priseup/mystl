#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#include "myiterator.h"
#include "myalloc.h"
#include "mypair.h"
#include "myhashfun.h"
#include "myfunction.h"
#include "myvector.h"
#include "myconstruct.h"

namespace my
{

// Note: assumes long is at least 32 bits.
enum { __stl_num_primes = 28 };

static const unsigned long __stl_prime_list[__stl_num_primes] =
{
    53ul,         97ul,         193ul,       389ul,       769ul,
    1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
    49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
    1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
    50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
    1610612741ul, 3221225473ul, 4294967291ul
};

unsigned long get_next_prime(unsigned long n)
{
    int i = 0;
    while (n > __stl_prime_list[i])
        i++;

    return __stl_prime_list[i];
}

template <class T>
struct hash_node
{
    T data;
    struct hash_node* next;
};

template <class Key,
         class T,
         class Hash,
         class EqualKey,
         class ExtractKey,
         class Alloc,
         class Ref,
         class Ptr>
class hashtable;

template <class Key,
         class T,
         class ref,
         class ptr,
         class Hash,
         class EqualKey,
         class ExtractKey,
         class Alloc>
struct hashtableit
{
    typedef hashtableit Self;
    typedef hash_node<T> hashnode_type;
    typedef hashtable<Key, T, Hash, EqualKey, ExtractKey, Alloc, ref, ptr> hashtable_type;
    typedef hashtableit<Key, T, T&, T*, Hash, EqualKey, ExtractKey, Alloc> iterator;
    typedef hashtableit<Key, T, const T&, const T*, Hash, EqualKey, ExtractKey, Alloc> const_iterator;

    typedef input_tag catagory;
    typedef ref reference;
    typedef ptr pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    hashtableit(const iterator& it): m_hashtable(it.m_hashtable),
                                m_node(it.m_node) {}
    hashtableit(): m_hashtable(NULL), m_node(NULL) {}
    hashtableit(hashtable_type* ht, hashnode_type* hn): m_hashtable(ht),
                                                        m_node(hn) {}

    Self& operator++()
    {
        hashnode_type* old = m_node;
        m_node = m_node->next;
        if (!m_node)
        {
            for (size_type i = m_hashtable->get_bucket_index(old->data) + 1;
                    i < m_hashtable->bucket_count(); ++i)
            {
                if (m_hashtable->m_bucket[i])
                {
                    m_node = m_hashtable->m_bucket[i];
                    break;
                }
            }
        }

        return *this;
    }

    Self operator++(int)
    {
        Self t = *this;
        ++*this;
        return t;
    }

    reference operator*()
    {
        return m_node->data;
    }

    reference operator*() const
    {
        return m_node->data;
    }

    pointer operator->()
    {
        return &operator*();
    }

    pointer operator->() const
    {
        return &operator*();
    }
    
    bool operator!=(const Self& t) const
    {
        return m_node != t.m_node;
    }
    bool operator==(const Self& t) const
    {
        return m_node == t.m_node;
    }

    hashtable_type* m_hashtable;
    hashnode_type* m_node;
};

//template <class T, class ExtractKey = select1st<T>, class EqualKey = equal<typename T::key_type>, class Alloc = alloc_t<T> >
template <class T, class ExtractKey, class EqualKey, class Alloc = alloc_t<T> >
class hash_list
{
public:
    typedef hash_node<T> hashnode_type;
    typedef typename AllocatorTraits<hashnode_type, Alloc>::allocator_type allocator_type;

    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef hashnode_type* pointer;
    typedef const hashnode_type* const_pointer;
    typedef size_t size_type;

    typedef typename T::key_type key_type;

public:
    hash_list(): m_ptr(NULL) {}
    hash_list(hashnode_type* p): m_ptr(p) {}
    hash_list(hash_list& hl): m_ptr(hl.m_ptr), m_get_key(hl.m_get_key),
                                m_equal_key(hl.m_equal_key),
                                m_alloc(hl.m_alloc){}
    hash_list(hashnode_type* p, const ExtractKey& ek,
            const EqualKey& eq): m_ptr(p), m_get_key(ek),
            m_equal_key(eq) {}

    void push_front(const T& x)
    {
        pointer p = create_node(x);
        p->next = m_ptr;
        m_ptr = p;
    }

    pointer set_header(pointer p)
    {
        return m_ptr = p;
    }
    pointer get_header() const
    {
        return m_ptr;
    }

    pointer find(const key_type& key)
    {
        pointer first = m_ptr;
        while (first && !equal_key(first->data, key))
            first = first->next;

        return first;
    }

    const_pointer find(const key_type& key) const
    {
        pointer first = m_ptr;
        while (first && !equal_key(first->data, key))
            first = first->next;

        return first;
    }

    pointer insert_after(const value_type& x)
    {
        pointer first = find(get_key(x));

        return insert_after(first, x);
    }
    pointer insert_after(pointer p, const value_type& x)
    {
        if (p)
        {
            pointer p_new = create_node(x);
            p_new->next = p->next;
            p->next = p_new;
            
            return p_new;
        }
        else
        {
            push_front(x);
            return m_ptr;
        }
    }

    pointer find_or_insert(const value_type& x)
    {
        pointer first = find(get_key(x));

//        no match, so push front
        if (!first)
        {
            push_front(x);
            return m_ptr;
        }

//        return the matched node
        return first;
    }

    pair<pointer, pointer> equal_range(const key_type& key)
    {
        pointer first = find(key);
        pointer last = first ? first->next : NULL;

        while (last && equal_key(last->data, key))
            last = last->next;

        return pair<pointer, pointer>(first, last);
    }

    pair<const_pointer, const_pointer> equal_range(const key_type& key) const
    {
        const_pointer first = find(key);
        const_pointer last = first ? first->next : NULL;

        while (last && equal_key(last->data, key))
            last = last->next;

        return pair<const_pointer, const_pointer>(first, last);
    }

    size_type count(const key_type& key) const
    {
        size_type n = 0;
        const_pointer p = find(key);
        while (p && equal_key(p->data, key))
        {
            n++; p = p->next;
        }

        return n;
    }

//    erase the elements containning the 'key'
//    and return the count of removed elements of list
    size_type erase(const key_type& key)
    {
        size_type n = 0;
        pointer p = m_ptr;

        while (m_ptr && equal_key(m_ptr->data, key))
        {
            p = m_ptr;
            m_ptr = m_ptr->next;
            delete_node(p);
            n++;
        }
        while (p && p->next && !equal_key(p->next->data, key))
        {
            p = p->next;
        }
        while (p->next && equal_key(p->next->data, key))
        {
            pointer to_delete = p->next;
            p->next = to_delete->next;
            delete_node(to_delete);
            n++;
        }

        return n;
    }

    void erase(pointer del)
    {
        pointer p = m_ptr;
        if (m_ptr == del)
        {
            m_ptr = m_ptr->next;
            delete_node(p);
            return ;
        }
        while (p && p->next && p->next != del)
        {
            p = p->next;
        }
        if (p->next)
        {
            pointer to_delete = p->next;
            p->next = to_delete->next;
            delete_node(to_delete);
        }
    }

    void erase(pointer first, pointer last)
    {
        if (first == m_ptr)
        {
            while (m_ptr && m_ptr != last)
            {
                pointer p = m_ptr;
                m_ptr = m_ptr->next;
                delete_node(p);
            }

            return ;
        }

        while (first->next != last)
        {
            pointer p = first->next;
            first->next = p->next;
            delete_node(p);
        }
        pointer first_prev = m_ptr;
        while (first_prev->next != first)
            first_prev = first_prev->next;

        first_prev->next = first->next;
        delete_node(first);
    }

    void clear()
    {
        pointer p;
       
        while (m_ptr)
        {
            p = m_ptr;
            m_ptr = m_ptr->next;
            delete_node(p);
        }

        m_ptr = NULL;
    }

    size_type size() const
    {
        pointer p = m_ptr;
        size_type n = 0;
        while (p)
        {
            n++;
            p = p->next;
        }

        return n;
    }

    bool empty() const
    {
        return m_ptr == NULL;
    }

private:
    pointer create_node(const T& x)
    {
        pointer p = m_alloc.alloc(1);
        construct(&p->data, x);
        p->next = NULL;

        return p;
    }

    void delete_node(pointer p)
    {
        destroy(&p->data);
        m_alloc.dealloc(p);
    }

    key_type get_key(const T& x) const
    {
        return m_get_key(x);
    }

    bool equal_key(const key_type& key1, const key_type& key2) const
    {
        return m_equal_key(key1, key2);
    }
    bool equal_key(const T& x, const key_type& key) const
    {
        return equal_key(get_key(x), key);
    }
    bool equal_key(const T& x1, const T& x2) const
    {
        return equal_key(get_key(x1), get_key(x2));
    }

private:
    ExtractKey m_get_key;
    EqualKey m_equal_key;
    allocator_type m_alloc;
    hashnode_type* m_ptr; 
};

template <class Key,
         class T,
         class Hash = hash<Key>,
         class EqualKey = equal<Key>,
         class ExtractKey = select1st<T>,
         class Alloc = alloc_t<T>,
         class Ref = T&, class Ptr = T*>
class hashtable
{
friend class hashtableit<Key, T, Ref, Ptr, Hash, EqualKey, ExtractKey, Alloc>;
public:
    typedef Key key_type;
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef hash_node<T> hashnode_type;
    typedef hashnode_type* pointer;
    typedef const hashnode_type* const_pointer;
    typedef size_t size_type;
    typedef hashtableit<Key, T, T&, T*, Hash, EqualKey, ExtractKey, Alloc> iterator;
    typedef hashtableit<Key, T, const T&, const T*, Hash, EqualKey, ExtractKey, Alloc> const_iterator;
    typedef typename AllocatorTraits<hashnode_type, Alloc>::allocator_type allocator_type;

    typedef hashtable Self;

public:
    hashtable() {}
    hashtable(size_type n): m_bucket(n) {}
    hashtable(const Hash& hf, const EqualKey& eq,
            const ExtractKey& ex, const allocator_type& a): m_hash(hf), m_equal_key(eq),  m_get_key(ex), m_alloc(a), hlist(NULL, ex, eq) {}
    ~hashtable()
    {
        clear();
    }

Self& operator=(const Self& t)
{
    if (this != &t)
    {
        m_hash = t.m_hash;
        m_equal_key = t.m_equal_key;
        m_get_key = t.m_get_key;
        m_alloc = t.m_alloc;
        m_bucket = t.m_bucket;
    }
}

reference operator[](size_type i)
{
    iterator it = begin();
    while (i--)
        ++it;

    return *(++it);
}

const_reference operator[](size_type i) const
{
    const_iterator it = begin();
    while (i--)
        ++it;

    return *(++it);
}

reference at(size_type i)
{
    iterator it = begin();
    while (i--)
        ++it;

    return *(++it);
}

const_reference at(size_type i) const
{
    const_iterator it = begin();
    while (i--)
        ++it;

    return *(++it);
}

size_type count(const Key& key) const
{
    size_type i = get_bucket_index(key);
    hlist.set_header(m_bucket[i]);

    return hlist.count(key);
}

pair<iterator, iterator> equal_range(const Key& key)
{
    size_type i = get_bucket_index(key);
    hlist.set_header(m_bucket[i]);
    pair<pointer, pointer> p = hlist.equal_range(key);

    if (p.first == NULL)
        return pair<iterator, iterator>(iterator(this, NULL),
                                                    iterator(this, NULL));
    else if (p.second == NULL)
    {
        i++;
        while (i < m_bucket.size() && !m_bucket[i])
            i++;
        if (i < m_bucket.size())
            p.second = m_bucket[i];

        return pair<iterator, iterator>(iterator(this, p.first),
                                                    iterator(this, p.second));
    }
}

pair<const_iterator, const_iterator> equal_range(const Key& key) const
{
    size_type i = get_bucket_index(key);
    hlist.set_header(m_bucket[i]);
    pair<pointer, pointer> p = hlist.equal_range(key);

    if (p.first == NULL)
        return pair<const_iterator, const_iterator>(iterator(this, NULL),
                                                    iterator(this, NULL));
    else if (p.last == NULL)
    {
        i++;
        while (i < m_bucket.size() && !m_bucket[i])
            i++;
        if (i < m_bucket.size())
            p.last = m_bucket[i];

        return pair<const_iterator, const_iterator>(iterator(this, p.first),
                                                    iterator(this, p.last));
    }
}

bool empty() const
{
    for (size_type i = 0; i < m_bucket.size(); ++i)
        if (!m_bucket[i]);
            return false;

    return true;
}

size_type size() const
{
    size_type n = 0;
    for (size_type i = 0; i < m_bucket.size(); i++)
    {
        hlist.set_header(m_bucket[i]);

        n += hlist.size();
    }

    return n;
}

//    Return maximum size (public member function)
size_type max_size() const
{
    return size_type(-1);
}

iterator begin()
{
    for (size_type i = 0; i < m_bucket.size(); ++i)
        if (m_bucket[i] != NULL)
            return iterator(this, m_bucket[i]);

    return iterator(this, NULL);
}

iterator end()
{
    return iterator(this, NULL);
}

const_iterator begin() const
{
    for (size_type i = 0; i < m_bucket.size(); ++i)
        if (m_bucket[i] != NULL)
            return iterator(this, m_bucket[i]);

    return iterator(this, NULL);
}

const_iterator end() const
{
    return iterator(this, NULL);
}

size_type bucket_count() const
{
    return m_bucket.size();
}

size_type max_bucket_count() const
{
    return __stl_prime_list[__stl_num_primes-1];
}

//    Locate element's bucket (public member function)
//void bucket()
//{}

size_type elems_in_bucket(size_type bucket) const
{
    hlist.set_header(m_bucket[bucket]);

    return hlist.size();
}

pair<iterator, bool> insert_unique(const value_type& v)
{
    resize(size() + 1);
    return insert_unique_noresize(v);
}

iterator insert_equal(const value_type& v)
{
    resize(size() + 1);
    return insert_equal_noresize(v);
}

pair<iterator, bool> insert_unique_noresize(const value_type& v)
{
    size_type i = get_bucket_index(v);
    hlist.set_header(m_bucket[i]);
    pointer p = hlist.find_or_insert(v);

    return pair<iterator, bool>(iterator(this, p), update_bucket(i));
}

iterator insert_equal_noresize(const value_type& v)
{
    size_type i = get_bucket_index(v);
    hlist.set_header(m_bucket[i]);
    pointer p = hlist.insert_after(v);
    update_bucket(i);

    return iterator(this, p);
}

reference find_or_insert(const value_type& v)
{
    resize(size() + 1);
    size_type i = get_bucket_index(v);
    hlist.set_header(m_bucket[i]);
    pointer p = hlist.find_or_insert(v);
    update_bucket(i);

    return p->data;
}

iterator find(const key_type& key)
{
    size_type i = get_bucket_index(key);
    hlist.set_header(m_bucket[i]);

    return iterator(this, hlist.find(key));
}
const_iterator find(const key_type& key) const
{
    size_type i = get_bucket_index(key);
    hlist.set_header(m_bucket[i]);

    return iterator(this, hlist.find(key));
}

size_type erase(const key_type& key)
{
    size_type i = get_bucket_index(key);
    pointer p = m_bucket[i];
    hlist.set_header(m_bucket[i]);

    size_type n = hlist.erase(key);
    update_bucket(i);

    return n;
}
void erase(const iterator& it)
{
    size_type i = get_bucket_index(it.m_node->data);
    pointer p = m_bucket[i];
    hlist.set_header(m_bucket[i]);

    hlist.erase(it.m_node);
    update_bucket(i);
}

bool update_bucket(size_type i)
{
    if (hlist.get_header() != m_bucket[i])
    {
        m_bucket[i] = hlist.get_header();
        return true;
    }

    return false;
}

void erase(iterator first, iterator last)
{
    size_type i1 = get_bucket_index(first.m_node->data);
    size_type i2 = get_bucket_index(last.m_node->data);

    if (i1 == i2)
    {
        hlist.set_header(m_bucket[i1]);
        hlist.erase(first.m_node, last.m_node);
        update_bucket(i1);
    }
    else
    {
        hlist.set_header(m_bucket[i1]);
        hlist.erase(first.m_node, NULL);
        update_bucket(i1);

        hlist.set_header(m_bucket[i2]);
        hlist.erase(m_bucket[i2], last.m_node);
        update_bucket(i2);

        while (i1 < i2)
        {
            erase_bucket(++i1);
        }
    }

}

void erase_bucket(size_type i)
{
    hlist.set_header(m_bucket[i]);

    hlist.clear();
    update_bucket(i);
}
void erase(const const_iterator& it)
{}
void erase(const_iterator first, const_iterator last)
{}

void resize(size_type n)
{
    size_type old_size = m_bucket.size();
    if (n > old_size)
    {
        size_type new_elements_count = get_next_prime(n);
        if (new_elements_count > old_size)
        {
            vector<pointer> tmp(new_elements_count, 0);
            for (size_type i = 0; i < old_size; i++)
                while (pointer first = m_bucket[i])
                {
                    size_type bucket_index = m_hash(m_get_key(first->data)) % new_elements_count;
                    m_bucket[i] = first->next;
                    first->next = tmp[bucket_index];
                    tmp[bucket_index] = first;
                }
            m_bucket.swap(tmp);
        }
    }
}

Hash hash_function() const
{
    return m_hash;
}

EqualKey key_eq() const
{
    return m_equal_key;
}

allocator_type get_allocator() const
{
    return m_alloc;
}

//    Construct and insert element (public member function )
//emplace

//    Construct and insert element with hint (public member function )
//emplace_hint

void clear()
{
    for (size_type i = 0; i < m_bucket.size(); i++)
    {
        hlist.set_header(m_bucket[i]);
        hlist.clear();
    }
    m_bucket.clear();
}

void swap(Self& t)
{
    my::swap(m_hash, t.m_hash);
    my::swap(m_equal_key, t.m_equal_key);
    my::swap(m_get_key, t.m_get_key);
    my::swap(m_alloc, t.m_alloc);
    my::swap(m_bucket, t.m_bucket);
    my::swap(hlist, t.hlist);
}

size_type get_bucket_index(const key_type& key) const
{
    return m_hash(key) % m_bucket.size();
}
size_type get_bucket_index(const T& x) const
{
    return m_hash(m_get_key(x)) % m_bucket.size();
}

//    Return load factor (public member function)
//load_factor

//    Get or set maximum load factor (public member function )
//max_load_factor

//    Set number of buckets (public member function )
//rehash

//    Request a capacity change (public member function)
//reserve

private:
    Hash m_hash;
    EqualKey m_equal_key;
    ExtractKey m_get_key;
    allocator_type m_alloc;
    vector<hash_node<T>*> m_bucket;
    mutable hash_list<T, ExtractKey, EqualKey> hlist;
};

//Non-member function overloads
//
//operators (unordered_map)
//    Relational operators for unordered_map (function template )
//
//swap (unordered_map)
//    Exchanges contents of two unordered_map containers (function template )
}   // namespace my

#endif /* end of include guard: MYHASHTABLE_H */
