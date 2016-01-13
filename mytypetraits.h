#ifndef TYPETRAITS_H
#define TYPETRAITS_H

namespace my
{
struct true_type {};
struct false_type {};

template <class C>
struct TypeTraits
{
    typedef false_type has_trivial_default_constructor;
    typedef false_type has_trivial_copy_constructor;
    typedef false_type has_trivial_assignment_constructor;
    typedef false_type has_trivial_destructor;
    typedef false_type is_pod_type;
};

template <>
struct TypeTraits<bool>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<char>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<signed char>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<unsigned char>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

//template <>
//struct TypeTraits<wchar_t>
//{
//    typedef true_type has_trivial_default_constructor;
//    typedef true_type has_trivial_copy_constructor;
//    typedef true_type has_trivial_assignment_constructor;
//    typedef true_type has_trivial_destructor;
//    typedef true_type is_pod_type;
//};

template <>
struct TypeTraits<short>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<unsigned short>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<int>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<unsigned int>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<long>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<unsigned long>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<long long>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<unsigned long long>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<float>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <>
struct TypeTraits<double>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <class C>
struct TypeTraits<C*>
{
    typedef true_type has_trivial_default_constructor;
    typedef true_type has_trivial_copy_constructor;
    typedef true_type has_trivial_assignment_constructor;
    typedef true_type has_trivial_destructor;
    typedef true_type is_pod_type;
};

template <class C>
struct IntegerTraits
{
    typedef false_type is_integer;
};

template <>
struct IntegerTraits<bool>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<char>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<signed char>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<unsigned char>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<short>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<unsigned short>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<int>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<unsigned int>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<long>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<unsigned long>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<long long>
{
    typedef true_type is_integer;
};

template <>
struct IntegerTraits<unsigned long long>
{
    typedef true_type is_integer;
};
}   // namespace my

#endif /* end of include guard: TYPETRAITS_H */
