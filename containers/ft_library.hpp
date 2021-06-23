#ifndef FT_LIBRARY_HPP
# define FT_LIBRARY_HPP

# include <stdlib.h>

namespace ft
{
template<typename T, typename U>
struct is_same { static const bool value = false; };
template<typename T>
struct is_same<T, T> { static const bool value = true; };

template<typename T>
struct is_integer { typedef struct FalseType type; };
template<>
struct is_integer<int> { typedef struct TrueType type; };
struct TrueType {};
struct FalseType {};

template<bool, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> { typedef T type; };

template<bool>
void do_throw() { }

template<>
void do_throw<true>() { abort(); }

template<typename T>
struct addressof_impl
{
    static inline T* f(T& v, long)
    {
        return reinterpret_cast<T*>(&const_cast<char&>(
            reinterpret_cast<const char&>(v)));
    }
    static inline T* f(T* v, int)
    {
        return v;
    }
};

template<typename T>
T* addressof(T& v) { return ft::addressof_impl<T>::f(v, 0); }

template<typename ForwardIter, typename Alloc>
void destroy(ForwardIter first, ForwardIter last, Alloc& alloc)
{
    for (; first != last; ++first)
    {
        alloc.destroy(ft::addressof(*first));
    }
}

template<typename T>
const T& max(const T& a, const T& b)
{
	return (a<b) ? b : a;
}

template<typename InputIterator1, typename InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1 != last1)
	{
		if (*first1 != *first2)
			return false;
		++first1; ++first2;
	}
	return true;
}

template<typename InputIterator1, typename InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first1 > *first2)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1; ++first2;
	}
	return (first2 != last2);
}

template<typename ForwardIt, typename T>
void fill(ForwardIt first, ForwardIt last, const T& value)
{
    for (; first != last; ++first)
        *first = value;
}

template<class OutputIt, class Size, class T>
OutputIt fill_n(OutputIt first, Size count, const T& value)
{
    for (Size i = 0; i < count; i++) {
        *first++ = value;
    }
    return first;
}

} // namespace ft

#endif /*FT_LIBRARY_HPP */
