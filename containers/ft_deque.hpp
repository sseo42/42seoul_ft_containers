#ifndef FT_DEQUE_HPP
# define FT_DEQUE_HPP

# include "ft_iter.hpp"
# include "ft_library.hpp"
# include <memory>

/**
 * member functions
 * Iterators:
 *      begin       clear
 *      end         clear
 *      rbegin      clear
 *      rend        clear
 * 
 * Capacity:
 *      size        clear
 *      max_size    clear
 *      resize      clear
 *      empty       clear
 * 
 * Element access:
 *      operator[]  clear
 *      at          clear
 *      front       clear
 *      back        clear
 * 
 * Modifiers:
 *      assign      clear
 *      push_back   clear
 *      push_front  clear
 *      pop_back    clear
 *      pop_front   clear
 *      insert      clear
 *      erase       clear
 *      swap        clear
 *      clear       clear
 */

namespace ft
{
#ifndef DEQUE_BUF_SIZE
# define DEQUE_BUF_SIZE 512
#endif

inline size_t deque_buf_size(size_t size)
{ return (size < DEQUE_BUF_SIZE) ? size_t(DEQUE_BUF_SIZE / size) : size_t(1); }
    // check

template<typename Tp, typename Ref, typename Ptr>
struct DequeIterator
{
    typedef DequeIterator                           Self;
    typedef Tp*                                     Elt_pointer;
    typedef Tp**                                    Map_pointer;

    typedef DequeIterator<Tp, Tp&, Tp*>             iterator;
    typedef DequeIterator<Tp, const Tp&, const Tp*> const_iterator;
    typedef std::random_access_iterator_tag         iterator_category;
    typedef Tp                                      value_type;
    typedef Ptr                                     pointer;
    typedef Ref                                     reference;
    typedef long                                    difference_type;

    static size_t s_buf_size()
    { return ft::deque_buf_size(sizeof(Tp)); }

    DequeIterator(Elt_pointer x, Map_pointer y)
        : m_cur(x), m_first(*y), m_last(*y + s_buf_size()), m_node(y) {};
    
    DequeIterator()
        : m_cur(), m_first(), m_last(), m_node() {};

    DequeIterator(const iterator& x)
        : m_cur(x.m_cur), m_first(x.m_first),
        m_last(x.m_last), m_node(x.m_node) {}

    iterator m_const_cast() const
    { return iterator(m_cur, m_node); }

    reference operator*() const
    { return *m_cur; }

    pointer operator->() const
    { return m_cur; }

    Self& operator++()
    {
        ++m_cur;
        if (m_cur == m_last)
        {
            m_set_node(m_node + 1);
            m_cur = m_first;
        }
        return *this;
    }

    Self operator++(int)
    {
        Self tmp = *this;
        ++*this;
        return tmp;
    }

    Self& operator--()
    {
        if (m_cur == m_first)
        {
            m_set_node(m_node - 1);
            m_cur = m_last;
        }
        --m_cur;
        return *this;
    }

    Self operator--(int)
    {
        Self tmp = *this;
        --*this;
        return tmp;
    }

    Self& operator+=(difference_type n)
    {
        const difference_type offset = n + (m_cur - m_first);
        if (offset >= 0 && offset < difference_type(s_buf_size()))
        {
            m_cur += n;
        }
        else
        {
            const difference_type node_offset =
                (offset > 0) ? offset / difference_type(s_buf_size())
                : -difference_type((-offset - 1) / s_buf_size()) - 1;
            m_set_node(m_node + node_offset);
            m_cur = m_first +
                (offset - node_offset * difference_type(s_buf_size()));
        }
        return *this;
    }

    Self operator+(difference_type n) const
    { Self tmp = *this; return (tmp += n); }

    Self& operator-=(difference_type n)
    { return *this += -n; }

    Self operator-(difference_type n) const
    { Self tmp = *this; return (tmp -= n); }

    reference operator[](difference_type n) const
    { return *(*this + n); }

    void m_set_node(Map_pointer new_node)
    {
        m_node = new_node;
        m_first = *new_node;
        m_last = m_first + difference_type(s_buf_size());
    }

