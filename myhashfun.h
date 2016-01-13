#ifndef MYHASHFUN_H
#define MYHASHFUN_H
#include <stddef.h>

namespace my
{

size_t my_hash_string(const char* p)
{
    unsigned long s = 0;

    while (*p)
    {
        s = 5 * s + *p++;
    }

    return s;
}

template <class T>
struct hash
{ };

template <>
struct hash<char *>
{
    size_t operator()(const char* p) const
    {
        return my_hash_string(p);
    }
};

template <>
struct hash<const char *>
{
    size_t operator()(const char* p) const
    {
        return my_hash_string(p);
    }
};

template <>
struct hash<signed char>
{
    size_t operator()(unsigned char x) const
    {
        return x;
    }
};

template <>
struct hash<unsigned char>
{
    size_t operator()(unsigned char x) const
    {
        return x;
    }
};

template <>
struct hash<signed int>
{
    size_t operator()(unsigned int x) const
    {
        return x;
    }
};

template <>
struct hash<unsigned int>
{
    size_t operator()(unsigned int x) const
    {
        return x;
    }
};

template <>
struct hash<signed short>
{
    size_t operator()(unsigned short x) const
    {
        return x;
    }
};

template <>
struct hash<signed long>
{
    size_t operator()(unsigned long x) const
    {
        return x;
    }
};

template <>
struct hash<unsigned long>
{
    size_t operator()(unsigned long x) const
    {
        return x;
    }
};

}   // namespace my


#endif /* end of include guard: MYHASHFUN_H */
