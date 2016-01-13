#ifndef MYPAIR_H
#define MYPAIR_H

namespace my
{

template <class T1, class T2>
struct pair
{
    typedef T1 key_type;
    typedef T2 value_type;

    T1 first;
    T2 second;
    
    pair(): first(T1()), second(T2()) {}
    pair(const T1& a, const T2& b): first(a), second(b) {}

    template <class U1, class U2>
    pair(const pair<U1, U2>& other): first(other.first), second(other.second) {}
};

template <class T1, class T2>
pair<T1, T2> make_pair(const T1& a, const T2& b)
{
    return pair<T1, T2>(a, b);
}

template <class T1, class T2>
bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return x.first == y.first
        && x.second == y.second;
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return !(x == y);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return x.first > y.first
        || (x.first == y.first && x.second > y.second);
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return !(x < y);
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return y > x;
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return !(x > y);
}

}   // namespace my

#endif /* end of include guard: MYPAIR_H */