    Elt_pointer m_cur;
    Elt_pointer m_first;
    Elt_pointer m_last;
    Map_pointer m_node;
};

template<typename Tp, typename Ref, typename Ptr>
inline bool operator==(const DequeIterator<Tp, Ref, Ptr>& x,
    const DequeIterator<Tp, Ref, Ptr>& y)
{ return (x.m_cur == y.m_cur); }

template<typename Tp, typename RefL, typename PtrL,
    typename RefR, typename PtrR>
inline bool operator==(const DequeIterator<Tp, RefL, PtrL>& x,
    const DequeIterator<Tp, RefR, PtrR>& y)
{ return (x.m_cur == y.m_cur); }

template<typename Tp, typename Ref, typename Ptr>
inline bool operator!=(const DequeIterator<Tp, Ref, Ptr>& x,
    const DequeIterator<Tp, Ref, Ptr>& y)
{ return !(x.m_cur == y.m_cur); }

template<typename Tp, typename RefL, typename PtrL,
    typename RefR, typename PtrR>
inline bool operator!=(const DequeIterator<Tp, RefL, PtrL>& x,
    const DequeIterator<Tp, RefR, PtrR>& y)
{ return !(x.m_cur == y.m_cur); }

template<typename Tp, typename Ref, typename Ptr>
inline bool operator<(const DequeIterator<Tp, Ref, Ptr>& x,
    const DequeIterator<Tp, Ref, Ptr>& y)
{ return ((x.m_node == y.m_node) ? (x.m_cur < y.m_cur)
    : (x.m_node < y.m_node)); }

template<typename Tp, typename RefL, typename PtrL,
    typename RefR, typename PtrR>
inline bool operator<(const DequeIterator<Tp, RefL, PtrL>& x,
    const DequeIterator<Tp, RefR, PtrR>& y)
{ return ((x.m_node == y.m_node) ? (x.m_cur < y.m_cur)
    : (x.m_node < y.m_node)); }

template<typename Tp, typename Ref, typename Ptr>
inline bool operator>(const DequeIterator<Tp, Ref, Ptr>& x,
    const DequeIterator<Tp, Ref, Ptr>& y)
{ return (y < x); }

template<typename Tp, typename RefL, typename PtrL,
    typename RefR, typename PtrR>
inline bool operator>(const DequeIterator<Tp, RefL, PtrL>& x,
    const DequeIterator<Tp, RefR, PtrR>& y)
{ return (y < x); }

template<typename Tp, typename Ref, typename Ptr>
inline bool operator<=(const DequeIterator<Tp, Ref, Ptr>& x,
    const DequeIterator<Tp, Ref, Ptr>& y)
{ return !(y < x); }

template<typename Tp, typename RefL, typename PtrL,
    typename RefR, typename PtrR>
inline bool operator<=(const DequeIterator<Tp, RefL, PtrL>& x,
    const DequeIterator<Tp, RefR, PtrR>& y)
{ return !(y < x); }

template<typename Tp, typename Ref, typename Ptr>
inline bool operator>=(const DequeIterator<Tp, Ref, Ptr>& x,
    const DequeIterator<Tp, Ref, Ptr>& y)
{ return !(x < y); }

template<typename Tp, typename RefL, typename PtrL,
    typename RefR, typename PtrR>
inline bool operator>=(const DequeIterator<Tp, RefL, PtrL>& x,
    const DequeIterator<Tp, RefR, PtrR>& y)
{ return !(x < y); }

template<typename Tp, typename Ref, typename Ptr>
inline typename DequeIterator<Tp, Ref, Ptr>::difference_type
    operator-(const DequeIterator<Tp, Ref, Ptr>& x,
    const DequeIterator<Tp, Ref, Ptr>& y)
{
    return typename DequeIterator<Tp, Ref, Ptr>::difference_type
    (DequeIterator<Tp, Ref, Ptr>::s_buf_size()) * (x.m_node - y.m_node - 1)
    + (x.m_cur - x.m_first) + (y.m_last - y.m_cur);
}

template<typename Tp, typename RefL, typename PtrL,
    typename RefR, typename PtrR>
inline typename DequeIterator<Tp, RefL, PtrL>::difference_type
    operator-(const DequeIterator<Tp, RefL, PtrL>& x,
    const DequeIterator<Tp, RefR, PtrR>& y)
{
    return typename DequeIterator<Tp, RefL, PtrL>::difference_type
    (DequeIterator<Tp, RefL, PtrL>::s_buf_size()) * (x.m_node - y.m_node - 1)
    + (x.m_cur - x.m_first) + (y.m_last - y.m_cur);
}

template<typename Tp, typename Ref, typename Ptr>
inline typename DequeIterator<Tp, Ref, Ptr>::difference_type
    operator+(long n, const DequeIterator<Tp, Ref, Ptr>& x)
{ return x + n; }

template<typename Tp, typename Alloc>
class DequeBase
{
public:
    typedef Alloc                                   Alloc_type;
    typedef typename std::allocator<Alloc>::template
    rebind<Tp>::other                               Tp_alloc_type;
    typedef typename Tp_alloc_type::pointer         pointer;
    typedef typename Tp_alloc_type::const_pointer   const_pointer;
    typedef typename std::allocator<Alloc>::template
    rebind<pointer>::other                          Map_alloc_type;
    typedef ft::DequeIterator<Tp, Tp&, pointer>     iterator;
    typedef ft::DequeIterator<Tp, const Tp&, const_pointer> const_iterator;

    DequeBase() : m_impl()
    { m_initialize_map(0); }
    DequeBase(size_t num_elems) : m_impl()
    { m_initialize_map(num_elems); }
    DequeBase(const Alloc_type& a, size_t num_elems) : m_impl(a)
    { m_initialize_map(num_elems); }
    DequeBase(const Alloc_type& a) : m_impl(a)
    { m_initialize_map(0); }

    ~DequeBase()
    {
        if (this->m_impl.m_map)
        {
            m_destroy_nodes(this->m_impl.m_start.m_node,
                this->m_impl.m_finish.m_node + 1);
            m_deallocate_map(this->m_impl.m_map, this->m_impl.m_map_size);
        }
    }

protected:
    typedef typename iterator::Map_pointer          Map_pointer;
    enum { s_initial_map_size = 8 };

    struct Deque_impl : public Tp_alloc_type
    {
        Map_pointer m_map;
        size_t m_map_size;
        iterator m_start;
        iterator m_finish;

