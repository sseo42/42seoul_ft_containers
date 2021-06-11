#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

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
 *      capacity    clear
 *      empty       clear
 *      reserve     clear
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
 *      pop_back    clear
 *      insert      clear
 *      erase       clear
 *      swap        clear
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
        std::swap(m_impl.m_start, x.m_start);
        std::swap(m_impl.m_finish, x.m_finish);
        std::swap(m_impl.m_end_of_storage, x.m_end_of_storage);
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
            size_t(this->m_impl.m_end_of_storage - this->m_impl.m_start));
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
        return size_t(this->m_impl.m_end_of_storage - this->m_impl.m_start);
    }

    void clear()
    {
        m_erase_at_end(this->m_impl.m_start);
    }

    void assign(size_t n, const value_type& val)
    { m_fill_assign(n, val); }

    void resize(size_t new_size, value_type x = value_type())
    {
        if (new_size > size())
            m_fill_insert(end(), new_size - size(), x);
        else if (new_size < size())
            m_erase_at_end(this->m_impl.m_start + new_size);
    }

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

    bool empty() const
    { return (begin() == end()); }

    void reserve(size_t n)
    {
        if (n > max_size())
            throw std::length_error("vector::reserve");
        if (this->capacity() < n)
        {
            pointer new_start = Base::m_allocate(n);
            pointer new_finish = std::uninitialized_copy(this->m_impl.start,
                this->m_impl.m_finish, new_start);
            ft::destroy(this->m_impl.m_start, this->m_impl.m_finish,
                Base::m_get_tp_allocator());
            Base::m_deallocate(this->m_impl.m_start,
                size_t(this->m_impl.m_end_of_storage - this->m_impl.start));
            this->m_impl.m_start = new_start;
            this->m_impl.m_finish = new_finish;
            this->m_impl.m_end_of_storage = new_start + n;
        }
    }

    reference operator[](size_t n)
    { return *(this->m_impl.m_start + n); }

    const reference operator[](size_t n) const
    { return *(this->m_impl.m_start + n); }

    reference at(size_t n)
    {
        if (n >= this->size())
            throw std::length_error("vector::at");
        return (*this)[n];
    }

    const reference at(size_t n) const
    {
        if (n >= this->size())
            throw std::length_error("vector::at");
        return (*this)[n];
    }

    reference front()
    { return *begin(); }

    const reference front() const
    { return *begin(); }

    reference back()
    { return *(end() - 1); }

    const reference back() const
    { return *(end() - 1); }

    void pop_back()
    { m_erase_at_end(this->m_impl.m_finish - 1); }

    iterator insert(iterator pos, const value_type& x)
    {
        size_t len = std::distance(begin(), pos);
        m_fill_insert(pos, 1, x);
        return (begin() + len);
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

    iterator erase(iterator pos) //not detecting pos error
    {
        iterator cur = pos;
        while (1)
        {
            this->m_impl.destroy(ft::addressof(*cur));
            if (cur + 1 == end())
                break ;
            std::uninitialized_copy(cur + 1, cur + 2, cur);
            cur++;
        }
        --this->m_impl.m_finish;
        return (pos);
    }
    iterator erase(iterator first, iterator last)
    {
        size_t len = std::distance(first, last);
        iterator cur = first;
        if (first != last)
        {
            ft::destroy(first, last, Base::m_get_tp_allocator());
            while (last != end())
            {
                std::uninitialized_copy(last, last + 1, cur);
                this->m_impl.destroy(ft::addressof(*last));
                cur++;
                last++;
            }
            this->m_impl.m_finish -= len;
        }
        return first;
    }
    void swap(Vector& x)
    {
        Alloc one = this->m_get_tp_allocator();
        Alloc two = x.m_get_tp_allocator();
        Base::m_swap_data(x.m_impl);
        std::swap(one, two);
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
        std::uninitialized_fill_n(this->m_impl.m_start, n, val);
        this->m_impl.m_finish = this->m_impl.m_start + n;
    }
    template<typename Integer>
    void m_insert_dispatch(iterator pos, Integer n, Integer val, TrueType)
    {
        m_fill_insert(pos, n, val);
    }
    template<typename InputIter>
    void m_insert_dispatch(iterator pos, InputIter first, InputIter last, FalseType)
    {
        for (; first != last; ++first)
        {
            pos = insert(pos, *first);
            ++pos;
        }
    }
    void m_fill_insert(iterator pos, size_t n, const value_type& x)
    {
        if (n != 0)
        {
            if (size_t(this->m_impl.m_end_of_storage - this->m_impl.m_finish) >= n)
            {
                const size_t elems_after = std::distance(pos, end());
                pointer old_finish(this->m_impl.m_finish);
                if (elems_after > n)
                {
                    std::uninitialized_copy(this->m_impl.m_finish - n,
                        this->m_impl.m_finish, this->m_impl.m_finish);
                    this->m_impl.m_finish += n;
                    ft::destroy(old_finish - elems_after + n, old_finish,
                        Base::m_get_tp_allocator());
                    std::uninitialized_copy(pos, pos + elems_after - n,
                        old_finish - elems_after + n);
                    ft::fill(pos, pos + n, x);
                }
                else
                {
                    std::uninitialized_fill_n(this->m_impl.m_finish, n - elems_after, x);
                    this->m_impl.m_finish += n - elems_after;
                    std::uninitialized_copy(this->m_impl.m_finish - n,
                        old_finish, this->m_impl.m_finish);
                    this->m_impl.m_finish += elems_after;
                    ft::fill(pos, pos + n, x);
                }
            }
            else
            {
                const size_t len = m_check_len(n, "vector:: m_default_append");
                const size_t elems_before = std::distance(begin(), pos);
                pointer new_start(this->m_allocate(len));
                pointer new_finish(new_start);
                try
                {
                    std::uninitialized_fill_n(new_start + elems_before, n, x);
                    new_finish = pointer();
                    new_finish = std::uninitialized_copy(this->begin(), pos, new_start);
                    new_finish += n;
                    new_finish = std::uninitialized_copy(pos, this->end(), new_finish);
                }
                catch(...)
                {
                    if (!new_finish)
                        ft::destroy(new_start + elems_before,
                            new_start + elems_before + n, Base::m_get_tp_allocator());
                    else
                        ft::destroy(new_start, new_finish, Base::m_get_tp_allocator());
                    Base::m_deallocate(new_start, len);
                    throw ;
                }
                ft::destroy(this->m_impl.m_start, this->m_impl.m_finish,
                    Base::m_get_tp_allocator());
                Base::m_deallocate(this->m_impl.m_start,
                    size_t(this->m_impl.m_end_of_storage - this->m_impl.m_start));
                this->m_impl.m_start = new_start;
                this->m_impl.m_finish = new_finish;
                this->m_impl.m_end_of_storage = new_start + len;
            }
        }
    }
    void m_fill_assign(size_t n, const value_type& val)
    {
        if (n > capacity())
        {
            Vector tmp(n, val, Base::m_get_tp_allocator());
            Base::m_swap_data(tmp.m_impl);
        }
        else if (n > size())
        {
            ft::fill(begin(), end(), val);
            std::uninitialized_fill_n(this->m_impl.m_finish, n - size(), val);
        }
        else
        {
            m_erase_at_end(ft::fill_n(this->m_impl.m_start, n, val));
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
        try     //insert elem at pos and push back all data after pos
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
                this->m_impl.destroy(new_start + elems_before);
            else
                ft::destroy(new_start, new_finish, Base::m_get_tp_allocator());
            Base::m_deallocate(new_start, len);
            throw ;
        }
        ft::destroy(this->m_impl.m_start, this->m_impl.m_finish, Base::m_get_tp_allocator());
        Base::m_deallocate(this->m_impl.m_start,
            size_t(this->m_impl.m_end_of_storage - this->m_impl.m_start));
        this->m_impl.m_start = new_start;
        this->m_impl.m_finish = new_finish;
        this->m_impl.m_end_of_storage = this->m_impl.m_start + len;
    }
    size_t m_check_len(size_t n, const char* s)
    {
        if (max_size() - size() < n)
            throw std::length_error(s);
        const size_t len = size() + ft::max(size(), n);
        return ((len < size() || len > max_size()) ? max_size() : len);
    }
};
} // namespace ft


#endif /* FT_VECTOR_HPP */
