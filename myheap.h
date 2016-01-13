
#ifndef MYHEAP_H
#define MYHEAP_H

#include "myfunction.h"
#include "myiterator.h"

namespace my
{

template <class RandomIterator>
void percolate_up(RandomIterator it, RandomIterator first)
{
    typename IteratorTraits<RandomIterator>::value_type v = *it;
    RandomIterator parent = first + (it - first - 1) / 2;

    while (parent > first)
    {
        if (*parent < v)
        {
            *it = *parent;

            it = parent;
            parent = first + (it - first - 1) / 2;
        }
        else
            break;
    }

    if (*parent < v)
    {
        *it = *parent;
        it = parent;
    }

    *it = v;
}

template <class RandomIterator>
void percolate_down(RandomIterator first, RandomIterator it, RandomIterator end)
{
    typename IteratorTraits<RandomIterator>::size_type n = distance(first, it);
    RandomIterator Child = first + 2 * n + 1;
    typename IteratorTraits<RandomIterator>::value_type v = *it;

    while (Child < end)
    {
        if (Child + 1 >= end)
        {
            if (v < *Child)
            {
                *it = *Child;

                it = Child;
                n = distance(first, it);
                Child = first + 2 * n + 1;
            }
            else
                break;
        }
        else
        {
           if (*Child < *(Child + 1))
               ++Child;
           if (v < *Child)
           {
                *it = *Child;

                it = Child;
                n = distance(first, it);
                Child = first + 2 * n + 1;
           }
           else
               break;
        }
    }
    *it = v;
}

template <class RandomIterator>
void make_heap(RandomIterator first, RandomIterator last)
{
    typename IteratorTraits<RandomIterator>::size_type n = distance(first, last);

    RandomIterator it = first + (n - 1) / 2;
    while (it >= first)
    {
        percolate_down(first, it, last);
        --it;
    }
}

template <class RandomIterator>
void pop_heap(RandomIterator first, RandomIterator last)
{
    swap(*first, *--last);
    percolate_down(first, first, last);
}

template <class RandomIterator>
void push_heap(RandomIterator first, RandomIterator last)
{
    percolate_up(last - 1, first);
}

template <class RandomIterator>
void sort_heap(RandomIterator first, RandomIterator last)
{
    while (first < last)
    {
        pop_heap(first, last);
        --last;
    }
}

//========================================================================================================
template <class RandomIterator, class Comp>
void percolate_up(RandomIterator it, RandomIterator first, Comp c)
{
    typename IteratorTraits<RandomIterator>::value_type v = *it;
    RandomIterator parent = first + (it - first - 1) / 2;

    while (parent > first)
    {
        if (c(*parent, v))
        {
            *it = *parent;

            it = parent;
            parent = first + (it - first - 1) / 2;
        }
        else
            break;
    }

    if (c(*parent, v))
    {
        *it = *parent;
        it = parent;
    }

    *it = v;
}

template <class RandomIterator, class Comp>
void percolate_down(RandomIterator first, RandomIterator it, RandomIterator end, Comp c)
{
    typename IteratorTraits<RandomIterator>::size_type n = distance(first, it);
    RandomIterator Child = first + 2 * n + 1;
    typename IteratorTraits<RandomIterator>::value_type v = *it;

    while (Child < end)
    {
        if (Child + 1 >= end)
        {
            if (c(v, *Child))
            {
                *it = *Child;

                it = Child;
                n = distance(first, it);
                Child = first + 2 * n + 1;
            }
            else
                break;
        }
        else
        {
           if (c(*Child, *(Child + 1)))
               ++Child;
           if (c(v, *Child))
           {
                *it = *Child;

                it = Child;
                n = distance(first, it);
                Child = first + 2 * n + 1;
           }
           else
               break;
        }
    }
    *it = v;
}

template <class RandomIterator, class Comp>
void make_heap(RandomIterator first, RandomIterator last, Comp c)
{
    typename IteratorTraits<RandomIterator>::size_type n = distance(first, last);

    RandomIterator it = first + (n - 1) / 2;
    while (it >= first)
    {
        percolate_down(first, it, last, c);
        --it;
    }
}

template <class RandomIterator, class Comp>
void pop_heap(RandomIterator first, RandomIterator last, Comp c)
{
    swap(*first, *--last);
    percolate_down(first, first, last, c);
}

template <class RandomIterator, class Comp>
void push_heap(RandomIterator first, RandomIterator last, Comp c)
{
    percolate_up(last - 1, first, c);
}

template <class RandomIterator, class Comp>
void sort_heap(RandomIterator first, RandomIterator last, Comp c)
{
    while (first < last)
    {
        pop_heap(first, last, c);
        --last;
    }
}

}   // namespace my

#endif /* end of include guard: MYHEAP_H */