        Deque_impl()
            : Tp_alloc_type(), m_map(), m_map_size(0), m_start(), m_finish() {}
        Deque_impl(const Tp_alloc_type& a)
            : Tp_alloc_type(a), m_map(), m_map_size(0), m_start(), m_finish() {}

        void m_swap_data(Deque_impl& x)
        {
            std::swap(this->m_start, x.m_start);
            std::swap(this->m_finish, x.m_finish);
            std::swap(this->m_map, x.m_map);
            std::swap(this->m_map_size, x.m_map_size);
        }
    };

    Tp_alloc_type& m_get_tp_allocator()
    { return *static_cast<Tp_alloc_type*>(&this->m_impl); }

    const Tp_alloc_type& m_get_tp_allocator() const
    { return *static_cast<const Tp_alloc_type*>(&this->m_impl); }

    Map_alloc_type m_get_map_allocator() const
    { return Map_alloc_type(m_get_tp_allocator()); }

    pointer m_allocate_node()
    { return m_impl.allocate(deque_buf_size(sizeof(Tp))); }

    void m_deallocate_node(pointer p)
    { m_impl.deallocate(p, deque_buf_size(sizeof(Tp))); }

    Map_pointer m_allocate_map(size_t n)
    {
        Map_alloc_type map_alloc = m_get_map_allocator();
        return map_alloc.allocate(n);
    }

    void m_deallocate_map(Map_pointer p, size_t n)
    {
        Map_alloc_type map_alloc = m_get_map_allocator();
        map_alloc.deallocate(p, n);
    }

    void m_initialize_map(size_t num_elems)
    {
        const size_t num_nodes = num_elems / deque_buf_size(sizeof(Tp)) + 1;

        this->m_impl.m_map_size = ft::max(
            (size_t)s_initial_map_size, size_t(num_nodes + 2));
        this->m_impl.m_map = m_allocate_map(this->m_impl.m_map_size);

        Map_pointer nstart = this->m_impl.m_map + 
            (this->m_impl.m_map_size - num_nodes) / 2;
        Map_pointer nfinish = nstart + num_nodes;

        try
        {
            m_create_nodes(nstart, nfinish);
        }
        catch(...)
        {
            m_deallocate_map(this->m_impl.m_map, this->m_impl.m_map_size);
            this->m_impl.m_map = Map_pointer();
            this->m_impl.m_map_size = 0;
            throw ;
        }
        this->m_impl.m_start.m_set_node(nstart);
        this->m_impl.m_finish.m_set_node(nfinish - 1);
        this->m_impl.m_start.m_cur = this->m_impl.m_start.m_first;
        this->m_impl.m_finish.m_cur = this->m_impl.m_finish.m_first +
            num_elems % deque_buf_size(sizeof(Tp));
    }

    void m_create_nodes(Map_pointer nstart, Map_pointer nfinish)
    {
        Map_pointer cur;

        try
        {
            for (cur = nstart; cur < nfinish; ++cur)
                *cur = this->m_allocate_node();
        }
        catch(...)
        {
            m_destroy_nodes(nstart, cur);
            throw ;
        }
    }

    void m_destroy_nodes(Map_pointer nstart, Map_pointer nfinish)
    {
        for (Map_pointer n = nstart; n < nfinish; ++n)
            m_deallocate_node(*n);
    }

    Deque_impl m_impl;
};

template<typename Tp, typename Alloc = std::allocator<Tp> >
class Deque : public DequeBase<Tp, Alloc>
{
    typedef DequeBase<Tp, Alloc>                            Base;
    typedef typename Base::Tp_alloc_type                    Tp_alloc_type;
    typedef typename Base::Map_pointer                      Map_pointer;

public:
    typedef Alloc                                           Alloc_type;
    typedef Tp                                              value_type;
    typedef typename Alloc_type::pointer                    pointer;
    typedef typename Alloc_type::const_pointer              const_pointer;
    typedef typename Alloc_type::reference                  reference;
    typedef typename Alloc_type::const_reference            const_reference;
    typedef typename Base::iterator                         iterator;
    typedef typename Base::const_iterator                   const_iterator;
    typedef typename ft::ReverseIterator<iterator>          reverse_iterator;
    typedef typename ft::ReverseIterator<const_iterator>    const_reverse_iterator;
    typedef long                                            difference_type;

    Deque() : Base() {}
    Deque(const Alloc_type& a) : Base(a, 0) {}
    Deque(size_t n, const value_type& value = value_type(),
        const Alloc_type& a = Alloc_type()) : Base(a, n)
    { m_fill_initialize(value); }
    Deque(const Deque& x) : Base(x.m_get_tp_allocator(), x.size()) //problem copy
    { std::uninitialized_copy(x.begin(), x.end(), this->m_impl.m_start); }

    template<typename InputIter>
    Deque(InputIter first, InputIter last, const Alloc_type& a = Alloc_type())
        : Base(a)
    {
        typedef typename ft::is_integer<InputIter>::type Integral;
        m_initialized_dispatch(first, last, Integral());
    }
    ~Deque()
    { m_destroy_data(begin(), end()); }

    iterator begin()
    { return this->m_impl.m_start; }

    const_iterator begin() const
    { return this->m_impl.m_start; }

