#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP

# include "ft_library.hpp"

namespace ft
{

template<typename T1, typename T2>
struct Pair
{
    typedef T1                  first_type;
    typedef T2                  second_type;

    Pair() : first(), second() {}
    Pair(const T1& a, const T2& b) : first(a), second(b) {}

    template<typename U1, typename U2>
    Pair(const Pair<U1, U2>& p) : first(p.first), second(p.second) {}

    ~Pair() {}

    template<typename U1, typename U2>
    Pair& operator=(const Pair<typename ft::enable_if<(ft::is_same<U1, T1>::value), U1>::type,
        typename ft::enable_if<(ft::is_same<U2, T2>::value), U2>::type>& p)
    { first = p.first; second = p.second; return *this; }

    T1 first;
    T2 second;
};

template<typename T1, typename T2>
Pair<T1, T2> make_pair(T1 a, T2 b)
{ return Pair<T1, T2>(a, b); }

template<typename T1, typename T2>
inline bool operator==(const Pair<T1, T2>& x, const Pair<T1, T2>& y)
{ return (x.first == y.first && x.second == y.second); }

template<typename T1, typename T2>
inline bool operator<(const Pair<T1, T2>& x, const Pair<T1, T2>& y)
{ return (x.first < y.first || (!(y.first < x.first) && x.second < y.second)); }

template<typename T1, typename T2>
inline bool operator!=(const Pair<T1, T2>& x, const Pair<T1, T2>& y)
{ return !(x == y); }

template<typename T1, typename T2>
inline bool operator>(const Pair<T1, T2>& x, const Pair<T1, T2>& y)
{ return y < x; }

template<typename T1, typename T2>
inline bool operator<=(const Pair<T1, T2>& x, const Pair<T1, T2>& y)
{ return !(y < x); }

template<typename T1, typename T2>
inline bool operator>=(const Pair<T1, T2>& x, const Pair<T1, T2>& y)
{ return !(x < y); }
} // namespace ft

#endif /* FT_PAIR_HPP */