#ifndef MYALGORITHM_H
#define MYALGORITHM_H

namespace my
{

// 泛型编程与STL P199: 11.1 find function
template <class InputIterator, class EqualityComparable>
InputIterator find(InputIterator first, InputIterator last,
        const EqualityComparable& value)
{}

template <class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last,
        Predicate pred)
{}

template <class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
{}

template <class ForwardIterator, class BinaryPredicate>
ForwardIterator find_if(ForwardIterator first, ForwardIterator last,
        BinaryPredicate binary_pred)
{}

template <class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator flast1,
        ForwardIterator first2, ForwardIterator last2)
{}

template <class InputIterator,
    class ForwardIterator,
    class BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator flast1,
        ForwardIterator first2, ForwardIterator last2,
        BinaryPredicate comp)
{}

template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
        ForwardIterator2 first2, ForwardIterator2 last2)
{}

template <class ForwardIterator1, class ForwardIterator2,
    class BinaryPredicate>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
        ForwardIterator2 first2, ForwardIterator2 last2,
        BinaryPredicate binary_pred)
{}

template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
        ForwardIterator2 first2, ForwardIterator2 last2)
{}

template <class ForwardIterator1, class ForwardIterator2,
    class BinaryPredicate>
ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
        ForwardIterator2 first2, ForwardIterator2 last2,
        BinaryPredicate binary_pred)
{}

template <class ForwardIterator, class Integer, class T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
        Integer count, const T& value)
{}

template <class ForwardIterator, class Integer, class T,
    class BinaryPredicate>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
        Integer count, const T& value, BinaryPredicate binary_pred)
{}

template <class InputIterator, class EqualityComparable>
typename IteratorTraits<InputIterator>::difference_type
count(InputIterator first, InputIterator last,
        const EqualityComparable& value)
{}

template <class InputIterator, class EqualityComparable, class Size>
typename IteratorTraits<InputIterator>::difference_type
count(InputIterator first, InputIterator last,
        const EqualityComparable& value,
        Size& n)
{}

template <class InputIterator, class Predicate>
typename IteratorTraits<InputIterator>::difference_type
count_if(InputIterator first, InputIterator last, Predicate pred)
{}

template <class InputIterator, class Predicate, class Size>
typename IteratorTraits<InputIterator>::difference_type
count_if(InputIterator first, InputIterator last,
        Predicate pred, Size& n)
{}

template <class InputIterator, class UnaryFunction>
UnaryFunction for_each(InputIterator first, InputIterator last,
        UnaryFunction f)
{}

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2)
{}

template <class InputIterator1, class InputIterator2,
    class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, BinaryPredicate binary_pred)
{}

template <class InputIterator1, class InputIterator2>
pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2)
{}

template <class InputIterator1, class InputIterator2,
    class BinaryPredicate>
pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, BinaryPredicate binary_pred)
{}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2)
{}

template <class InputIterator1, class InputIterator2,
    class BinaryPredicate>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2,
        BinaryPredicate comp)
{}

template <class LessThanComparable>
const LessThanComparable& max(const LessThanComparable& a,
        const LessThanComparable& b)
{}

template <class T, class BinaryPredicate>
const T& max(const T& a, const T& b, BinaryPredicate comp)
{}

template <class ForwardIterator>
ForwardIterator
min_element(ForwardIterator first, ForwardIterator last)
{}

template <class ForwardIterator, class BinaryPredicate>
ForwardIterator
min_element(ForwardIterator first, ForwardIterator last,
        BinaryPredicate comp)
{}

template <class ForwardIterator>
ForwardIterator
max_element(ForwardIterator first, ForwardIterator last)
{}

template <class ForwardIterator, class BinaryPredicate>
ForwardIterator
max_element(ForwardIterator first, ForwardIterator last,
        BinaryPredicate comp)
{}

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last,
        OutputIterator result)
{}

template <class InputIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy(InputIterator1 first, InputIterator1 last,
        BidirectionalIterator2 result)
{}

template <class Assignable>
void swap(Assignable& a, Assignable& b)
{}

template <class ForwardIterator1, class ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b)
{}

template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1,
        ForwardIterator2 first2)
{}

template <class InputIterator, class OutputIterator, class UnaryFunction>
OutputIterator transform(InputIterator first, InputIterator last,
        OutputIterator result, UnaryFunction op)
{}

template <class InputIterator1, class OutputIterator2, 
    class OutputIterator, class BinaryFunction>
OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, OutputIterator result,
        BinaryFunction binary_op)
{}

template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last,
        const T& old_value, const T& new_value)
{}