    iterator end()
    { return this->m_impl.m_finish; }

    const_iterator end() const
    { return this->m_impl.m_finish; }

    reverse_iterator rbegin()
    { return reverse_iterator(this->m_impl.m_finish); }

    const_reverse_iterator rbegin() const
    { return const_reverse_iterator(this->m_impl.m_finish); }

    reverse_iterator rend()
    { return reverse_iterator(this->m_impl.m_start); }

    const_reverse_iterator rend() const
    { return const_reverse_iterator(this->m_impl.m_start); }

    size_t size() const
    { return (this->m_impl.m_finish - this->m_impl.m_start); }

    size_t max_size() const
    { return Tp_alloc_type().max_size(); }

    void resize(size_t new_size, value_type x = value_type())
    {
        const size_t len = size();
        if (new_size > len)
            m_fill_insert(this->m_impl.m_finish, new_size - len, x);
        else if (new_size < len)
            m_erase_at_end(this->m_impl.m_start + difference_type(new_size));
    }

    bool empty() const
    { return this->m_impl.m_start == this->m_impl.m_finish; }

    reference operator[](size_t n)
    { return this->m_impl.m_start[difference_type(n)]; }

    const reference operator[](size_t n) const
    { return this->m_impl.m_start[difference_type(n)]; }

    reference at(size_t n)
    {
        if (n < size())
            return (*this)[n];
        throw std::out_of_range("deque: at");
    }

    const reference at(size_t n) const
    {
        if (n < size())
            return (*this)[n];
        throw std::out_of_range("deque: at");
    }

    reference front()
    { return *begin(); }

    const reference front() const
    { return *begin(); }

    reference back()
    { iterator tmp = end(); --tmp; return *tmp; }

    const reference back() const
    { const iterator tmp = end(); --tmp; return *tmp; }

    void assign(size_t n, const value_type& x)
    { m_fill_assign(n, x); }

    template<typename InputIter>
    void assign(InputIter first, InputIter last)
    {
        typedef typename ft::is_integer<InputIter>::type Integral;
        m_assign_dispatch(first, last, Integral());
    }

    void push_front(const value_type& x)
    {
        if (this->m_impl.m_start.m_cur != this->m_impl.m_start.m_first)
        {
            this->m_impl.construct(this->m_impl.m_start.m_cur - 1, x);
            --this->m_impl.m_start.m_cur;
        }
        else
        {
            m_push_front(x);
        }
    }

    void push_back(const value_type& x)
    {
        if (this->m_impl.m_finish.m_cur != this->m_impl.m_finish.m_last - 1)
        {
            this->m_impl.construct(this->m_impl.m_finish.m_cur, x);
            ++this->m_impl.m_finish.m_cur;
        }
        else
        {
            m_push_back(x);
        }
    }

    void pop_front()
    {
        if (this->m_impl.m_start.m_cur != this->m_impl.m_start.m_last - 1)
        {
            this->m_impl.destroy(this->m_impl.m_start.m_cur);
            ++this->m_impl.m_start.m_cur;
        }
        else
        {
            m_pop_front();
        }
    }

    void pop_back()
    {
        if (this->m_impl.m_finish.m_cur != this->m_impl.m_finish.m_first)
        {
            --this->m_impl.m_finish.m_cur;
            this->m_impl.destroy(this->m_impl.m_finish.m_cur);
        }
        else
        {
            m_pop_back();
        }
    }

    iterator insert(iterator pos, const value_type& x)
    {
        if (pos.m_cur == this->m_impl.m_start.m_cur)
        {
            push_front(x);
            return this->m_impl.m_start;
        }
        else if (pos.m_cur == this->m_impl.m_finish.m_cur)
        {
            push_back(x);
            iterator tmp = this->m_impl.m_finish;
            --tmp;
            return tmp;
        }
        else
        {
            return m_insert(pos, x);
        }
    }

    void insert(iterator pos, size_t n, const value_type& x)
    {
        m_fill_insert(pos, n, x);
    }

    template<typename InputIter>
    void insert(iterator pos, InputIter first, InputIter last)
    {
        typedef typename ft::is_integer<InputIter>::type Integral;
        m_insert_dispatch(pos, first, last, Integral());
    }

    iterator erase(iterator pos)
    { return m_erase(pos); }

    iterator erase(iterator first, iterator last)
    { return m_erase(first, last); }

    void swap(Deque& dq)
    {
        this->m_impl.m_swap_data(dq.m_impl);
        std::swap(Base::m_get_tp_allocator(), dq.Base::m_get_tp_allocator());
    }

    void clear()
    { m_erase_at_end(begin()); }

protected:
    static size_t s_buf_size()
    { return deque_buf_size(sizeof(Tp)); }
    
