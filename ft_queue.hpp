#ifndef FT_QUEUE_HPP
# define FT_QUEUE_HPP

# include "ft_deque.hpp"
# include <memory>
# include <iostream> //for test

/**
 * member functions
 *      empty
 *      size
 *      front
 *      back
 *      push
 *      pop
 */

namespace ft
{
template< typename Tp, typename Sequence = ft::Deque<Tp> >
class Queue
{
public:
    ft_queue(/* args */);
    ~ft_queue();
};
} // namespace ft

#endif /* FT_QUEUE_HPP */