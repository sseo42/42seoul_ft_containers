#ifndef FT_ITER_HPP
# define FT_ITER_HPP

# include "ft_library.hpp"
# include <iterator>

namespace ft
{
template<typename Iterator>
class ReverseIterator
    : public std::iterator<typename std::iterator_traits<Iterator>::iterator_category,
        typename std::iterator_traits<Iterator>::value_type,
        typename std::iterator_traits<Iterator>::difference_type,
        typename std::iterator_traits<Iterator>::pointer,
        typename std::iterator_traits<Iterator>::reference>
{
public:
    typedef std::iterator_traits<Iterator>          traits_type;
    typedef Iterator                                iterator_type;
    typedef typename traits_type::difference_type   difference_type;
    typedef typename traits_type::pointer           pointer;
    typedef typename traits_type::reference         reference;

    ReverseIterator() : m_current() {}
    ReverseIterator(Iterator i) : m_current(i) {}
    ReverseIterator(const ReverseIterator& copy) : m_current(copy.base()) {}
    template<typename Iter>
    ReverseIterator(const ReverseIterator<Iter>& copy) : m_current(copy.base()) {}

    ~ReverseIterator() {}

    reference operator*() const
    { Iterator tmp = m_current; return *(--tmp); } 

    pointer operator->() const
    { return ft::addressof(operator*()); }

    ReverseIterator& operator++()
    { --m_current; return *this; }

    ReverseIterator operator++(int)
    { ReverseIterator tmp = *this; --m_current; return tmp; }

    ReverseIterator& operator--()
    { ++m_current; return *this; }

    ReverseIterator operator--(int)
    { ReverseIterator tmp = *this; ++m_current; return tmp; }

    ReverseIterator operator+(difference_type n) const
    { return ReverseIterator(m_current - n); }

    ReverseIterator& operator+=(difference_type n)
    { m_current -= n; return *this; }

    ReverseIterator operator-(difference_type n) const
    { return ReverseIterator(m_current + n); }

    ReverseIterator operator-=(difference_type n)
    { m_current += n; return *this; }

    reference operator[](difference_type n) const
    { return *(*this + n); }

    iterator_type base() const { return m_current; }

protected:
    Iterator    m_current;
};

template<typename IteratorL, typename IteratorR>
inline bool operator==(const ReverseIterator<IteratorL>& lhs,
    const ReverseIterator<IteratorR>& rhs)
{ return (lhs.base() == rhs.base()); }

template<typename Iterator>
inline bool operator==(const ReverseIterator<Iterator>& lhs,
    const ReverseIterator<Iterator>& rhs)
{ return (lhs.base() == rhs.base()); }

template<typename IteratorL, typename IteratorR>
inline bool operator!=(const ReverseIterator<IteratorL>& lhs,
    const ReverseIterator<IteratorR>& rhs)
{ return (lhs.base() != rhs.base()); }

template<typename Iterator>
inline bool operator!=(const ReverseIterator<Iterator>& lhs,
    const ReverseIterator<Iterator>& rhs)
{ return (lhs.base() != rhs.base()); }

template<typename Iterator, typename Container>
class NormalIterator
{
public:
    typedef std::iterator_traits<Iterator>          traits_type;
    typedef Iterator                                iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type        value_type;
    typedef typename traits_type::difference_type   difference_type;
    typedef typename traits_type::reference         reference;
    typedef typename traits_type::pointer           pointer;

    NormalIterator() : m_current() {}
    explicit NormalIterator(const iterator_type& i) : m_current(i) {}
    template<typename Iter>
    NormalIterator(const NormalIterator<Iter, typename ft::enable_if<(
        ft::is_same<Iter, typename Container::pointer>::value), Container>::type>& copy)
        : m_current(copy.base()) {}

    ~NormalIterator() {}

    template<typename Iter>
    NormalIterator& operator=(const NormalIterator<Iter, typename ft::enable_if<(
        ft::is_same<Iter, typename Container::pointer>::value), Container>::type>& i)
    { if (*this == i) return (*this); m_current(i.base()); }

    reference operator*() const
    { return *m_current; }

    pointer operator->() const
    { return m_current; }