    void m_fill_initialize(const value_type& value)
    {
        Map_pointer cur;
        try
        {
            for (cur = this->m_impl.m_start.m_node;
                cur < this->m_impl.m_finish.m_node; ++cur)
                std::uninitialized_fill(*cur, *cur + s_buf_size(), value);
            std::uninitialized_fill(this->m_impl.m_finish.m_finish,
                this->m_impl.m_finish.m_cur, value);
        }
        catch(...)
        {
            ft::destroy(this->m_impl.m_start, iterator(*cur, cur), Base::m_get_tp_allocator());
            throw ;
        }
    }
    template<typename ForwardIterator>
    void m_range_initialze(ForwardIterator first, ForwardIterator last,
        std::forward_iterator_tag)
    {
        const size_t n = std::distance(first, last);
        this->Base::m_initialize_map(n);

        Map_pointer cur_node;
        try
        {
            for (cur_node = this->m_impl.m_start.m_node;
                cur_node < this->m_impl.m_finish.m_node; ++cur_node)
            {
                ForwardIterator mid = first;
                std::advance(mid, s_buf_size());
                std::uninitialized_copy(first, mid, *cur_node, Base::m_get_tp_allocator());
                first = mid;
            }
            std::uninitialized_copy(first, last, this->m_impl.m_finish.m_first, Base::m_get_tp_allocator());
        }
        catch(...)
        {
            ft::destroy(this->m_impl.m_start, iterator(*cur_node, cur_node), Base::m_get_tp_allocator());
            throw ;
        }
    }
    void m_fill_insert(iterator pos, size_t n, const value_type& x)
    {
        if (pos.m_cur == this->m_impl.m_start.m_cur)
        {
            iterator new_start = m_reserve_elems_at_front(n);
            try
            {
                std::uninitialized_fill(new_start, this->m_impl.m_start, x);
                this->m_impl.m_start = new_start;
            }
            catch(...)
            {
                Base::m_destroy_nodes(new_start.m_node, this->m_impl.m_start.m_node);
                throw ;
            }
        }
        else if (pos.m_cur == this->m_impl.m_finish.m_cur)
        {
            iterator new_finish = m_reserve_elems_at_back(n);
            try
            {
                std::uninitialized_fill(this->m_impl.m_finish, new_finish, x);
                this->m_impl.m_finish = new_finish;
            }
            catch(...)
            {
                Base::m_destroy_nodes(this->m_impl.m_finish.m_node + 1,
                    new_finish.m_node + 1);
                throw ;
            }
        }
        else
        {
            m_insert(pos, n, x);
        }
    }
    template<typename Integer>
    void m_initialized_dispatch(Integer n, Integer x, ft::TrueType)
    {
        Base::m_initialize_map(static_cast<size_t>(n));
        m_fill_initialize(x);
    }
    template<typename InputIter>
    void m_initialized_dispatch(InputIter first, InputIter last, ft::FalseType)
    {
        m_range_initialize(first, last, first.interator_category);
    }

    template<typename Integer>
    void m_assign_dispatch(Integer n, Integer x, ft::TrueType)
    { m_fill_assign(n, x); }

    template<typename InputIter>
    void m_assign_dispatch(InputIter first, InputIter last, ft::FalseType)
    { m_assign(first, last); }

    template<typename Integer>
    void m_insert_dispatch(iterator pos, Integer n, Integer x, ft::TrueType)
    { m_fill_insert(pos, n, x); }

    template<typename InputIter>
    void m_insert_dispatch(iterator pos, InputIter first, InputIter last, ft::FalseType)
    { m_range_insert(pos, first, last); }

    void m_fill_assign(size_t n, const value_type& x)
    {
        if (n > size())
        {
            ft::fill(begin(), end(), x);
            m_fill_insert(end(), n - size(), x);
        }
        else
        {
            m_erase_at_end(begin() + difference_type(n));
            ft::fill(begin(), end(), x);
        }
    }

    iterator m_insert(iterator pos, const value_type& x) //check error case
    {
        value_type x_copy = x;
        difference_type index = pos - this->m_impl.m_start;
        if (index < (difference_type(size() / 2)))
        {
            push_front(value_type());
            iterator tmp1 = this->m_impl.m_start;
            ++tmp1;
            pos = this->m_impl.m_start + index;
            iterator tmp2 = pos;
            ++tmp2;
            std::copy(tmp1, tmp2, this->m_impl.m_start);
        }
        else
        {
            push_back(value_type());
            iterator tmp = this->m_impl.m_finish;
            --tmp;
            pos = this->m_impl.m_start + index;
            std::copy_backward(pos, tmp, this->m_impl.m_finish);
        }
        *pos = x_copy;
        return pos;
    }

