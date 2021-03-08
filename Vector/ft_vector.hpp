#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <iostream>
# include "ft_iter.hpp"
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
 *      resize
 *      capacity    clear
 *      empty
 *      reserve
 * 
 * Element access:
 *      operator[]
 *      at
 *      front
 *      back
 *      
 * Modifiers:
 *      assign      clear
 *      push_back   clear
 *      pop_back
 *      insert
 *      erase
 *      swap
 *      clear       clear
 */

namespace ft
{
template<typename Tp, typename Alloc>
class VectorBase
{
public:
    typedef Alloc                                   Alloc_type;
    typedef typename std::allocator<Alloc>::template
    rebind<Tp>::other                               Tp_Alloc_type;
    typedef typename Tp_Alloc_type::pointer         pointer;
    typedef typename Tp_Alloc_type::const_pointer   const_pointer;
    typedef typename Tp_Alloc_type::reference       reference;
    typedef typename Tp_Alloc_type::const_reference const_reference;

    struct VectorImpl : public Tp_Alloc_type
    {
        VectorImpl()
            : Tp_Alloc_type(), m_start(), m_finish(), m_end_of_storage() {}
        VectorImpl(const Tp_Alloc_type& a)
            : Tp_Alloc_type(a), m_start(), m_finish(), m_end_of_storage() {}
        ~VectorImpl() {}

        pointer m_start;
        pointer m_finish;
        pointer m_end_of_storage;
    };

    VectorBase() : m_impl() {}
    VectorBase(const Tp_Alloc_type& a) : m_impl(a) {}
    VectorBase(size_t n) : m_impl() { m_create_storage(n); }
    VectorBase(size_t n, const Tp_Alloc_type& a) : m_impl(a) { m_create_storage(n); }

    ~VectorBase() {}

    void    m_swap_data(VectorImpl& x)
    {
        std::swap(m_start, x.m_start);
        std::swap(m_finish, x.finish);
        std::swap(m_end_of_storage, x.m_end_of_storage);
    }

    pointer m_allocate(size_t n)
    { return (n != 0 ? m_impl.allocate(n) : pointer()); }

    void m_deallocate(pointer p, size_t n)
    { if (p) m_impl.deallocate(p, n); }

    Tp_Alloc_type& m_get_tp_allocator()
    { return *static_cast<Tp_Alloc_type*>(&this->m_impl); }

    const Tp_Alloc_type& m_get_tp_allocator() const
    { return *static_cast<const Tp_Alloc_type*>(&this->m_impl); }

    Alloc_type get_allocator() const
    { return Alloc_type(m_get_tp_allocator()); }

    VectorImpl m_impl;

protected:
    void m_create_storage(size_t n)
    {
        this->m_impl.m_start = this->m_allocate(n);
        this->m_impl.m_finish = this->m_impl.m_start;
        this->m_impl.m_end_of_storage = this->m_impl.m_start + n;
    }
};

template<typename Tp, typename Alloc = std::allocator<Tp> >
class Vector : public VectorBase<Tp, Alloc>
{
public:
    typedef VectorBase<Tp, Alloc>                   Base;
    typedef Alloc                                   Alloc_type;
    typedef Tp                                      value_type;
    typedef typename Base::pointer                  pointer;
    typedef typename Base::const_pointer            const_pointer;
    typedef typename Base::reference                reference;
    typedef typename Base::const_reference          const_reference;
    typedef NormalIterator<pointer, Vector>         iterator;
    typedef NormalIterator<const_pointer, Vector>   const_iterator;
    typedef ReverseIterator<iterator>               reverse_iterator;
    typedef ReverseIterator<const_iterator>         const_reverse_iterator;

    Vector() : Base() {}
    Vector(const Alloc_type& a) : Base(a) {}
    Vector(size_t n, const value_type& val = value_type(),
        const Alloc_type& a = Alloc_type())
        : Base(n, a)
    { m_fill_initialize(n, val); }
    Vector(const Vector& copy) : Base(copy.size(), copy.get_allocator())
    {
        this->m_impl.m_finish = std::uninitialized_copy(copy.begin(), 
                                copy.end(), this->m_impl.m_start);
    }
    template<typename InputIter>
    Vector(InputIter first, InputIter last,
        const Alloc_type& a = Alloc_type())
        : Base(a)
    {
         typedef typename ft::is_integer<InputIter>::type  Integral;
         m_initialize_dispatch(first, last, Integral());
    }

    ~Vector()
    {
        clear();
        Base::m_deallocate(this->m_impl.m_start,
            std::distance(this->m_impl.m_start, this->m_impl.m_end_of_storage)); // check
    }

    // Vector& operator=(const Vector& v)
    // {
    //     Base()
    // }

    iterator begin()
    { return iterator(this->m_impl.m_start); }

    const_iterator begin() const
    { return const_iterator(this->m_impl.m_start); }

    iterator end()
    { return iterator(this->m_impl.m_finish); }

