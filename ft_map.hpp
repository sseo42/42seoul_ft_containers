#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include <memory>
#include <functional>
#include <utility>

namespace ft
{

template<typename Key, typename Tp, typename Compare = std::less<Key>,
    typename Alloc = std::allocator<std::pair<const Key, Tp> > >
class Map
{
public:
    typedef Key                                     key_type;
    typedef Tp                                      mapped_type;
    typedef std::pair<const Key, Tp>                value_type;
    typedef Compare                                 key_compare;
    typedef Alloc                                   allocator_type;


};
} // namespace ft

#endif /* FT_MAP_HPP */