    void m_insert(iterator pos, size_t n, const value_type& x)
    {
        const difference_type elems_before = pos - this->m_impl.m_start;
        const size_t len = this->size();
        value_type x_copy = x;
        if (elems_before < difference_type(len / 2))
        {
            iterator new_start = m_reserve_elems_at_front(n);
            iterator old_start = this->m_impl.m_start;
            pos = this->m_impl.m_start + elems_before; // need?
            try
            {
                if (elems_before >= difference_type(n))
                {
                    iterator start_n = this->m_impl.m_start + difference_type(n);
                    std::uninitialized_copy(this->m_impl.m_start, start_n, new_start);
                    this->m_impl.m_start = new_start;
                    std::copy(start_n, pos, old_start); //check memory leak
                    ft::fill(pos - difference_type(n), pos, x_copy);
                }
                else
                {
                    iterator tmp = std::uninitialized_copy(this->m_impl.m_start, pos, new_start);
                    try
                    {
                        std::uninitialized_fill(tmp, this->m_impl.m_start, x_copy);
                    }
                    catch(...)
                    {
                        ft::destroy(new_start, tmp, Base::m_get_tp_allocator());
                        throw ;
                    }
                    this->m_impl.m_start = new_start;
                    ft::fill(old_start, pos, x_copy);
                }
            }
            catch(...)
            {
                Base::m_destroy_nodes(new_start.m_node, this->m_impl.m_start.m_node);
                throw ;
            }
        }
        else
        {
            iterator new_finish = m_reserve_elems_at_back(n);
            iterator old_finish = this->m_impl.m_finish;
            const difference_type elems_after = difference_type(len) - elems_before;
            pos = this->m_impl.m_finish - elems_after;
            try
            {
                if (elems_after > difference_type(n))
                {
                    iterator finish_n = this->m_impl.m_finish - difference_type(n);
                    std::uninitialized_copy(finish_n, this->m_impl.m_finish, this->m_impl.m_finish);
                    this->m_impl.m_finish = new_finish;
                    std::copy_backward(pos, finish_n, old_finish); //check 3rd argument
                    ft::fill(pos, pos + difference_type(n), x_copy);
                }
                else
                {
                    std::uninitialized_copy(pos, this->m_impl.m_finish, new_finish - elems_after);
                    try
                    {
                        std::uninitialized_fill(this->m_impl.m_finish, new_finish - elems_after, x_copy);
                    }
                    catch(...)
                    {
                        ft::destroy(new_finish - elems_after, new_finish, Base::m_get_tp_allocator());
                        throw ;
                    }
                    this->m_impl.m_finish = new_finish;
                    ft::fill(pos, old_finish, x_copy);
                }
            }
            catch(...)
            {
                Base::m_destroy_nodes(this->m_impl.m_finish.m_node + 1, new_finish.m_node + 1);
                throw ;
            }
        }
    }

    template<typename ForwardIter>
    void m_insert(iterator pos, ForwardIter first, ForwardIter last, size_t n)
    {
        const difference_type elems_before = pos - this->m_impl.m_start;
        const size_t len = size();
        if (elems_before < difference_type(len / 2))
        {
            iterator new_start = m_reserve_elems_at_front(n);
            iterator old_start = this->m_impl.m_start;
            pos = this->m_impl.m_start + elems_before; // need?
            try
            {
                if (elems_before >= difference_type(n))
                {
                    iterator start_n = this->m_impl.m_start + difference_type(n);
                    std::uninitialized_copy(this->m_impl.m_start, start_n, new_start);
                    this->m_impl.m_start = new_start;
                    std::copy(start_n, pos, old_start);
                    std::copy(first, last, pos - difference_type(n));
                }
                else
                {
                    ForwardIter mid = first;
                    std::advance(mid, difference_type(n) - elems_before);
                    iterator tmp = std::uninitialized_copy(this->m_impl.m_start, pos, new_start);
                    try
                    {
                        std::uninitialized_copy(first, mid, tmp);
                    }
                    catch(...)
                    {
                        ft::destroy(new_start, tmp, Base::m_get_tp_allocator());
                        throw ;
                    }
                    this->m_impl.m_start = new_start;
                    std::copy(mid, last, old_start);
                }
            }
            catch(...)
            {
                Base::m_destroy_nodes(new_start.m_node, this->m_impl.m_start.m_node);
                throw ;
            }
        }
        else
        {
            iterator new_finish = m_reserve_elems_at_back(n);
            iterator old_finish = this->m_impl.m_finish;
            const difference_type elems_after = difference_type(len) - elems_before;
            pos = this->m_impl.m_finish - elems_after; //need?
            try
            {
                if (elems_after > difference_type(n))
                {
                    iterator finish_n = this->m_impl.m_finish - difference_type(n);
                    std::uninitialized_copy(finish_n, this->m_impl.m_finish, this->m_impl.m_finish);
                    std::copy_backward(pos, finish_n, this->m_impl.m_finish); //check 3rd argment
                    this->m_impl.m_finish = new_finish;
                    std::copy(first, last, pos);
                }
                else
                {
                    ForwardIter mid = first;
                    std::advance(mid, elems_after);
                    std::uninitialized_copy(pos, this->m_impl.m_finish, new_finish - elems_after);
                    try
                    {
                        std::uninitialized_copy(mid, last, this->m_impl.m_finish);
                    }
                    catch(...)
                    {
                        ft::destroy(new_finish - elems_after, new_finish, Base::m_get_tp_allocator());
                    }
                    this->m_impl.m_finish = new_finish;
                    std::copy(first, mid, pos);
                }
            }
            catch(...)
            {
                Base::m_destroy_nodes(this->m_impl.m_finish.m_node + 1, new_finish.m_node + 1);
                throw ;
            }
        }
    }

    template<typename ForwardIter>
    void m_range_insert(iterator pos, ForwardIter first, ForwardIter last)
    {
        const size_t n = std::distance(first, last);
        if (pos.m_cur == this->m_impl.m_start.m_cur)
        {
            iterator new_start = m_reserve_elems_at_front(n);
            try
            {
                std::uninitialized_copy(first, last, new_start);
                this->m_impl.m_start = new_start;
            }
            catch(...)
            {
                Base::m_destroy_nodes(new_start.m_node, this->m_impl.m_start.m_node);
                throw ;
            }
        }
        else if (pos.m_cur == this->m_impl.m_finish.m_cur)
        {
            iterator new_finish = m_reserve_elems_at_back(n);
            try
            {
                std::uninitialized_copy(first, last, this->m_impl.m_finish);
                this->m_impl.m_finish = new_finish;
            }
            catch(...)
            {
                Base::m_destroy_nodes(this->m_impl.m_finish.m_node + 1, new_finish.m_node + 1);
                throw ;
            }
        }
        else
        {
            m_insert(pos, first, last, n);
        }
    }

