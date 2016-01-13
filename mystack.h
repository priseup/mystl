#ifndef MYSTACK_H
#define MYSTACK_H

#include "mydeque.h"

namespace my
{

template <class T, class Sequence = deque<T> >
class stack
{
template <class T1, class S1>
friend bool operator==(const stack<T1, S1>& x, const stack<T1, S1>& y);
template <class T1, class S1>
friend bool operator<=(const stack<T1, S1>& x, const stack<T1, S1>& y);

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

    void pop()
    {
        s.pop_back();
    }

    void push(const T& x)
    {
        s.push_back(x);
    }

    reference top()
    {
        return s.back();
    }

    const_reference top() const
    {
        return s.back();
    }

private:
    Sequence s;
};

template <class T1, class S1>
bool operator==(const stack<T1, S1>& x, const stack<T1, S1>& y)
{
    return x.s == y.s;
}

template <class T1, class S1>
bool operator<(const stack<T1, S1>& x, const stack<T1, S1>& y)
{
    return x.s < y.s;
}

template <class T1, class S1>
bool operator!=(const stack<T1, S1>& x, const stack<T1, S1>& y)
{
    return !(x == y);
}

template <class T1, class S1>
bool operator>(const stack<T1, S1>& x, const stack<T1, S1>& y)
{
    return y < x;
}

template <class T1, class S1>
bool operator<=(const stack<T1, S1>& x, const stack<T1, S1>& y)
{
    return !(x > y);
}
template <class T1, class S1>
bool operator>=(const stack<T1, S1>& x, const stack<T1, S1>& y)
{
    return !(x < y);
}

}   // namespace my

#endif /* end of include guard: MYSTACK_H */
