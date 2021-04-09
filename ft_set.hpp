#ifndef FT_SET_HPP
# define FT_SET_HPP

# include "ft_rbtree.hpp"
# include "ft_function.hpp"
# include <memory>
# include <functional>
# include <utility>

/**
 * menber functions
 * 
 * iterator:
 *      begin       clear
 *      end         clear
 *      rbegin      clear
 *      rend        clear
 * 
 * capacity:
 *      empty       clear
 *      size        clear
 *      max_size    clear
 * 
 * modifiers:
 *      insert      clear
 *      erase       clear
 *      swap        clear
 *      clear       clear
 * 
 * observers:
 *      key_comp    clear
 *      value_comp  clear
 * 
 * operations:
 *      find        clear
 *      count       clear
 *      lower_bound clear
 *      upper_bound clear
 *      equal_range clear
 */

namespace ft
{

template<typename Key, typename Compare = std::less<Key>,
    typename Alloc = std::allocator<Key> >
class Set
{
public:
    typedef Key                                         key_type;
    typedef Key                                         value_type;
    typedef Compare                                     key_compare;
    typedef Compare                                     value_compare;
    typedef Alloc                                       allocator_type;

private:
    typedef typename std::allocator<Alloc>::template
        rebind<key>::other                              Key_allocator;
    typedef ft::Rbtree<key_type, value_type, ft::Identity<value_type>,
        key_compare, Key_allocator>                     Rep_type;

public:
    typedef typename Key_allocator::pointer             pointer;
    typedef typename Key_allocator::const_pointer       const_pointer;
    typedef typename Key_allocator::reference           reference;
    typedef typename Key_allocator::const_reference     const_reference;
    typedef typename Rep_type::const_iterator           iterator;
    typedef typename Rep_type::const_iterator           const_iterator;
    typedef typename Rep_type::const_reverse_iterator   reverse_iterator;
    typedef typename Rep_type::const_reverse_iterator   const_reverse_iterator;
    typedef typename Rep_type::difference_type          difference_type;

    Set() : m_t() {}
    Set(const Compare& comp, const allocator_type& a = allocator_type())
        : m_t(comp, Key_allocator(a)) {}
    Set(const Set& x) : m_t(x.m_t) {}

    template<typename InputIter>
    Set(InputIter first, InputIter last) : m_t()
    { m_t.m_insert_unique(first, last); }

    template<typename InputIter>
    Set(InputIter first, InputIter last, const Compare& comp,
        const allocator_type& a = allocator_type()) : m_t(comp, Key_allocator(a))
    { m_t.m_insert_unique(first, last); }

    ~Set() {}

    Set& operator=(const Set& x)
    { m_t = x.m_t; return *this; }

    iterator begin()
    { return m_t.begin(); }

    const_iterator begin() const
    { return m_t.begin(); }

    iterator end()
    { return m_t.end(); }

    const_iterator end() const
    { return m_t.end(); }

    reverse_iterator rbegin()
    { return m_t.rbegin(); }

    const_reverse_iterator rbegin() const
    { return m_t.rbegin(); }

    reverse_iterator rend()
    { return m_t.rend(); }

    const_reverse_iterator rend() const
    { return m_t.rend(); }

    bool empty() const
    { return m_t.empty(); }

    size_t size() const
    { return m_t.size(); }

    size_t max_size() const
    { return m_t.max_size(); }

    std::pair<iterator, bool> insert(const value_type& x)
    {
        std::pair<typename Rep_type::iterator, bool> tmp = 
            m_t.m_insert_unique(x);
        return std::pair<iterator, bool>(tmp.first, tmp.second);
    }

    iterator insert(iterator pos, const value_type& x)
    { return m_t.m_insert_unique(pos, x); }

    template<typename InputIter>
    void insert(InputIter first, InputIter last)
    { m_t.m_insert_unique(first, last); }

    void erase(iterator pos)
    { m_t.erase(pos); }

    size_t erase(const key_type& x)
    { return m_t.erase(x); }

    void erase(iterator first, iterator last)
    { m_t.erase(first, last); }

    void swap(Set& x)
    { m_t.swap(x.m_t); }

    void clear()
    { m_t.clear(); }

    key_compare key_comp() const
    { return m_t.key_comp(); }

    value_compare value_comp() const
    { return m_t.key_comp(); }

    iterator find(const key_type& x)
    { return m_t.find(x); }

    const_iterator find(const key_type& x) const
    { return m_t.find(x); }

    size_t count(const key_type& x) const
    { return m_t.find(x) == m_t.end() ? 0 : 1; }

    iterator lower_bound(const key_type& x)
    { return m_t.lower_bound(x); }

    const_iterator lower_bound(const key_type& x) const
    { return m_t.lower_bound(x); }

    iterator upper_bound(const key_type& x)
    { return m_t.upper_bound(x); }
    
    const_iterator upper_bound(const key_type& x) const
    { return m_t.upper_bound(x); }

    std::pair<iterator, iterator> equal_range(const key_type& x)
    { return m_t.equal_range(x); }

    std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const
    { return m_t.equal_range(x); }

    template<typename _Key, typename _Compare, typename _Alloc>
    friend bool operator==(const Set<_Key, _Compare, _Alloc>& x,
	    const Set<_Key,_Compare, _Alloc>& y)
    { return x.m_t == y.m_t; }

    template<typename _Key, typename _Compare, typename _Alloc>
    friend bool operator<(const Set<_Key,_Compare, _Alloc>& x,
	    const Set<_Key,_Compare, _Alloc>& y)
    { return x.m_t < y.m_t; }

private:
    Rep_type m_t;
};

template<typename _Key, typename _Compare, typename _Alloc>
inline bool operator!=(const Set<_Key,_Compare, _Alloc>& x,
    const Set<_Key,_Compare, _Alloc>& y)
{ return !(x.m_t == y.m_t); }

template<typename _Key, typename _Compare, typename _Alloc>
inline bool operator>(const Set<_Key,_Compare, _Alloc>& x,
    const Set<_Key,_Compare, _Alloc>& y)
{ return y < x; }

template<typename _Key, typename _Compare, typename _Alloc>
inline bool operator<=(const Set<_Key,_Compare, _Alloc>& x,
    const Set<_Key,_Compare, _Alloc>& y)
{ return !(y < x); }

template<typename _Key, typename _Compare, typename _Alloc>
inline bool operator>=(const Set<_Key,_Compare, _Alloc>& x,
    const Set<_Key,_Compare, _Alloc>& y)
{ return !(x < y); }

template<typename Key, typename Compare, typename Alloc>
inline void swap(Set<Key, Compare, Alloc>& x, Set<Key, Compare, Alloc>& y)
{ x.swap(y); }
} // namespace ft

#endif /* FT_SET_HPP */