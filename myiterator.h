#ifndef ITERATOR_H
#define ITERATOR_H

#include "mytypetraits.h"
#include <stddef.h>
namespace my
{

struct input_tag {};
struct output_tag {};
struct binput_tag : input_tag {};
struct random_tag : binput_tag {};

template <class _catagory,
         class _T,
         class _reference = _T&,
         class _pointer = _T*,
         class _size_type = size_t,
         class _difference_type = ptrdiff_t>
struct Iterator
{
    typedef _catagory catagory;
    typedef _T value_type;
    typedef _reference reference;
    typedef _pointer pointer;
    typedef _size_type size_type;
    typedef _difference_type difference_type;
};

template <class Iterator>
struct IteratorTraits
{
    typedef typename Iterator::catagory catagory;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::size_type size_type;
};
template <class T>
struct IteratorTraits<T*>
{
    typedef random_tag catagory;
    typedef T& reference;
    typedef T value_type;
    typedef T* pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
};
template <class T>
struct IteratorTraits<const T*>
{
    typedef random_tag catagory;
    typedef const T& reference;
    typedef T value_type;
    typedef const T* pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
};

//template <class catagory>
//struct InputIterator : Iterator<>
//{};
//
//template <class catagory>
//struct OutputIterator : Iterator<>
//{};
//
//template <class >
//struct BinputIterator : Iterator<>
//{};
//
//template <class >
//struct RandomIterator : Iterator<>
//{};

template <class Iterator>
class my_reverse_iterator
{
public:
    typedef typename IteratorTraits<Iterator>::value_type value_type;
    typedef typename IteratorTraits<Iterator>::reference reference;
    typedef typename IteratorTraits<Iterator>::pointer pointer;

    typedef my_reverse_iterator self;
    my_reverse_iterator(): ss(0) {}
    my_reverse_iterator(Iterator t): ss(t) {}
    my_reverse_iterator(const self& t): ss(t.ss) {}
    template <class U>
    my_reverse_iterator(const my_reverse_iterator<U>& x): ss(static_cast<Iterator>(x.getSS())) {}

public:
    Iterator getSS() const {return ss;}

    self& operator++()
    {
        --ss;
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
        ++ss;
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
        return self(ss + n);
    }

    reference operator*()
    {
        Iterator temp(ss);
        return *--temp;
    }

    self operator+(int n)
    {
        return self(ss - n);
    }

    pointer operator->()
    {
        return &*ss;
    }

    bool operator!=(const self& t)
    {
        return ss != t.ss;
    }

private:
    Iterator ss;
};

}   // namespace my

#endif /* end of include guard: ITERATOR_H */
