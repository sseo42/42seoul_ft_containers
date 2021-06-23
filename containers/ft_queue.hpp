#ifndef FT_QUEUE_HPP
# define FT_QUEUE_HPP

# include "ft_deque.hpp"

/**
 * member functions
 *      empty       clear
 *      size        clear
 *      front       clear
 *      back        clear
 *      push        clear
 *      pop         clear
 */

namespace ft
{
template< typename Tp, typename Sequence = ft::Deque<Tp> >
class Queue
{
    /* friend zone */
public:
    typedef typename Sequence::value_type           value_type;
    typedef typename Sequence::reference            reference;
    typedef typename Sequence::const_reference      const_reference;
    typedef Sequence                                constainter_type;

    Queue(const Sequence& c = Sequence()) : c(c) {}
    
    bool empty() const
    { return c.empty(); }

    size_t size() const
    { return c.size(); }

    reference front()
    { return c.front(); }

    const reference front() const
    { return c.front(); }

    reference back()
    { return c.back(); }

    const reference back() const
    { return c.back(); }

    void push(const value_type& x)
    { c.push_back(x); }

    void pop()
    { c.pop_front(); }

    Sequence c;
};

template<typename Tp, typename Seq>
inline bool operator==(const Queue<Tp, Seq>& x, const Queue<Tp, Seq>& y)
{ return (x.c == y.c); }

template<typename Tp, typename Seq>
inline bool operator!=(const Queue<Tp, Seq>& x, const Queue<Tp, Seq>& y)
{ return !(x.c == y.c); }

template<typename Tp, typename Seq>
inline bool operator<(const Queue<Tp, Seq>& x, const Queue<Tp, Seq>& y)
{ return (x.c < y.c); }

template<typename Tp, typename Seq>
inline bool operator>(const Queue<Tp, Seq>& x, const Queue<Tp, Seq>& y)
{ return (y.c < x.c); }

template<typename Tp, typename Seq>
inline bool operator<=(const Queue<Tp, Seq>& x, const Queue<Tp, Seq>& y)
{ return !(y.c < x.c); }

template<typename Tp, typename Seq>
inline bool operator>=(const Queue<Tp, Seq>& x, const Queue<Tp, Seq>& y)
{ return !(x.c < y.c); }
} // namespace ft

#endif /* FT_QUEUE_HPP */