#ifndef FT_DEQUE_HPP
# define FT_DEQUE_HPP

# include <memory>
# include <iostream>

/**
 * member functions
 * Iterators:
 *      begin
 *      end
 *      rbegin
 *      rend
 * 
 * Capacity:
 *      size
 *      max_size
 *      resize
 *      empty
 * 
 * Element access:
 *      operator[]
 *      at
 *      front
 *      back
 * 
 * Modifiers:
 *      assign
 *      push_back
 *      push_front
 *      pop_back
 *      pop_front
 *      insert
 *      erase
 *      swap
 *      clear
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
    typedef ptrdiff_t                               difference_type;

    static size_t s_buf_size()
    { return ft::deque_buf_size(sizeof(Tp)); }

    DequeIterator(Elt_pointer x, Map_pointer y)
        : m_cur(x), m_first(*y), m_last(*y + s_buf_size()), m_node(y) {};
    
    DequeIterator() :
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
                : -difference_type(-offset - 1) / s_buf_size()) - 1;
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
    { Self tmp = *this; retun (tmp -= n); }

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
    DequeBase(const Alloc_type& a) : m_impl(a) {}

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

    enum { s_initial_map_size = 8 };

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

    void m_dealloc_map(Map_pointer p, size_t n)
    {
        Map_alloc_type map_alloc = m_get_map_allocator();
        map_alloc.deallocate(p, n);
    }

    void m_initialize_map(size_t num_elems)
    {
        const size_t num_nodes = num_elems / deque_buf_size(sizeof(Tp)) + 1;

        this->m_impl.m_map_size = std::max(
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
            m_dealloc_map(this->m_impl.m_map, this->m_impl.m_map_size);
            this->m_impl.m_map = Map_pointer();
            this->m_impl.m_map_size = 0;
            throw ;
        }
        this->m_impl.m_start.m_set_node(n_start);
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
public:

};
} // namespace ft

#endif /* FT_DEQUE_HPP */