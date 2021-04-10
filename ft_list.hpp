#ifndef FT_LIST_HPP
# define FT_LIST_HPP

# include "ft_library.hpp"
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
 *      empty       clear
 *      size        clear
 *      max_size    clear
 *
 * Element access:
 *      front       clear
 *      back        clear
 * 
 * Modifiers:
 *      assign      clear
 *      push_front  clear
 *      pop_front   clear
 *      push_back   clear
 *      pop_back    clear
 *      insert      clear
 *      erase       clear
 *      swap        clear
 *      resize      clear
 *      clear       clear
 *      splice      clear
 *      remove      clear
 *      remove_if   clear
 *      unique      clear
 *      merge       clear
 *      sort        clear
 *      reverse     clear
 */

namespace ft
{
struct ListNodeBase
{
    ListNodeBase* m_next;
    ListNodeBase* m_prev;

    static void swap(ListNodeBase& x, ListNodeBase& y)
    {
        if (x.m_next == ft::addressof(x) && y.m_next == ft::addressof(y))
            return ;
        if (x.m_next != ft::addressof(x))
        {
            x.m_prev->m_next = ft::addressof(y);
            x.m_next->m_prev = ft::addressof(y);
        }
        if (y.m_next != ft::addressof(y))
        {
            y.m_prev->m_next = ft::addressof(x);
            y.m_next->m_prev = ft::addressof(x);
        }
        if (x.m_next == ft::addressof(x))
        {
            x.m_prev = ft::addressof(y);
            x.m_next = ft::addressof(y);
        }
        else if (y.m_next == ft::addressof(y))
        {
            y.m_prev = ft::addressof(x);
            y.m_next = ft::addressof(x);
        }
    }
    void m_reverse()
    {
        ListNodeBase* cur = this->m_prev;
        ListNodeBase* tmp;

        while (cur != this)
        {
            tmp = cur->m_prev;
            cur->m_prev = cur->m_next;
            cur->m_next = tmp;
            cur = tmp;
        }
        tmp = this->m_prev;
        this->m_prev = this->m_next;
        this->m_next = tmp;
    }

    void m_transfer(ListNodeBase* const first, ListNodeBase* const last)
    {
        ListNodeBase* last_node = last->m_prev;

        first->m_prev->m_next = last;
        last->m_prev->m_next = this;
        last->m_prev = first->m_prev;
        first->m_prev = this->m_prev;
        this->m_prev->m_next = first;
        this->m_prev = last_node;
    }

    void m_hook(ListNodeBase* x)
    {
        x->m_prev->m_next = this;
        this->m_prev = x->m_prev;
        this->m_next = x;
        x->m_prev = this;
    }
    void m_unhook()
    {
        this->m_prev->m_next = this->m_next;
        this->m_next->m_prev = this->m_prev;
    }
};

template<typename Tp>
struct ListNode : ft::ListNodeBase
{
    Tp m_data;

    Tp* m_valptr()
    { return ft::addressof(m_data); };
    Tp const* m_valptr() const
    { return ft::addressof(m_data); };
};

template<typename Tp>
class ListIterator
{
public:
    typedef ListIterator<Tp>                Self;
    typedef ListNode<Tp>                    Node;
    typedef long                            dirrerence_type;
    typedef std::bidirectional_iterator_tag interator_category;
    typedef Tp                              value_type;
    typedef Tp*                             pointer;
    typedef Tp&                             reference;

    ListIterator() : m_node() {}
    ListIterator(ft::ListNodeBase* x) : m_node(x) {}

    Self m_const_cast() const
    { return *this; }

    reference operator*() const
    { return *static_cast<Node*>(m_node)->m_valptr(); }

    pointer operator->() const
    { return static_cast<Node*>(m_node)->m_valptr(); }

    Self& operator++()
    { m_node = m_node->m_next; return *this; }

    Self operator++(int)
    { Self tmp = *this; m_node = m_node->m_next; return tmp; }

    Self& operator--()
    { m_node = m_node->m_prev; return *this; }

    Self operator--(int)
    { Self tmp = *this; m_node = m_node->m_prev; return tmp; }

    bool operator==(const Self& x) const
    { return (m_node == x.m_node); }

    bool operator!=(const Self& x) const
    { return (m_node != x.m_node); }