    NormalIterator& operator++()
    { ++m_current; return *this; }

    NormalIterator operator++(int)
    { return NormalIterator(m_current++); }

    NormalIterator& operator--()
    { --m_current; return *this; }

    NormalIterator operator--(int)
    { return NormalIterator(m_current--); }

    reference operator[](difference_type n) const
    { return m_current[n]; }

    NormalIterator& operator+=(difference_type n)
    { m_current += n; return *this; }

    NormalIterator operator+(difference_type n) const
    { return NormalIterator(m_current + n); }

    NormalIterator& operator-=(difference_type n)
    { m_current -= n; return *this; }

    NormalIterator operator-(difference_type n) const
    { return NormalIterator(m_current - n); }

    const Iterator& base() const { return m_current; }

protected:
    Iterator    m_current;
};

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator==(const NormalIterator<IteratorL, Container>& lhs,
    const NormalIterator<IteratorR, Container>& rhs)
{ return (lhs.base() == rhs.base()); }

template<typename Iterator, typename Container>
inline bool operator==(const NormalIterator<Iterator, Container>& lhs,
    const NormalIterator<Iterator, Container>& rhs)
{ return (lhs.base() == rhs.base()); }

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator!=(const NormalIterator<IteratorL, Container>& lhs,
    const NormalIterator<IteratorR, Container>& rhs)
{ return (lhs.base() != rhs.base()); }

template<typename Iterator, typename Container>
inline bool operator!=(const NormalIterator<Iterator, Container>& lhs,
    const NormalIterator<Iterator, Container>& rhs)
{ return (lhs.base() != rhs.base()); }

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator<(const NormalIterator<IteratorL, Container>& lhs,
    const NormalIterator<IteratorR, Container>& rhs)
{ return (lhs.base() < rhs.base()); }

template<typename Iterator, typename Container>
inline bool operator<(const NormalIterator<Iterator, Container>& lhs,
    const NormalIterator<Iterator, Container>& rhs)
{ return (lhs.base() < rhs.base()); }

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator>(const NormalIterator<IteratorL, Container>& lhs,
    const NormalIterator<IteratorR, Container>& rhs)
{ return (lhs.base() > rhs.base()); }

template<typename Iterator, typename Container>
inline bool operator>(const NormalIterator<Iterator, Container>& lhs,
    const NormalIterator<Iterator, Container>& rhs)
{ return (lhs.base() > rhs.base()); }

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator>=(const NormalIterator<IteratorL, Container>& lhs,
    const NormalIterator<IteratorR, Container>& rhs)
{ return (lhs.base() >= rhs.base()); }

template<typename Iterator, typename Container>
inline bool operator>=(const NormalIterator<Iterator, Container>& lhs,
    const NormalIterator<Iterator, Container>& rhs)
{ return (lhs.base() >= rhs.base()); }

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator<=(const NormalIterator<IteratorL, Container>& lhs,
    const NormalIterator<IteratorR, Container>& rhs)
{ return (lhs.base() <= rhs.base()); }

template<typename IteratorL, typename IteratorR, typename Container>
inline typename NormalIterator<IteratorL, Container>::difference_type
    operator-(const NormalIterator<IteratorL, Container>& lhs,
	      const NormalIterator<IteratorR, Container>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename Iterator, typename Container>
inline typename NormalIterator<Iterator, Container>::difference_type
    operator-(const NormalIterator<Iterator, Container>& lhs,
	      const NormalIterator<Iterator, Container>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename IteratorL, typename IteratorR, typename Container>
inline typename NormalIterator<IteratorL, Container>::difference_type
    operator+(const NormalIterator<IteratorL, Container>& lhs,
	      const NormalIterator<IteratorR, Container>& rhs)
{ return lhs.base() + rhs.base(); }

template<typename Iterator, typename Container>
inline typename NormalIterator<Iterator, Container>::difference_type
    operator+(const NormalIterator<Iterator, Container>& lhs,
	      const NormalIterator<Iterator, Container>& rhs)
{ return lhs.base() + rhs.base(); }

} // namespace ft

#endif /* FT_ITER_HPP */
