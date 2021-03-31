#ifndef FT_STACK_HPP
# define FT_STACK_HPP

# include "ft_deque.hpp"

/**
 * member functions
 *      empty       clear
 *      size        clear
 *      top         clear
 *      push        clear
 *      pop         clear
 */

namespace ft
{
template< typename Tp, typename Sequence = ft::Deque<Tp> >
class Stack
{
public:
    typedef typename Sequence::value_type           value_type;
    typedef typename Sequence::reference            reference;
    typedef typename Sequence::const_reference      const_reference;
    typedef Sequence                                constainter_type;

    Stack(const Sequence& c = Sequence()) : c(c) {}
    
    bool empty() const
    { return c.empty(); }

    size_t size() const
    { return c.size(); }

    reference top()
    { return c.back(); }

    const reference top() const
    { return c.back(); }

    void push(const value_type& x)
    { c.push_back(x); }

    void pop()
    { c.pop_back(); }

    Sequence c;
};

template<typename Tp, typename Seq>
inline bool operator==(const Stack<Tp, Seq>& x, const Stack<Tp, Seq>& y)
{ return (x.c == y.c); }

template<typename Tp, typename Seq>
inline bool operator!=(const Stack<Tp, Seq>& x, const Stack<Tp, Seq>& y)
{ return !(x.c == y.c); }

template<typename Tp, typename Seq>
inline bool operator<(const Stack<Tp, Seq>& x, const Stack<Tp, Seq>& y)
{ return (x.c < y.c); }

template<typename Tp, typename Seq>
inline bool operator>(const Stack<Tp, Seq>& x, const Stack<Tp, Seq>& y)
{ return (y.c < x.c); }

template<typename Tp, typename Seq>
inline bool operator<=(const Stack<Tp, Seq>& x, const Stack<Tp, Seq>& y)
{ return !(y.c < x.c); }

template<typename Tp, typename Seq>
inline bool operator>=(const Stack<Tp, Seq>& x, const Stack<Tp, Seq>& y)
{ return !(x.c < y.c); }
} // namespace ft

#endif /* FT_STACK_HPP */