    ft::ListNodeBase* m_node;
};

template<typename Tp>
class ListConstIterator
{
public:
    typedef ListConstIterator<Tp>           Self;
    typedef ListNode<Tp>                    Node;
    typedef ListIterator<Tp>                iterator;
    typedef long                            dirrerence_type;
    typedef std::bidirectional_iterator_tag interator_category;
    typedef Tp                              value_type;
    typedef Tp*                             pointer;
    typedef Tp&                             reference;

    ListConstIterator() : m_node() {}
    ListConstIterator(const ft::ListNodeBase* x) : m_node(x) {}
    ListConstIterator(const iterator& x) : m_node(x.m_node) {}

    iterator m_const_cast() const
    { return iterator(const_cast<ft::ListNodeBase*>(m_node)); }

    reference operator*() const
    { return *(static_cast<Node*>(m_node)->m_valptr()); }

    pointer operator->() const
    { return static_cast<Node*>(m_node)->m_valptr(); }

    Self& operator++()
    { m_node = m_node->m_next; return *this; }

    Self operator++(int)
    { Self tmp = *this; m_node = m_node->m_next; return tmp; }

    Self& operator--()
    { m_node = m_node->m_prev; return *this; }

    Self operator--(int)
    { Self tmp = *this; m_node = m_node->m_prev; return tmp; }

    bool operator==(const Self& x) const
    { return (m_node == x.m_node); }

    bool operator!=(const Self& x) const
    { return (m_node != x.m_node); }

    const ft::ListNodeBase* m_node;
};

template<typename Val>
inline bool operator==(const ListIterator<Val>& x,
                       const ListConstIterator<Val>& y)
{ return (x.m_node == y.m_node); }

template<typename Val>
inline bool operator!=(const ListIterator<Val>& x,
                       const ListConstIterator<Val>& y)
{ return (x.m_node != y.m_node); }

template<typename Tp, typename Alloc>
class ListBase
{
public:
    typedef Alloc                                   Alloc_type;
    typedef typename std::allocator<Alloc>::template
    rebind<Tp>::other                               Tp_alloc_type;
    typedef typename Tp_alloc_type::template
    rebind<ft::ListNode<Tp> >::other                Node_alloc_type;
    typedef Tp                                      value_type;
    typedef typename Node_alloc_type::pointer       pointer;

    struct List_impl : public Node_alloc_type
    {
        ft::ListNodeBase m_node;

        List_impl() : Node_alloc_type(), m_node() {}
        List_impl(const Node_alloc_type& a)
            : Node_alloc_type(a), m_node() {}
    };

    ListBase() : m_impl() { m_init(); }
    ListBase(const Node_alloc_type& a) : m_impl(a) { m_init(); }

    ~ListBase() { m_clear(); }

    static size_t s_distance(ft::ListNodeBase* first, ft::ListNodeBase* last)
    {
        size_t n = 0;
        while (first != last)
        {
            first = first->m_next;
            ++n;
        }
        return n;
    }
    void m_init()
    {
        m_impl.m_node.m_next = ft::addressof(m_impl.m_node);
        m_impl.m_node.m_prev = ft::addressof(m_impl.m_node);
    }
    void m_clear()
    {
        ft::ListNodeBase* cur = m_impl.m_node.m_next;
        while (cur != &m_impl.m_node)
        {
            ft::ListNode<Tp>* tmp = static_cast<ft::ListNode<Tp>*>(cur);
            cur = tmp->m_next;
            value_type* val = tmp->m_valptr();
            Tp_alloc_type(m_get_node_allocator()).destroy(val);
            m_put_node(tmp);
        }
    }

    size_t m_node_count() const
    {
        return s_distance(m_impl.m_node.m_next,
            ft::addressof(m_impl.m_node));
    }

    pointer m_get_node() { return m_impl.allocate(1); }; // ListNode 로 allocate

    void m_put_node(pointer p) { return m_impl.deallocate(p, 1); };

    Node_alloc_type& m_get_node_allocator()
    { return m_impl; };

    const Node_alloc_type& m_get_node_allocator() const
    { return m_impl; };

