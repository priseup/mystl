#ifndef MYALGO_H
#define MYALGO_H

#include "mytypetraits.h"
#include "myiterator.h"

namespace my
{
template <class T> 
bool is_builtin(T)
{
    typedef typename TypeTraits<T>::is_pod_type is_pod_data;

    return _is_builtin_imple(is_pod_data());
}

bool _is_builtin_imple(false_type)
{
    return false;
}

bool _is_builtin_imple(true_type)
{
    return true;
}

template <class T>
inline void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class InputIterator>
typename IteratorTraits<InputIterator>::difference_type
_distance(InputIterator first, InputIterator last, input_tag)
{
    typename IteratorTraits<InputIterator>::difference_type n = 0;
    while (first != last)
    {
        ++first;
        n++;
    }

    return n;
}

template <class RandomIterator>
typename IteratorTraits<RandomIterator>::difference_type
_distance(RandomIterator first, RandomIterator last, random_tag)
{
    return last - first;
}

template <class Iterator>
typename IteratorTraits<Iterator>::difference_type
distance(Iterator first, Iterator last)
{
    typedef typename IteratorTraits<Iterator>::catagory _catagory;
    return _distance(first, last, _catagory());
}

template <class InputIterator, class Distance>
void _advance(InputIterator& it, Distance n, input_tag)
{
    while (n != 0)
    {
        ++it;
        --n;
    }
}

template <class BinputIterator, class Distance>
void _advance(BinputIterator& it, Distance n, binput_tag)
{
    while (n != 0)
    {
        if (n > 0)
        {
            ++it;
            --n;
        }
        else
        {
            --it;
            ++n;
        }
    }
}

template <class RandomIterator, class Distance>
void _advance(RandomIterator& it, Distance n, random_tag)
{
    it += n;
}

template <class Iterator, class Distance>
void advance(Iterator& it, Distance n)
{
    typedef typename IteratorTraits<Iterator>::catagory _catagory;
    _advance(it, n, _catagory());
}

template <class Iterator, class Distance>
void fill_n(Iterator it, Distance n)
{
    typedef typename IteratorTraits<Iterator>::value_type _C;
    typedef typename TypeTraits<_C>::is_pod_type is_pod_data;

    _fill_n(it, n, is_pod_data());
}

//void fill_n(char* p, size_t n)
//{
//    memset(p, 0, n);
//}
//
template <class InputIterator, class Distance>
void _fill_n(InputIterator it, Distance n, true_type)
{
    while (n--)
    {
        *it = 0;
        ++it;
    }
}

template <class InputIterator, class Distance>
void _fill_n(InputIterator it, Distance n, false_type)
{
    typedef typename IteratorTraits<InputIterator>::value_type C;
    while (n--)
    {
        *it = C();
        ++it;
    }
}

template <class Iterator>
void fill_n(Iterator first, Iterator last)
{
    typedef typename IteratorTraits<Iterator>::value_type _C;
    typedef typename TypeTraits<_C>::is_pod_type is_pod_data;

    _fill_n(first, last, is_pod_data());
}

//void fill_n(char* p, size_t n)
//{
//    memset(p, 0, n);
//}
//
template <class InputIterator>
void _fill_n(InputIterator first, InputIterator last, true_type)
{
    typedef typename IteratorTraits<InputIterator>::value_type _C;
    for (; first != last; ++first)
    {
        *first = _C();
    }
}

template <class InputIterator>
void _fill_n(InputIterator first, InputIterator last, false_type)
{
    typedef typename IteratorTraits<InputIterator>::value_type _C;
    for (; first != last; ++first)
    {
        *first = 0;
    }
}


template <class OutputIterator, class InputIterator>
void fill(OutputIterator ot, InputIterator first, InputIterator last)
{
    typedef typename IteratorTraits<OutputIterator>::value_type _C;
    typedef typename TypeTraits<_C>::is_pod_type is_pod_data;

    _fill(ot, first, last, is_pod_data());
}

template <class OutputIterator, class InputIterator>
void _fill(OutputIterator ot, InputIterator first, InputIterator last, false_type)
{
    for (; first != last; ++first)
    {
        *ot = *first;
        ++ot;
    }
}

template <class OutputIterator, class InputIterator>
void _fill(OutputIterator ot, InputIterator first, InputIterator last, true_type)
{
    for (; first != last; ++first)
    {
        *ot = *first;
        ++ot;
    }
}

}   // namespace my
#endif /* end of include guard: MYALGO_H */
