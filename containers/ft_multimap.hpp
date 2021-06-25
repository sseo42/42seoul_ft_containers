#ifndef FT_MULTIMAP_HPP
# define FT_MULTIMAP_HPP

# include "ft_pair.hpp"
# include "ft_function.hpp"
# include "ft_rbtree.hpp"

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

template<typename Key, typename Tp, typename Compare = std::less<Key>,
    typename Alloc = std::allocator<ft::Pair<const Key, Tp> > >
class Multimap
{
public:
    typedef Key                                         key_type;
    typedef Tp                                          mapped_type;
    typedef ft::Pair<const Key, Tp>                     value_type;
    typedef Compare                                     key_compare;
    typedef Alloc                                       allocator_type;

    class value_compare : public std::binary_function<value_type, value_type, bool>
    {
    public:
        friend class Multimap<Key, Tp, Compare, Alloc>;

        bool operator()(const value_type& x, const value_type& y) const
        { return comp(x.first, y.first); }

    protected:
        value_compare(Compare c) : comp(c) {}

        Compare comp;
    };

private:
    typedef typename std::allocator<Alloc>::template
        rebind<value_type>::other                       Pair_allocator;
    typedef ft::Rbtree<key_type, value_type, ft::Select1st<value_type>,
        key_compare, Pair_allocator>                    Rep_type;

public:
    typedef typename Pair_allocator::pointer            pointer;
    typedef typename Pair_allocator::const_pointer      const_pointer;
    typedef typename Pair_allocator::reference          reference;
    typedef typename Pair_allocator::const_reference    const_reference;
    typedef typename Rep_type::iterator                 iterator;
    typedef typename Rep_type::const_iterator           const_iterator;
    typedef typename Rep_type::reverse_iterator         reverse_iterator;
    typedef typename Rep_type::const_reverse_iterator   const_reverse_iterator;
    typedef typename Rep_type::difference_type          difference_type;

    Multimap() : m_t() {}
    Multimap(const Compare& comp, const allocator_type& a = allocator_type())
        : m_t(comp, Pair_allocator(a)) {}
    Multimap(const Multimap& x) : m_t(x.m_t) {}

    template<typename InputIter>
    Multimap(InputIter first, InputIter last) : m_t()
    { m_t.m_insert_equal(first, last); }

    template<typename InputIter>
    Multimap(InputIter first, InputIter last, const Compare& comp,
        const allocator_type& a = allocator_type()) : m_t(comp, Pair_allocator(a))
    { m_t.m_insert_equal(first, last); }

    ~Multimap() {}

    Multimap& operator=(const Multimap& x)
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

    iterator insert(const value_type& x)
    { return m_t.m_insert_equal(x); }

    iterator insert(iterator pos, const value_type& x)
    { return m_t.m_insert_equal(pos, x); }

    template<typename InputIter>
    void insert(InputIter first, InputIter last)
    { m_t.m_insert_equal(first, last); }

    void erase(iterator pos)
    { m_t.erase(pos); }

    size_t erase(const key_type& x)
    { return m_t.erase(x); }

    void erase(iterator first, iterator last)
    { m_t.erase(first, last); }

    void swap(Multimap& x)
    { m_t.swap(x.m_t); }

    void clear()
    { m_t.clear(); }

    key_compare key_comp() const
    { return m_t.key_comp(); }

    value_compare value_comp() const
    { return value_compare(m_t.key_comp()); }

    iterator find(const key_type& x)
    { return m_t.find(x); }

    const_iterator find(const key_type& x) const
    { return m_t.find(x); }

    size_t count(const key_type& x) const
    { return m_t.count(x); }

    iterator lower_bound(const key_type& x)
    { return m_t.lower_bound(x); }

    const_iterator lower_bound(const key_type& x) const
    { return m_t.lower_bound(x); }

    iterator upper_bound(const key_type& x)
    { return m_t.upper_bound(x); }
    
    const_iterator upper_bound(const key_type& x) const
    { return m_t.upper_bound(x); }

    ft::Pair<iterator, iterator> equal_range(const key_type& x)
    { return m_t.equal_range(x); }

    ft::Pair<const_iterator, const_iterator> equal_range(const key_type& x) const
    { return m_t.equal_range(x); }

    template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    friend bool operator==(const Multimap<_Key, _Tp, _Compare, _Alloc>& x,
	    const Multimap<_Key, _Tp, _Compare, _Alloc>& y)
    { return x.m_t == y.m_t; }

    template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    friend bool operator<(const Multimap<_Key, _Tp, _Compare, _Alloc>& x,
	    const Multimap<_Key, _Tp, _Compare, _Alloc>& y)
    { return x.m_t < y.m_t; }

private:
    Rep_type m_t;
};

template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool operator!=(const Multimap<_Key, _Tp, _Compare, _Alloc>& x,
    const Multimap<_Key, _Tp, _Compare, _Alloc>& y)
{ return !(x.m_t == y.m_t); }

template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool operator>(const Multimap<_Key, _Tp, _Compare, _Alloc>& x,
    const Multimap<_Key, _Tp, _Compare, _Alloc>& y)
{ return y < x; }

template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool operator<=(const Multimap<_Key, _Tp, _Compare, _Alloc>& x,
    const Multimap<_Key, _Tp, _Compare, _Alloc>& y)
{ return !(y < x); }

template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool operator>=(const Multimap<_Key, _Tp, _Compare, _Alloc>& x,
    const Multimap<_Key, _Tp, _Compare, _Alloc>& y)
{ return !(x < y); }

template<typename Key, typename Tp, typename Compare, typename Alloc>
inline void swap(Multimap<Key, Tp, Compare, Alloc>& x, Multimap<Key, Tp, Compare, Alloc>& y)
{ x.swap(y); }

} // namespace ft

#endif /* FT_Multimap_HPP */