    List_impl m_impl;
};

template<typename Tp, typename Alloc = std::allocator<Tp> >
class List : public ListBase<Tp, Alloc>
{
public:
    typedef Alloc                                   Alloc_type;
    typedef ListBase<Tp, Alloc>                     Base;
    typedef typename Base::Tp_alloc_type            Tp_alloc_type;
    typedef typename Base::Node_alloc_type          Node_alloc_type;
    typedef Tp                                      value_type;
    typedef typename Tp_alloc_type::pointer         pointer;
    typedef typename Tp_alloc_type::const_pointer   const_pointer;
    typedef typename Tp_alloc_type::reference       reference;
    typedef typename Tp_alloc_type::const_reference const_reference;
    typedef ft::ListIterator<Tp>                    iterator;
    typedef ft::ListConstIterator<Tp>               const_iterator;
    typedef ft::ReverseIterator<iterator>           reverse_iterator;
    typedef ft::ReverseIterator<const_iterator>     const_reverse_iterator;

    List() : Base() {}
    List(const Alloc_type& a) : Base(Node_alloc_type(a)) {};
    List(size_t n, const value_type* x = value_type(),
        const Alloc_type& a = Alloc_type())
        : Base(Node_alloc_type(a))
    { m_fill_initialize(n, x); }
    template<typename InputIter>
    List(InputIter first, InputIter last, const Alloc_type& a = Alloc_type())
        : Base(Node_alloc_type(a))
    {
        typedef typename ft::is_integer<InputIter>::type Integral;
        m_initialize_dispatch(first, last, Integral());
    }
    List(const List& x) : Base(x.m_get_node_allocator()) //problem copy
    { m_initialize_dispatch(x.begin().m_const_cast(),
        x.end().m_const_cast(), ft::FalseType()); }

    List& operator=(const List& x)
    {
        this->Base::m_clear();
        this->Base::m_init();
        m_initialize_dispatch(x.begin().m_const_cast(),
        x.end().m_const_cast(), ft::FalseType());
        return (*this);
    }

    iterator begin()
    { return iterator(this->m_impl.m_node.m_next); }

    const_iterator begin() const
    { return const_iterator(this->m_impl.m_node.m_next); }

    iterator end()
    { return iterator(ft::addressof(this->m_impl.m_node)); }

    const_iterator end() const
    { return const_iterator(ft::addressof(this->m_impl.m_node)); }

    reverse_iterator rbegin()
    { return reverse_iterator(end()); }

    const reverse_iterator rbegin() const
    { return const_reverse_iterator(end()); }

    reverse_iterator rend()
    { return reverse_iterator(begin()); }

    const reverse_iterator rend() const
    { return const_reverse_iterator(begin()); }

    bool empty() const
    { return (this->m_impl.m_node.m_next == ft::addressof(this->m_impl.m_node)); }

    size_t size() const
    { return this->m_node_count(); }
    
    size_t max_size() const
    { return Node_alloc_type::max_size(); }

    void resize(size_t new_size, value_type x = value_type())
    {
        const_iterator i = m_resize_pos(new_size);
        if (new_size)
            insert(end(), new_size, x);
        else
            erase(i.m_const_cast(), end());
    }

    reference front()
    { return *begin(); }

    const_reference front() const
    { return *begin(); }

    reference back()
    { iterator tmp = end(); --tmp; return *tmp; }

    const reference back() const
    { const_iterator tmp = end(); --tmp; return *tmp; }

    void push_front(const value_type& x)
    { this->m_insert(begin(), x); }

    void push_back(const value_type& x)
    { this->m_insert(end(), x); }

    void pop_front()
    { this->m_erase(begin()); }

    void pop_back()
    { this->m_earse(iterator(this->m_impl.m_node.m_prev)); }

    void assign(size_t n, const value_type& val) { m_fill_assign(n, val); }

    template<typename InputIter>
    void assign(InputIter first, InputIter last)
    {
        typedef typename ft::is_integer<InputIter>::type Integral;
        m_assign_dispatch(first, last, Integral());
    }
    iterator insert(iterator pos, const value_type& x)
    { m_insert(pos, x); }

    void insert(iterator pos, size_t n, const value_type& x)
    {
        List tmp(n, x, get_allocator());
        splice(pos, tmp);
    }
    template<typename InputIter>
    void insert(iterator pos, InputIter first, InputIter last)
    {
        List tmp(first, last, get_allocator());
        splice(pos, tmp);
    }

