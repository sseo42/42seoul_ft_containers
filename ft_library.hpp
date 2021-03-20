#ifndef FT_LIBRARY_HPP
# define FT_LIBRARY_HPP

# include <stdlib.h>
#include <iostream>

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
} // namespace ft

#endif /*FT_PIBRARY_HPP */