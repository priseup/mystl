#ifndef MYCONSTRUCT_H
#define MYCONSTRUCT_H

#include "myiterator.h"
#include <new>

namespace my
{
template <class Iterator>
inline
typename IteratorTraits<Iterator>::value_type*
value_type(Iterator it)
{
    typedef typename IteratorTraits<Iterator>::value_type C;
    return static_cast<C*>(0);
}

template <class T1, class T2>
inline void construct(T1* p, const T2& x)
{
    new(p) T1(x); // placement new operator 
}

template <class T1, class T2>
inline void construct(T1 first, T2 last, const T2& x)
{
    for (; first != last; ++first)
        construct(&*first, x);
}

template <class T>
inline void destroy(T* p)
{
    p->~T();
}

template <class Iterator>
inline void destroy(Iterator first, Iterator last)
{
    _destroy(first, last, value_type(first));
}

template <class Iterator, class T>
inline void _destroy(Iterator first, Iterator last, T*)
{
    typedef typename TypeTraits<T>::has_trivial_destructor C;
    _destroy_imple(first, last, C());
}

template <class Iterator>
inline void _destroy_imple(Iterator first, Iterator last, false_type)
{
    for (; first != last; ++first)
    {
        destroy(&*first);
    }
}

template <class Iterator>
inline void _destroy_imple(Iterator first, Iterator last, true_type)
{
}
}   // namespace my
#endif /* end of include guard: MYCONSTRUCT_H */

//namespace my
//{
//template <class Iterator>
//void _construct(Iterator it)
//{
//    typedef typename IteratorTraits<Iterator>::value_type T;
//    &(*it)->T();
//}
//
//template <class Iterator>
//void _construct(Iterator first, Iterator last)
//{
//    typedef typename IteratorTraits<Iterator>::value_type T;
//    for (; first != last; ++first)
//        &(*first)->T();
//}
//
//template <class Iterator, class T>
//void _construct(Iterator it, const T& x)
//{
//    &(*it)->T(x);
//}
//
//template <class Iterator>
//void _destroy(Iterator it)
//{
//    typedef typename IteratorTraits<Iterator>::value_type T;
//    &(*it)->~T();
//}
//
//template <class Iterator>
//void _destroy(Iterator first, Iterator last)
//{
//    typedef typename IteratorTraits<Iterator>::value_type T;
//    for (; first != last; ++first)
//        &(*first)->~T(); 
//}
//
//}       // namespace my