    template<typename ForwardIter>
    void m_assign(ForwardIter first, ForwardIter last)
    {
        const size_t n = std::distance(first, last);
        if (n > size())
        {
            ForwardIter mid = first;
            std::advance(mid, size());
            std::copy(first, mid, begin());
            m_range_insert(end(), mid, last);
        }
        else
        {
            m_erase_at_end(std::copy(first, last, begin()));
        }
    }

    void m_push_front(const value_type& x)
    {
        m_reserve_map_at_front();
        *(this->m_impl.m_start.m_node - 1) = this->Base::m_allocate_node();
        try
        {
            this->m_impl.m_start.m_set_node(this->m_impl.m_start.m_node - 1);
            this->m_impl.m_start.m_cur = this->m_impl.m_start.m_last - 1;
            this->m_impl.construct(this->m_impl.m_start.m_cur, x);
        }
        catch(...)
        {
            ++this->m_impl.m_start;
            Base::m_deallocate_node(*(this->m_impl.m_start.m_node - 1));
            throw ;
        }
    }

    void m_push_back(const value_type& x)
    {
        m_reserve_map_at_back();
        *(this->m_impl.m_finish.m_node + 1) = this->Base::m_allocate_node();
        try
        {
            this->m_impl.construct(this->m_impl.m_finish.m_cur, x);
            this->m_impl.m_finish.m_set_node(this->m_impl.m_finish.m_node + 1);
            this->m_impl.m_finish.m_cur = this->m_impl.m_finish.m_first;
        }
        catch(...)
        {
            this->m_impl.destroy(this->m_impl.m_finish.m_cur); //check error
            Base::m_deallocate_node(*(this->m_impl.m_finish.m_node + 1));
            throw ;
        }
    }

    void m_pop_front()
    {
        this->m_impl.destroy(this->m_impl.m_start.m_cur);
        Base::m_deallocate_node(this->m_impl.m_start.m_first);
        this->m_impl.m_start.m_set_node(this->m_impl.m_start.m_node + 1);
        this->m_impl.m_start.m_cur = this->m_impl.m_start.m_first;
    }

    void m_pop_back()
    {
        Base::m_deallocate_node(this->m_impl.m_finish.m_first);
        this->m_impl.m_finish.m_set_node(this->m_impl.m_finish.m_node - 1);
        this->m_impl.m_finish.m_cur = this->m_impl.m_finish.m_last - 1;
        this->m_impl.destroy(this->m_impl.m_finish.m_cur);
    }

    void m_erase_at_begin(iterator pos)
    {
        m_destroy_data(begin(), pos);
        Base::m_destroy_nodes(this->m_impl.m_start.m_node, pos.m_node);
        this->m_impl.m_start = pos;
    }

    void m_erase_at_end(iterator pos)
    {
        m_destroy_data(pos, end());
        Base::m_destroy_nodes(pos.m_node + 1, this->m_impl.m_finish.m_node + 1);
        this->m_impl.m_finish = pos;
    }

    iterator m_erase(iterator pos)
    {
        iterator next = pos;
        ++next;
        const difference_type index = pos - begin();
        if (index < difference_type(size() / 2))
        {
            if (pos != begin())
                std::copy_backward(begin(), pos, next);
            pop_front();
        }
        else
        {
            if (next != end())
                std::copy(next, end(), pos);
            pop_back();
        }
        return begin() + index;
    }

    iterator m_erase(iterator first, iterator last)
    {
        if (first == last)
        {
            return first;
        }
        else if (first == begin() && last == end())
        {
            clear();
            return end();
        }
        else
        {
            const difference_type n = std::distance(first, last);
            const difference_type elems_before = std::distance(begin(), first);
            if (elems_before <= (difference_type(size()) - n) / 2)
            {
                if (first != begin())
                    std::copy_backward(begin(), first, last);
                m_erase_at_begin(begin() + n);
            }
            else
            {
                if (last != end())
                    std::copy(last, end(), first);
                m_erase_at_end(end() - n);
            }
            return begin() + elems_before;
        }
    }

    void m_destroy_data(iterator first, iterator last)
    {
        for (Map_pointer node = first.m_node + 1; node < last.m_node; ++node)
            ft::destroy(*node, *node + s_buf_size(), Base::m_get_tp_allocator());
        if (first.m_node != last.m_node)
        {
            ft::destroy(first.m_cur, first.m_last, Base::m_get_tp_allocator());
            ft::destroy(last.m_first, last.m_cur, Base::m_get_tp_allocator());
        }
        else
        {
            ft::destroy(first.m_cur, last.m_cur, Base::m_get_tp_allocator());
        }
    }

    void m_reserve_map_at_front(size_t nodes_to_add = 1)
    {
        if (nodes_to_add > size_t(this->m_impl.m_start.m_node - this->m_impl.m_map))
            m_reallocate_map(nodes_to_add, true);
    }

