#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "myiterator.h"
#include "mydeque.h"
#include "myvector.h"
#include "myfunction.h"
#include "myheap.h"

namespace my
{

template <class T, class Sequence = deque<T> >
class queue
{
template <class T1, class S1>
friend bool operator==(const queue<T1, S1>& x, const queue<T1, S1>& y);
template <class T1, class S1>
friend bool operator<(const queue<T1, S1>& x, const queue<T1, S1>& y);

public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
    typedef typename Sequence::size_type size_type;

public:
    bool empty() const
    {
        return s.empty();
    }

    size_type size() const
    {
        return s.size();
    }

    void push(const T& x)
    {
        s.push_back(x);
    }

    void pop()
    {
        s.pop_front();
    }

    reference front()
    {
        return s.front();
    }

    const_reference front() const
    {
        return s.front();
    }

    reference back()
    {
        return s.back();
    }

    const_reference back() const
    {
        return s.back();
    }

private:
    Sequence s;
};

template <class T1, class S1>
bool operator==(const queue<T1, S1>& x, const queue<T1, S1>& y)
{
    return x.s == y.s;
}

template <class T1, class S1>
bool operator<(const queue<T1, S1>& x, const queue<T1, S1>& y)
{
    return x.s < y.s;
}

template <class T1, class S1>
bool operator!=(const queue<T1, S1>& x, const queue<T1, S1>& y)
{
    return !(x == y);
}

template <class T1, class S1>
bool operator>(const queue<T1, S1>& x, const queue<T1, S1>& y)
{
    return y < x;
}

template <class T1, class S1>
bool operator<=(const queue<T1, S1>& x, const queue<T1, S1>& y)
{
    return !(x > y);
}
template <class T1, class S1>
bool operator>=(const queue<T1, S1>& x, const queue<T1, S1>& y)
{
    return !(x < y);
}

template <class T, class Sequence = vector<T>, class Compare = less<T> >
class priority_queue
{
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
    typedef typename Sequence::size_type size_type;

public:
    priority_queue() {}
    priority_queue(const Compare& com): c(com) {}
    priority_queue(const Sequence& t, const Compare& com): s(t), c(com)
    {
        make_heap(s.begin(), s.end(), c);
    }

    template <class RandomIterator>
    priority_queue(RandomIterator first, RandomIterator last): s(first, last)
    {
        make_heap(s.begin(), s.end(), c);
    }

    template <class RandomIterator>
    priority_queue(RandomIterator first, RandomIterator last, const Compare& com): s(first, last), c(com)
    {
        make_heap(s.begin(), s.end(), c);
    }

    priority_queue(const priority_queue& pq): s(pq.s), c(pq.c)
    {
        make_heap(s.begin(), s.end(), c);
    }

    bool empty() const
    {
        return s.empty();
    }

    size_type size() const
    {
        return s.size();
    }

    reference top() 
    {
        return s.front();
    }

    const_reference top() const
    {
        return s.front();
    }

    void push(const T& x)
    {
        s.push_back(x);

        push_heap(s.begin(), s.end());
    }

    void pop()
    {
        pop_heap(s.begin(), s.end());
        s.pop_back();
    }

private:
    Sequence s;
    Compare c;
};

}   // namesapce my

#endif /* end of include guard: MYQUEUE_H */