    iterator erase(iterator pos)
    {
        iterator ret = iterator(pos->m_next);
        m_erase(pos);
        return ret;
    }

    iterator erase(iterator first, iterator last)
    {
        while (first != last)
            first = erase(first);
        return last;
    }

    void swap(List& x)
    {
        ft::ListNodeBase::swap(this->m_impl.m_node, x.m_impl.m_node);
        typename Base::List_impl tmp;
        tmp = this->m_impl;
        this->m_impl = x.m_impl;
        x.m_impl = tmp;
    }

    void clear()
    { this->Base::m_clear(); this->Base::m_init(); }

    void splice(iterator pos, List& x)
    {
        if (!x.empty())
        {
            m_check_equal_allocator(Base::m_get_node_allocator(),
                x.Base::m_get_node_allocator());
            pos.m_node->m_transfer(x.begin().m_node, x.end().m_node);
        }
    }

    void splice(iterator pos, List& x, iterator i)
    {
        iterator j = i;

        ++j;
        if (pos == i || pos == j)
            return ;
        if (this != ft::addressof(x))
            m_check_equal_allocator(Base::m_get_node_allocator(),
                x.Base::m_get_node_allocator());
        this->m_transfer(pos, i, j);
    }
    void splice(iterator pos, List& x, iterator first, iterator last)
    {
        if (first != last)
        {
            if (this != ft::addressof(x))
                m_check_equal_allocator(Base::m_get_node_allocator(),
                    x.Base::m_get_node_allocator());
            this->m_transfer(pos, first, last);
        }
    }

    void remove(const Tp& value)
    {
        for (iterator i = begin(); i != end(); )
        {
            if (*i == value)
                i = erase(i);
            else
                ++i;
        }
    }

    template<typename Predicate>
    void remove_if(Predicate pred)
    {
        for (iterator i = begin(); i != end(); )
        {
            if (pred(*i))
                i = erase(i);
            else
                ++i;
        }
    }

    void unique()
    {
        iterator first = begin();
        iterator last = end();

        if (first == last)
            return ;
        iterator next = first;
        while (++next != last)
        {
            if (*first == *next)
                erase(next);
            else
                first = next;
            next = first;
        }
    }

    template<typename BinaryPredicate>
    void unique(BinaryPredicate binary_pred)
    {
        iterator first = begin();
        iterator last = end();
        if (first == last)
            return ;
        iterator next = first;
        while (++next != last)
        {
            if (binary_pred(*first, *last))
                erase(next);
            else
                first = next;
            next = first;
        }
    }

    void merge(List& x)
    {
        if (this != ft::addressof(x))
        {
            m_check_equal_allocator(Base::m_get_node_allocator(),
                x.Base::m_get_node_allocator());
            iterator first1 = this->begin();
            iterator last1 = this->end();
            iterator first2 = x.begin();
            iterator last2 = x.end();

            while (first1 != last1 && first2 != last2)
            {
                if (*first1 > *first2)
                {
                    iterator tmp = first2;
                    this->m_transfer(first1, first2, ++tmp);
                    first2 = tmp;
                }
                else
                {
                    ++first1;
                }
            }
            if (first2 != last2)
            {
                this->m_transfer(first1, first2, last2);
            }
        }
    }

    template<typename Compare>
    void merge(List& x, Compare comp)
    {
        if (this != ft::addressof(x))
        {
            m_check_equal_allocator(Base::m_get_node_allocator(),
                x.Base::m_get_node_allocator());
            iterator first1 = this->begin();
            iterator last1 = this->end();
            iterator first2 = x.begin();
            iterator last2 = x.end();

            while (first1 != last1 && first2 != last2)
            {
                if (comp(*first2, *first1))
                {
                    iterator tmp = first2;
                    this->m_transfer(first1, first2, ++tmp);
                    first2 = tmp;
                }
                else
                {
                    ++first1;
                }
            }
            if (first2 != last2)
            {
                this->m_transfer(first1, first2, last2);
            }
        }
    }