    void m_reserve_map_at_back(size_t nodes_to_add = 1)
    {
        if (nodes_to_add > this->m_impl.m_map_size
            - (this->m_impl.m_finish.m_node - this->m_impl.m_map + 1))
            m_reallocate_map(nodes_to_add, false);
    }

    iterator m_reserve_elems_at_front(size_t n)
    {
        const size_t vacancies = this->m_impl.m_start.m_cur
            - this->m_impl.m_start.m_first;
        if (n > vacancies)
            m_new_elems_at_front(n - vacancies);
        return (this->m_impl.m_start - difference_type(n));
    }

    iterator m_reserve_elems_at_back(size_t n)
    {
        const size_t vacancies = this->m_impl.m_finish.m_last
            - this->m_impl.m_finish.m_cur - 1;
        if (n > vacancies)
            m_new_elems_at_back(n - vacancies);
        return (this->m_impl.m_finish + difference_type(n));
    }

    void m_new_elems_at_front(size_t new_elems)
    {
        if (this->max_size() - this->size() < new_elems)
            throw std::length_error("deque::M_new_elements_at_front");
        const size_t new_nodes = (new_elems + s_buf_size() - 1) / s_buf_size();
        m_reserve_map_at_front(new_nodes);
        size_t i;
        try
        {
            for (i = 1; i <= new_nodes; ++i)
                *(this->m_impl.m_start.m_node - i) = this->Base::m_allocate_node();
        }
        catch(...)
        {
            for (size_t j = 1; j < i; ++j)
                Base::m_deallocate_node(*(this->m_impl.m_start.m_node - j));
            throw ;
        }
    }

    void m_new_elems_at_back(size_t new_elems)
    {
        if (this->max_size() - this->size() < new_elems)
            throw std::length_error("deque::M_new_elements_at_back");
        const size_t new_nodes = (new_elems + s_buf_size() - 1) / s_buf_size();
        m_reserve_map_at_back(new_nodes);
        size_t i;
        try
        {
            for (i = 1; i <= new_nodes; ++i)
                *(this->m_impl.m_finish.m_node + i) = this->Base::m_allocate_node();
        }
        catch(...)
        {
            for (size_t j = 1; j < i; ++j)
                Base::m_deallocate_node(*(this->m_impl.m_finish.m_node + j));
            throw ;
        }
    }

    void m_reallocate_map(size_t nodes_to_add, bool add_at_front)
    {
        const size_t old_num_nodes = this->m_impl.m_finish.m_node
            - this->m_impl.m_start.m_node + 1;
        const size_t new_num_nodes = old_num_nodes + nodes_to_add;

        Map_pointer new_nstart;
        if (this->m_impl.m_map_size > 2 * new_num_nodes)
        {
            new_nstart = this->m_impl.m_map + (this->m_impl.m_map_size - new_num_nodes) / 2
                + (add_at_front ? nodes_to_add : 0);
            if (new_nstart < this->m_impl.m_start.m_node)
                std::copy(this->m_impl.m_start.m_node,
                    this->m_impl.m_finish.m_node + 1, new_nstart);
            else
                std::copy_backward(this->m_impl.m_start.m_node,
                    this->m_impl.m_finish.m_node + 1, new_nstart + old_num_nodes);
        }
        else
        {
            size_t new_map_size = this->m_impl.m_map_size
                + ft::max(this->m_impl.m_map_size, nodes_to_add) + 2;
            Map_pointer new_map = this->Base::m_allocate_map(new_map_size);
            new_nstart = new_map + (new_map_size - new_num_nodes) / 2
                + (add_at_front ? nodes_to_add : 0);
            std::copy(this->m_impl.m_start.m_node, this->m_impl.m_finish.m_node + 1, new_nstart);
            Base::m_deallocate_map(this->m_impl.m_map, this->m_impl.m_map_size);
            
            this->m_impl.m_map = new_map;
            this->m_impl.m_map_size = new_map_size;
        }
        this->m_impl.m_start.m_set_node(new_nstart);
        this->m_impl.m_finish.m_set_node(new_nstart + old_num_nodes - 1);
    }
};

template<typename Tp, typename Alloc>
inline bool operator==(const Deque<Tp, Alloc>& x, const Deque<Tp, Alloc>& y)
{ return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin())); }

template<typename Tp, typename Alloc>
inline bool operator!=(const Deque<Tp, Alloc>& x, const Deque<Tp, Alloc>& y)
{ return !(x == y); }

template<typename Tp, typename Alloc>
inline bool operator<(const Deque<Tp, Alloc>& x, const Deque<Tp, Alloc>& y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template<typename Tp, typename Alloc>
inline bool operator>(const Deque<Tp, Alloc>& x, const Deque<Tp, Alloc>& y)
{ return (y < x); }

template<typename Tp, typename Alloc>
inline bool operator<=(const Deque<Tp, Alloc>& x, const Deque<Tp, Alloc>& y)
{ return !(y < x); }

template<typename Tp, typename Alloc>
inline bool operator>=(const Deque<Tp, Alloc>& x, const Deque<Tp, Alloc>& y)
{ return !(x < y); }
} // namespace ft

#endif /* FT_DEQUE_HPP */