template <class ForwardIterator, class Predicate, class T>
void replace(ForwardIterator first, ForwardIterator last,
        Predicate pred, const T& new_value)
{}

template <class InputIterator, class OutputIterator, class T>
OutputIterator replace_copy(InputIterator first, InputIterator last,
        OutputIterator result, 
        const T& old_value, const T& new_value)
{}

template <class InputIterator, class OutputIterator,
         class Predicate, class T>
OutputIterator replace_copy_if(InputIterator first, InputIterator last,
        OutputIterator result, Predicate pred,
        const T& new_value)
{}

template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value)
{}

template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value)
{}

template <class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen)
{}

template <class OutputIterator, class Size, class Generator>
OutputIterator generate_n(OutputIterator first, Size n, const Generator gen)
{}

template <class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value)
{}

template <class ForwardIterator, class Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
{}

template <class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last,
        OutputIterator result, const T& value)
{}

template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last,
        OutputIterator result, Predicate pred)
{}

template <class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last)
{}

template <class ForwardIterator, class BinaryPredicate>
ForwardIterator unique(ForwardIterator first, ForwardIterator last,
        BinaryPredicate binary_pred)
{}

template <class InputIterator, class OutputIterator>
OutputIterator unique_copy(InputIterator first, InputIterator last,
        OutputIterator result)
{}

template <class InputIterator, class OutputIterator, class BinaryPredicate>
OutputIterator unique_copy(InputIterator first, InputIterator last,
        OutputIterator result, BinaryPredicate binary_pred)
{}

template <class BidirectionalIterator>
void reverse(BidirectionalIterator first, BidirectionalIterator last)
{}

template <class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last,
        OutputIterator result)
{}

template <class ForwardIterator>
inline void rotate(ForwardIterator first, ForwardIterator middle,
        ForwardIterator last)
{}

template <class ForwardIterator, class OutputIterator>
OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle,
        ForwardIterator last, OutputIterator result)
{}

template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last)
{}

template <class BidirectionalIterator, class StrictWeakOrdering>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last, StrictWeakOrdering comp)
{}

template <class BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last)
{}

template <class BidirectionalIterator, class StrictWeakOrdering>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last, StrictWeakOrdering comp)
{}

template <class BidirectionalIterator, class Predicate>
BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
{}

template <class ForwardIterator, class Predicate>
ForwardIterator stable_partition(ForwardIterator first, ForwardIterator last, Predicate pred)
{}

template <class RandomAccessIterator>
void random_shuffle(RandomAccessIterator first,
        RandomAccessIterator last)
{}

template <class RandomAccessIterator, class RandomNumberGenerator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
        RandomNumberGenerator& rand)
{}

template <class InputIterator, class RandomAccessIterator>
RandomAccessIterator random_sample(InputIterator first, InputIterator last,
        RandomAccessIterator ofirst, RandomAccessIterator olast)
{}

template <class InputIterator, class RandomAccessIterator, class RandomNumberGenerator>
RandomAccessIterator random_sample(InputIterator first, InputIterator last,
        RandomAccessIterator ofirst, RandomAccessIterator olast,
        RandomNumberGenerator& rand)
{}

template <class ForwardIterator, class OutputIterator, class Distance>
OutputIterator random_sample_n(ForwardIterator first, ForwardIterator last,
        OutputIterator out, Distance n)
{}

template <class ForwardIterator, class OutputIterator,
    class Distance, class RandomNumberGenerator>
OutputIterator random_sample_n(ForwardIterator first, ForwardIterator last,
        OutputIterator out, Distance n, RandomNumberGenerator& rand)
{}

template <class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init)
{}

template <class InputIterator, class T, class BinaryFunction>
T accumulate(InputIterator first, InputIterator last, T init, BinaryFunction binary_op)
{}

template <class InputIterator1, class InputIterator2, class T>
T inner_product(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, T init)
{}

template <class InputIterator1, class InputIterator2, class T
    class BinaryFunction1, class BinaryFunction2>
T inner_product(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, T init,
        BinaryFunction1 binary_op1, BinaryFunction2 binary_op2)
{}

template <class InputIterator, class OutputIterator>
OutputIterator partial_sum(InputIterator first, InputIterator last,
        OutputIterator result)
{}

template <class InputIterator, class OutputIterator,
    class BinaryFunction>
OutputIterator partial_sum(InputIterator first, InputIterator last,
        OutputIterator result, BinaryFunction binary_op)
{}

// 泛型编程与STL P287: 12.10.4 adjacent_difference function

}   // namespace my

#endif /* end of include guard: MYALGORITHM_H */