    const_iterator end() const
    { return const_iterator(this->m_impl.m_finish); }

    reverse_iterator rbegin()
    { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const
    { return const_reverse_iterator(end()); }

    reverse_iterator rend()
    { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const
    { return const_reverse_iterator(begin()); }

    size_t size() const { return size_t(this->m_impl.m_finish - this->m_impl.m_start); }

    size_t max_size() const { return this->m_impl.max_size(); };

    size_t capacity() const
    {
        return std::distance(this->m_impl.m_start, this->m_impl.m_end_of_storage);
    }

    void clear()
    {
        m_erase_at_end(this->m_impl.m_start);
    }

    void assign(size_t n, const value_type& val)
    { m_fill_assign(n, val); }

    void push_back(const value_type& x)
    {
        if (this->m_impl.m_finish != this->m_impl.m_end_of_storage)
        {
            this->m_impl.construct(this->m_impl.m_finish, x);
            ++this->m_impl.m_finish;
        }
        else
        {
            m_realloc_insert(end(), x);
        }
    }

protected:
    template<typename Integer>
    void m_initialize_dispatch(Integer n, Integer val, TrueType)
    {
        this->m_impl.m_start = Base::m_allocate(static_cast<size_t>(n));
        this->m_impl.m_end_of_storage =
            this->m_impl.m_start + static_cast<size_t>(n);
        m_fill_initialize(static_cast<size_t>(n), val);
    }
    template<typename InputIter>
    void m_initialize_dispatch(InputIter first, InputIter last, FalseType)
    {
        typedef typename std::iterator_traits<InputIter>::iterator_category IterCategory;
        m_range_initialize(first, last, IterCategory());
    }
    template<typename InputIter>
    void m_range_initialize(InputIter first, InputIter last, std::input_iterator_tag)
    {
        try
        {
            for (; first != last; ++first)
                push_back(*first);
        }
        catch(...)
        {
            clear();
            throw ;
        }
    }
    template<typename InputIter>
    void m_range_initialize(InputIter first, InputIter last, std::forward_iterator_tag)
    {
        const size_t n = std::distance(first, last);
        this->m_impl.m_start = this->m_allocate(n);
        this->m_impl.m_end_of_storage = this->m_impl.m_start + n;
        this->m_impl.m_finish =
            std::uninitialized_copy(first, last, this->m_impl.m_start);
    }
    void m_fill_initialize(size_t n, const value_type& val)
    {
        this->m_impl.m_finish = std::uninitialized_fill_n(this->m_impl.m_start, n, val);
    }
    void m_fill_assign(size_t n, const value_type& val)
    {
        if (n > capacity())
        {
            Vector tmp(n, val, m_get_tp_allocator());
            Base::m_swap_data(tmp); //check here
        }
        else if (n > size())
        {
            std::fill(begin(), end(), val);
            std::uninitialized_fill_n(this.m_impl.m_finish, n - size(), val);
        }
        else
        {
            m_erase_at_end(std::fill_n(this->m_impl.m_start, n, val));
        }
    }
    void m_erase_at_end(pointer pos)
    {
        ft::destroy(pos, this->m_impl.m_finish, Base::m_get_tp_allocator());
        this->m_impl.m_finish = pos;
    }
    void m_realloc_insert(iterator pos, const value_type& x)
    {
        const size_t len = m_check_len(size_t(1), "Vector:: m_realloc_insert");
        const size_t elems_before = std::distance(this->begin(), pos);
        pointer new_start = this->m_allocate(len);
        pointer new_finish = new_start;
        try     //insert elem at pos and push all data after pos
        {
            this->m_impl.construct(new_start + elems_before, x);
            new_finish = pointer();
            new_finish = std::uninitialized_copy(this->begin(), pos, new_start);

            ++new_finish;
            new_finish = std::uninitialized_copy(pos.base(), this->m_impl.m_finish, new_finish);
        }
        catch(...)
        {
            if (!new_finish)
                this->m_impl.destroy(new_start + elems_before); //error by ++operator
            else
                ft::destroy(new_start, new_finish, Base::m_get_tp_allocator());
            Base::m_deallocate(new_start, len);
            throw ;
        }
        ft::destroy(this->m_impl.m_start, this->m_impl.m_finish, Base::m_get_tp_allocator());
        Base::m_deallocate(this->m_impl.m_start,
            std::distance(this->m_impl.m_start, this->m_impl.m_finish));
        this->m_impl.m_start = new_start;
        this->m_impl.m_finish = new_finish;
        this->m_impl.m_end_of_storage = this->m_impl.m_start + len;
    }
    size_t m_check_len(size_t n, const char* s)
    {
        if (max_size() - size() < n)
            throw std::length_error(s);
        const size_t len = size() + std::max(size(), n);
        return ((len < size() || len > max_size()) ? max_size() : len);
    }
};
} // namespace ft


#endif /* FT_VECTOR_HPP */