    void sort()
    {
        if (this->m_impl.m_node.m_next == this->m_impl.m_node.m_prev)
            return ;
        List carry;
        List tmp[64];
        List* last = tmp;
        List* counter;
        try
        {
            do
            {
                carry.splice(carry.begin(), *this, this->begin());
                for (counter = tmp; counter != last && !counter->empty();
                    ++counter)
                {
                    counter->merge(carry);
                    carry.swap(*counter);
                }
                carry.swap(*counter);
                if (counter == last)
                    ++last;
            }
            while ( !this->empty() );
            for (counter = tmp + 1; counter != last; ++counter)
                counter->merge(*(counter - 1));
            swap(*(last - 1));
        }
        catch(...)
        {
            this->splice(this->end(), carry);
            for (int i = 0; i < sizeof(tmp) / sizeof(tmp[0]); ++i)
                this->splice(this->end(), tmp[i]);
            throw ;
        }
        
    }
    template<typename Compare>
    void sort(Compare comp)
    {
        if (this->m_impl.m_node.m_next == this->m_impl.m_node.m_prev)
            return ;
        List carry;
        List tmp[64];
        List* last = tmp;
        List* counter;

        try
        {
            do
            {
                carry.splice(carry.begin(), *this, this->begin());
                for (counter = tmp; counter != last && !counter->empty();
                    ++counter)
                {
                    counter->merge(carry, comp);
                    carry.swap(*counter);
                }
                carry.swap(*counter);
                if (counter == last)
                    ++last;
            }
            while (!empty());
            
            for (counter = tmp + 1; counter != last; ++counter)
                counter->merge(*(counter - 1), comp);
            swap(*(last - 1));
        }
        catch(...)
        {
            this->splice(this->end(), carry);
            for (int i = 0; i < sizeof(tmp) / sizeof(tmp[0]); ++i)
                this->splice(this->end(), tmp[i]);
            throw ;
        }
    }
    void reverse()
    { this->m_impl.m_node.m_reverse(); }

    Alloc_type get_allocator() const
    { return Alloc_type(Base::m_get_node_allocator()); }

protected:
    typedef ft::ListNode<Tp>                        Node;

    Node* m_create_node(const value_type& x)
    {
        Node* p = this->Base::m_get_node();
        try
        {
            Tp_alloc_type alloc(Base::m_get_node_allocator());
            alloc.construct(p->m_valptr(), x);
        }
        catch(...)
        {
            this->Base::m_put_node(p);
            throw ;
        }
        return p;
    }
    template<typename Integer>
    void m_initialize_dispatch(Integer n, Integer x, ft::TrueType)
    {
        m_fill_initialize(static_cast<size_t>(n), x);
    }
    template<typename InputIter>
    void m_initialize_dispatch(InputIter first, InputIter last, ft::FalseType)
    {
        for (; first != last; ++first)
            push_back(*first);
    }
    void m_fill_initialize(size_t n, const value_type& x)
    {
        while (n--)
            push_back(x);
    }

    void m_insert(iterator pos, const value_type& x)
    {
        Node* tmp = m_create_node(x);
        tmp->m_hook(pos.m_node);
    }
    void m_fill_assign(size_t n, const value_type& val)
    {
        iterator i = begin();
        for (; i != end(); ++i, --n)
            *i = val;
        if (n > 0)
            insert(end(), n, val);
        else
            erase(i, end());
    }
    void m_erase(iterator pos)
    {
        pos->m_node.m_unhook();
        Node* tmp = static_cast<Node*>(pos.m_node);
        Tp_alloc_type(Base::m_get_node_allocator()).destroy(tmp->m_valptr());
        m_put_node(tmp);
    }
    void m_transfer(iterator pos, iterator first, iterator last)
    {
        pos.m_node->m_transfer(first.m_node, last.m_node);
    }
    const_iterator m_resize_pos(size_t& new_size)
    {
        const_iterator i;
        size_t len = 0;
        for (i = begin(); i != end() && len < new_size; ++i, ++len);
        new_size -= len;
        return i;
    }    

    template<typename Alloc1, typename Alloc2>
    void m_check_equal_allocator(const Alloc1&, const Alloc2&)
    {
        typedef typename ft::is_same<Alloc1, Alloc2>      Tf;

        ft::do_throw<!Tf::value>();
    }
};
} // namespace ft

#endif /* FT_LIST_HPP */