#ifndef MYFUNCTION_H
#define MYFUNCTION_H

namespace my
{
template <class ret, class T>
struct unary_function
{
    typedef ret return_type;
    typedef T argument_type;
};

template <class ret, class T1, class T2>
struct binary_function
{
    typedef ret return_type;
    typedef T1 first_type;
    typedef T2 second_type;
};

template <class T>
struct logical_not: public unary_function<bool, T>
{
    bool operator()(const T& x) const
    {
        return !x;
    }
};

template <class T>
struct negate: public unary_function<T, T>
{
    T operator()(const T& x) const
    {
        return -x;
    }
};

template <class T>
struct logical_and: public binary_function<bool, T, T>
{
    bool operator()(const T& x, const T& y) const
    {
        return x && y;
    }
};

template <class T>
struct logical_or: public binary_function<bool, T, T>
{
    bool operator()(const T& x, const T& y) const
    {
        return x || y;
    }
};

template <class T>
struct equal: public binary_function<bool, T, T>
{
    bool operator()(const T& x, const T& y) const
    {
        return x == y;
    }
};

template <class T>
struct not_equal: public binary_function<bool, T, T>
{
    bool operator()(const T& x, const T& y) const
    {
        return x != y;
    }
};

template <class T>
struct less: public binary_function<bool, T, T>
{
    bool operator()(const T& x, const T& y) const
    {
        return x < y;
    }
};

template <class T>
struct greater: public binary_function<bool, T, T>
{
    bool operator()(const T& x, const T& y) const
    {
        return x > y;
    }
};

template <class T>
struct less_equal: public binary_function<bool, T, T>
{
    bool operator()(const T& x, const T& y) const
    {
        return x <= y;
    }
};

template <class T>
struct greater_equal: public binary_function<bool, T, T>
{
    bool operator()(const T& x, const T& y) const
    {
        return x >= y;
    }
};

template <class R, class T>
struct plus: public binary_function<R, T, T>
{
    R operator()(const T& x, const T& y) const
    {
        return x + y;
    }
};

template <class R, class T>
struct minus: public binary_function<R, T, T>
{
    R operator()(const T& x, const T& y) const
    {
        return x - y;
    }
};

template <class R, class T>
struct multiplies: public binary_function<R, T, T>
{
    R operator()(const T& x, const T& y) const
    {
        return x * y;
    }
};

template <class R, class T>
struct divides: public binary_function<R, T, T>
{
    R operator()(const T& x, const T& y) const
    {
        return x / y;
    }
};

template <class R, class T>
struct modulus: public binary_function<R, T, T>
{
    R operator()(const T& x, const T& y) const
    {
        return x % y;
    }
};

template <class _pair>
struct select1st: public unary_function<typename _pair::key_type, _pair>
{
    typename _pair::key_type operator()(const _pair& p) const
    {
        return p.first;
    }
};

template <class _pair>
struct select2nd: public unary_function<typename _pair::value_type, _pair>
{
    typename _pair::value_type operator()(const _pair& p) const
    {
        return p.second;
    }
};

template <class R, class T>
struct mem_fun: public binary_function<R, T, T>
{
};


}   // namespace my

#endif /* end of include guard: MYFUNCTION_H */
