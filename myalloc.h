#ifndef MYALLOC_H
#define MYALLOC_H

#include <stddef.h>
#include <stdlib.h>
#include "myconstruct.h"

namespace my
{
template <class T>
class alloc_t
{
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template <class U>
    alloc_t(const alloc_t<U>& other) {} // do nothing
    alloc_t() {}
    alloc_t(const alloc_t& cp) {}
    ~alloc_t() {}
    
    template <class U>
    struct rebind
    {
        typedef alloc_t<U> other;
    };

    pointer alloc(size_type n)
    {
        return (pointer)::malloc(n * sizeof (T));
    }

    pointer realloc(pointer p, size_type n)
    {
        return (pointer)::realloc(p, n);
    }

    void dealloc(pointer p)
    {
        ::free(p);
    }

    pointer address(reference x) const
    {
        return &x;
    }

    const_pointer address(const_reference x) const
    {
        return (const_pointer)&x;
    }

    size_type max_size() const
    {
        return size_type(-1) / sizeof (T);
    }

    void construct(pointer p, const T& x)
    {
        new(p) T(x);
    }

    void destroy(pointer p)
    {
        p->~T();
    }
};

template <class T, class Alloc>
struct AllocatorTraits
{
    typedef typename Alloc::template rebind<T>::other allocator_type;    // must have "template"
};

} // namespace my 

#endif /* end of include guard: MYALLOC_H */
