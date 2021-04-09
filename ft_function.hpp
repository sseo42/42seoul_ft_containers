#ifndef FT_FUNCTION_HPP
# define FT_FUNCTION_HPP

# include <functional>
# include <iostream>

namespace ft
{
template<typename Pair>
struct Select1st : public std::unary_function<Pair, typename Pair::first_type>
{
    typename Pair::first_type& operator()(Pair& x) const
    { return x.first; }

    const typename Pair::first_type& operator()(const Pair& x) const
    { return x.first; }
};

template<typename Tp>
struct Identity : public std::unary_function<Tp, Tp>
{
    Tp& operator()(Tp& x) const
    { return x; }

    const Tp& operator()(const Tp& x) const
    { return x; }
};
} // namespace ft

#endif /*FT_FUNCTION_HPP */