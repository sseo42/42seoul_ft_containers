#ifndef FT_RBTREE_HPP
# define FT_RBTREE_HPP

# include "ft_library.hpp"
# include "ft_pair.hpp"
# include "ft_iter.hpp"
# include <memory>

namespace ft
{
enum rbtree_color { Red = false, Black = true };

// it has color and {parent, left, right} node and has functions to get leftest rightest node
struct Rbtree_node_base // it 
{
    typedef Rbtree_node_base*               Base_ptr;
    typedef const Rbtree_node_base*         Const_Base_ptr;

    static Base_ptr s_minimum(Base_ptr x)
    {
        while (x->m_left != 0)
            x = x->m_left;
        return x;
    }
    static Const_Base_ptr s_minimum(Const_Base_ptr x)
    {
        while (x->m_left != 0)
            x = x->m_left;
        return x;
    }
    static Base_ptr s_maximum(Base_ptr x)
    {
        while (x->m_right != 0)
            x = x->m_right;
        return x;
    }
    static Const_Base_ptr s_maximum(Const_Base_ptr x)
    {
        while (x->m_right != 0)
            x = x->m_right;
        return x;
    }

    rbtree_color m_color;
    Base_ptr m_parent;
    Base_ptr m_left;
    Base_ptr m_right;
};

// it has compare function
template<typename Key_compare>
struct Rbtree_key_compare
{
    Rbtree_key_compare() : m_key_compare() {}
    Rbtree_key_compare(const Key_compare& comp) : m_key_compare(comp) {}

    Key_compare m_key_compare;
};

// it has header which type is node_base and node_count
struct Rbtree_header // 
{
    Rbtree_header()
    { m_header.m_color = Red; m_reset(); }

    void m_move_data(Rbtree_header& from)
    {
        m_header.m_color = from.m_header.m_color;
        m_header.m_parent = from.m_header.m_parent;
        m_header.m_left = from.m_header.m_left;
        m_header.m_right = from.m_header.m_right;
        m_header.m_parent->m_parent = ft::addressof(m_header);
        m_node_count = from.m_node_count;
        from.m_reset();
    }
    void m_reset()
    {
        m_header.m_parent = 0;
        m_header.m_left = ft::addressof(m_header);
        m_header.m_right = ft::addressof(m_header);
        m_node_count = 0;
    }

    Rbtree_node_base m_header;
    size_t m_node_count;
};

// node_base + val
template<typename Val>
struct Rbtree_node : public Rbtree_node_base
{
    typedef Rbtree_node<Val>*           Link_type;

    Val* m_valptr()
    { return ft::addressof(m_value_field); }

    const Val* m_valptr() const
    { return ft::addressof(m_value_field); }

    Val m_value_field;
};

static Rbtree_node_base* rbtree_increment(Rbtree_node_base* x)
{
    if (x->m_right != 0)
    {
        return Rbtree_node_base::s_minimum(x->m_right);
    }
    else
    {
        Rbtree_node_base* tmp;
        tmp = x->m_parent;
        while (tmp->m_right == x)
        {
            x = tmp;
            tmp = tmp->m_parent;
        }
        if (x->m_right != tmp)
            x = tmp;
        return x;
    }
}

static const Rbtree_node_base* rbtree_increment(const Rbtree_node_base* x)
{
    return rbtree_increment(const_cast<Rbtree_node_base*>(x));
}

static Rbtree_node_base* rbtree_decrement(Rbtree_node_base* x)
{
    if (x->m_color == Red && x->m_parent->m_parent == x)
    {
        return x->m_right;
    }
    else if (x->m_left != 0)
    {
        return Rbtree_node_base::s_maximum(x->m_left);
    }
    else
    {
        Rbtree_node_base* tmp;
        tmp = x->m_parent;
        while (tmp->m_left == x)
        {
            x = tmp;
            tmp = tmp->m_parent;
        }
        if (x->m_left != tmp)
            x = tmp;
        return x;
    }
}

static const Rbtree_node_base* rbtree_decrement(const Rbtree_node_base* x)
{
    return rbtree_decrement(const_cast<Rbtree_node_base*>(x));
}

// it has m_node which type is node_base*
template<typename Tp>
struct Rbtree_iterator
{
    typedef Rbtree_iterator<Tp>                 Self;
    typedef Rbtree_node_base::Base_ptr          Base_ptr;
    typedef Rbtree_node<Tp>*                    Link_type;

    typedef Tp                                  value_type;
    typedef Tp&                                 reference;
    typedef Tp*                                 pointer;
    typedef std::bidirectional_iterator_tag     iterator_category;
    typedef long                                difference_type;

    Rbtree_iterator() : m_node() {}

    Rbtree_iterator(Base_ptr x) : m_node(x) {}

    reference operator*() const
    { return *static_cast<Link_type>(m_node)->m_valptr(); }

    pointer operator->() const
    { return static_cast<Link_type>(m_node)->m_valptr(); }

    Self& operator++()
    { m_node = rbtree_increment(m_node); return *this; }

    Self operator++(int)
    { Self tmp = *this; m_node = rbtree_increment(m_node); return tmp; }

    Self& operator--()
    { m_node = rbtree_decrement(m_node); return *this; }

    Self operator--(int)
    { Self tmp = *this; m_node = rbtree_decrement(m_node); return tmp; }

    bool operator==(const Self& x) const
    { return m_node == x.m_node; }

    bool operator!=(const Self& x) const
    { return m_node != x.m_node; }

    Base_ptr m_node;
};

template<typename Tp>
struct Rbtree_const_iterator
{
    typedef Rbtree_const_iterator<Tp>           Self;
    typedef Rbtree_node_base::Const_Base_ptr    Base_ptr;
    typedef const Rbtree_node<Tp>*              Link_type;

    typedef Tp                                  value_type;
    typedef const Tp&                           reference;
    typedef const Tp*                           pointer;
    typedef Rbtree_iterator<Tp>                 iterator;
    typedef std::bidirectional_iterator_tag     iterator_category;
    typedef long                                difference_type;

    Rbtree_const_iterator() : m_node() {}
    Rbtree_const_iterator(Base_ptr x) : m_node(x) {}
    Rbtree_const_iterator(const iterator& it) : m_node(it.m_node) {}

    iterator m_const_cast() const
    { return iterator(const_cast<typename iterator::Base_ptr>(m_node)); }

    reference operator*() const
    { return *static_cast<Link_type>(m_node)->m_valptr(); }

    pointer operator->() const
    { return static_cast<Link_type>(m_node)->m_valptr(); }

    Self& operator++()
    { m_node = rbtree_increment(m_node); return *this; }

    Self operator++(int)
    { Self tmp = *this; m_node = rbtree_increment(m_node); return tmp; }

    Self& operator--()
    { m_node = rbtree_decrement(m_node); return *this; }

    Self operator--(int)
    { Self tmp = *this; m_node = rbtree_decrement(m_node); return tmp; }

    bool operator==(const Self& x) const
    { return m_node == x.m_node; }

    bool operator!=(const Self& x) const
    { return m_node != x.m_node; }
    
    Base_ptr m_node;
};

template<typename Val>
inline bool operator==(const Rbtree_iterator<Val>& x,
    const Rbtree_iterator<Val>& y)
{ return (x.m_node == y.m_node); }

template<typename Val>
inline bool operator!=(const Rbtree_iterator<Val>& x,
    const Rbtree_iterator<Val>& y)
{ return (x.m_node != y.m_node); }

static void rotate_right(Rbtree_node_base* x, Rbtree_node_base*& root)
{
    Rbtree_node_base* y = x->m_left;
    x->m_left = y->m_right;
    if (y->m_right)
    {
        y->m_right->m_parent = x;
    }
    if (x == root)
        root = y;
    else if (x->m_parent->m_left == x)
        x->m_parent->m_left = y;
    else
        x->m_parent->m_right = y;
    y->m_parent = x->m_parent;
    y->m_right = x;
    x->m_parent = y;
}

static void rotate_left(Rbtree_node_base* x, Rbtree_node_base*& root)
{
    Rbtree_node_base* y = x->m_right;
    x->m_right = y->m_left;
    if (y->m_left)
    {
        y->m_left->m_parent = x;
    }
    if (x == root)
        root = y;
    else if (x->m_parent->m_right == x)
        x->m_parent->m_right = y;
    else
        x->m_parent->m_left = y;
    y->m_parent = x->m_parent;
    y->m_left = x;
    x->m_parent = y;
}

// insert x into p's (insert_left) node keeping balance
// and update header's left, right and header's parent(root)
static void rbtree_insert_and_rebalance(const bool insert_left, Rbtree_node_base* x,
    Rbtree_node_base* p, Rbtree_node_base& header)
{
    Rbtree_node_base*& root = header.m_parent;
    x->m_parent = p;
    x->m_left = 0;
    x->m_right = 0;
    x->m_color = Red;

    if (insert_left)
    {
        p->m_left = x;
        if (p == &header)
        {
            header.m_parent = x;
            header.m_right = x;
        }
        else if (p == header.m_left)
            header.m_left = x;
    }
    else
    {
        p->m_right = x;
        if (p == header.m_right)
            header.m_right = x;
    }
    while (x != root && x->m_parent->m_color == Red)
    {
        Rbtree_node_base* const xxp = x->m_parent->m_parent;
        if (xxp->m_left == x->m_parent)
        {
            if (xxp->m_right && xxp->m_right->m_color == Red)
            {
                x->m_parent->m_color = Black;
                xxp->m_right->m_color = Black;
                xxp->m_color = Red;
                x = xxp;
            }
            else
            {
                if (x->m_parent->m_right == x)
                {
                    x = x->m_parent;
                    rotate_left(x, root);
                }
                x->m_parent->m_color = Black;
                xxp->m_color = Red;
                rotate_right(xxp, root);
            }
        }
        else
        {
            if (xxp->m_left && xxp->m_left->m_color == Red)
            {
                x->m_parent->m_color = Black;
                xxp->m_left->m_color = Black;
                xxp->m_color = Red;
                x = xxp;
            }
            else
            {
                if (x->m_parent->m_left == x)
                {
                    x = x->m_parent;
                    rotate_right(x, root);
                }
                x->m_parent->m_color = Black;
                xxp->m_color = Red;
                rotate_left(xxp, root);
            }
        }
    }
    root->m_color = Black;
}

// erase node keeping balance
static Rbtree_node_base* rbtree_rebalance_for_erase(Rbtree_node_base* const z, Rbtree_node_base& header)
{
    Rbtree_node_base*& root = header.m_parent;
    Rbtree_node_base*& leftmost = header.m_left;
    Rbtree_node_base*& rightmost = header.m_right;
    Rbtree_node_base* y = z;
    Rbtree_node_base* x = 0;
    Rbtree_node_base* x_parent = 0;

    if (y->m_right == 0)
    {
        x = y->m_left;
    }
    else if (y->m_left == 0)
    {
        x = y->m_right;
    }
    else
    {
        y = Rbtree_node_base::s_minimum(y->m_right);
        x = y->m_right;
    }
    if (y != z)
    {
        z->m_left->m_parent = y;
        y->m_left = z->m_left;
        if (y != z->m_right)
        {
            x_parent = y->m_parent;
            y->m_right = z->m_right;
            z->m_right->m_parent = y;
            if (x)
                x->m_parent = x_parent;
            x_parent->m_left = x;
        }
        else
        {
            x_parent = y;
        }
        if (root == z)
            root = y;
        else if (z->m_parent->m_left == z)
            z->m_parent->m_left = y;
        else
            z->m_parent->m_right = y;
        y->m_parent = z->m_parent;
        std::swap(y->m_color, z->m_color);
        y = z;
    }
    else
    {
        x_parent = y->m_parent;
        if (x)
            x->m_parent = y->m_parent;
        if (root == z)
            root = x;
        else if (z->m_parent->m_left == z)
            z->m_parent->m_left = x;
        else
            z->m_parent->m_right = x;
        if (leftmost == z)
        {
            if (z->m_right == 0)
                leftmost = z->m_parent;
            else
                leftmost = Rbtree_node_base::s_minimum(x);
        }
        if (rightmost == z)
        {
            if (z->m_left == 0)
                rightmost = z->m_parent;
            else
                rightmost = Rbtree_node_base::s_maximum(x);
        }
    }
    if (y->m_color != Red)
    {
        while (x != root && (x == 0 || x->m_color == Black))
        {
            if (x == x_parent->m_left)
            {
                Rbtree_node_base* w = x_parent->m_right;
                if (w && w->m_color == Red)
                {
                    w->m_color = Black;
                    x_parent->m_color = Red;
                    rotate_left(x_parent, root);
                    w = x_parent->m_right;
                }
                if (w == 0)
                {
                    x = x_parent;
                    x_parent = x_parent->m_parent;
                }
                else if ((w->m_right == 0 || w->m_right->m_color == Black)
                    && (w->m_left == 0 || w->m_left->m_color == Black))
                {
                    w->m_color = Red;
                    x = x_parent;
                    x_parent = x_parent->m_parent;
                }
                else
                {
                    if (w->m_right == 0 || w->m_right->m_color == Black)
                    {
                        w->m_left->m_color = Black;
                        w->m_color = Red;
                        rotate_right(w, root);
                        w = x_parent->m_right;
                    }
                    w->m_color = x_parent->m_color;
                    x_parent->m_color = Black;
                    if (w->m_right)
                        w->m_right->m_color = Black;
                    rotate_left(x_parent, root);
                    break ;
                }
            }
            else
            {
                Rbtree_node_base* w = x_parent->m_left;
                if (w && w->m_color == Red)
                {
                    w->m_color = Black;
                    x_parent->m_color = Red;
                    rotate_right(x_parent, root);
                    w = x_parent->m_left;
                }
                if (w == 0)
                {
                    x = x_parent;
                    x_parent = x_parent->m_parent;
                }
                else if ((w->m_right == 0 || w->m_right->m_color == Black)
                    && (w->m_left == 0 || w->m_left->m_color == Black))
                {
                    w->m_color = Red;
                    x = x_parent;
                    x_parent = x_parent->m_parent;
                }
                else
                {
                    if (w->m_left == 0 || w->m_left->m_color == Black)
                    {
                        w->m_right->m_color = Black;
                        w->m_color = Red;
                        rotate_left(w, root);
                        w = x_parent->m_left;
                    }
                    w->m_color = x_parent->m_color;
                    x_parent->m_color = Black;
                    if (w->m_left)
                        w->m_left->m_color = Black;
                    rotate_right(x_parent, root);
                    break ;
                }
            }
        }
        if (x)
            x->m_color = Black;
    }
    return y;
}

template<typename Key, typename Val, typename KeyOfValue,
    typename Compare, typename Alloc = std::allocator<Val> >
class Rbtree
{
public:
    typedef Alloc                               allocator_type;
    typedef typename std::allocator<Alloc>::template
    rebind<Rbtree_node<Val> >::other            Node_allocator;
    typedef Key                                 key_type;
    typedef Val                                 value_type;
    typedef value_type*                         pointer;
    typedef const value_type*                   const_pointer;
    typedef value_type&                         reference;
    typedef const value_type&                   const_reference;
    typedef long                                difference_type;
    typedef Rbtree_iterator<value_type>         iterator;
    typedef Rbtree_const_iterator<value_type>   const_iterator;
    typedef ft::ReverseIterator<iterator>       reverse_iterator;
    typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

protected:
    typedef Rbtree_node_base*                   Base_ptr;
    typedef const Rbtree_node_base*             Const_Base_ptr;
    typedef Rbtree_node<Val>*                   Link_type;
    typedef const Rbtree_node<Val>*             Const_Link_type;

public:
    Rbtree() {}
    Rbtree(const Compare& comp, const allocator_type& a = allocator_type())
        : m_impl(comp, Node_allocator(a)) {}
    Rbtree(const Rbtree& x) : m_impl(x.m_impl)
    { if (x.m_root() != 0) m_root() = m_copy(x); }

    ~Rbtree()
    { m_erase(m_begin()); }

    Rbtree& operator=(const Rbtree& x)
    {
        if (this != ft::addressof(x))
        {
            Reuse_or_alloc_node roan(*this);
            m_impl.m_reset();
            m_impl.m_key_compare = x.m_impl.m_key_compare;
            if (x.m_root() != 0)
                m_root() = m_copy(x, roan);
        }
        return *this;
    }

    Compare key_comp() const
    { return m_impl.m_key_compare; }

    iterator begin()
    { return iterator(this->m_impl.m_header.m_left); }

    const_iterator begin() const
    { return const_iterator(this->m_impl.m_header.m_left); }

    iterator end()
    { return iterator(&this->m_impl.m_header); }

    const_iterator end() const
    { return const_iterator(&this->m_impl.m_header); }

    reverse_iterator rbegin()
    { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const
    { return const_reverse_iterator(end()); }

    reverse_iterator rend()
    { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const
    { return const_reverse_iterator(begin()); }

    bool empty() const
    { return (m_impl.m_node_count == 0); }

    size_t size() const
    { return m_impl.m_node_count; }

    size_t max_size() const
    { return m_get_node_allocator().max_size(); } // check

    void swap(Rbtree& x)
    {
        if (m_root() == 0)
        {
            if (x.m_root() != 0)
                m_impl.m_move_data(x.m_impl);
        }
        else if (x.m_root() == 0)
        {
            x.m_impl.m_move_data(m_impl);
        }
        else
        {
            std::swap(m_root(), x.m_root());
            std::swap(m_leftmost(), x.m_leftmost());
            std::swap(m_rightmost(), x.m_rightmost());
            m_root()->m_parent = m_end();
            x.m_root()->m_parent = x.m_end();
            std::swap(this->m_impl.m_node_count, x.m_impl.m_node_count);
        }
        std::swap(this->m_impl.m_key_compare, x.m_impl.m_key_compare);
        std::swap(m_get_node_allocator(), x.m_get_node_allocator());
    }

    Node_allocator& m_get_node_allocator()
    { return *static_cast<Node_allocator*>(&this->m_impl); }

    const Node_allocator& m_get_node_allocator() const
    { return *static_cast<const Node_allocator*>(&this->m_impl); }

    allocator_type get_allocator() const
    { return allocator_type(m_get_node_allocator()); }

    // get the position for k, return <pos_to_insert, parent node>
    // if there is a node 'pos' with same k return <pos, 0>
    ft::Pair<Base_ptr, Base_ptr> m_get_insert_unique_pos(const key_type& k)
    {
        typedef ft::Pair<Base_ptr, Base_ptr>    Res;
        Link_type x = m_begin();
        Base_ptr y = m_end();
        bool comp = true;
        while (x != 0)
        {
            y = x;
            comp = m_impl.m_key_compare(k, s_key(x));
            x = comp ? s_left(x) : s_right(x);
        }
        iterator it = iterator(y);
        if (comp)
        {
            if (it == begin())
                return Res(x, y);
            else
                --it;
        }
        if (m_impl.m_key_compare(s_key(it.m_node), k))
            return Res(x, y);
        return Res(it.m_node, 0);
    }

    // get the position for k allowing same k
    ft::Pair<Base_ptr, Base_ptr> m_get_insert_equal_pos(const key_type& k)
    {
        typedef ft::Pair<Base_ptr, Base_ptr>    Res;
        Link_type x = m_begin();
        Base_ptr y = m_end();
        while (x != 0)
        {
            y = x;
            x = m_impl.m_key_compare(k, s_key(x)) ? s_left(x) : s_right(x);
        }
        return Res(x, y);
    }

    // same as m_get_insert_unique_pos but use a hint 'position'
    ft::Pair<Base_ptr, Base_ptr> m_get_insert_hint_unique_pos(const_iterator position, const key_type& k)
    {
        typedef ft::Pair<Base_ptr, Base_ptr>    Res;
        iterator pos = position.m_const_cast();
        if (pos.m_node == m_end())
        {
            if (size() > 0 && this->m_impl.m_key_compare(s_key(m_rightmost()), k))
                return Res(0, m_rightmost());
            else
                return m_get_insert_unique_pos(k);
        }
        else if (this->m_impl.m_key_compare(k, s_key(pos.m_node)))
        {
            iterator before = pos;
            if (pos.m_node == m_leftmost())
            {
                return Res(m_leftmost(), m_leftmost());
            }
            else if (this->m_impl.m_key_compare(s_key((--before).m_node), k))
            {
                if (s_right(before.m_node) == 0)
                    return Res(0, before.m_node);
                else
                    return Res(pos.m_node, pos.m_node);
            }
            else
            {
                return m_get_insert_unique_pos(k);
            }
        }
        else if (this->m_impl.m_key_compare(s_key(pos.m_node), k))
        {
            iterator after = pos;
            if (pos.m_node == m_rightmost())
            {
                return Res(0, m_rightmost());
            }
            else if (this->m_impl.m_key_compare(k, s_key((++after).m_node)))
            {
                if (s_right(pos.m_node) == 0)
                    return Res(0, pos.m_node);
                else
                    return Res(after.m_node, after.m_node);
            }
            else
            {
                return m_get_insert_unique_pos(k);
            }
        }
        else
        {
            return Res(pos.m_node, 0);
        }
    }

    ft::Pair<Base_ptr, Base_ptr> m_get_insert_hint_equal_pos(const_iterator position, const key_type& k)
    {
        typedef ft::Pair<Base_ptr, Base_ptr>    Res;
        iterator pos = position.m_const_cast();
        if (pos.m_node == m_end())
        {
            if (size() > 0 && !m_impl.m_key_compare(k, s_key(m_rightmost())))
                return Res(0, m_rightmost());
            else
                return m_get_insert_equal_pos(k);
        }
        else if (!this->m_impl.m_key_compare(s_key(pos.m_node), k))
        {
            iterator before = pos;
            if (pos.m_node == m_leftmost())
                return Res(m_leftmost(), m_leftmost());
            else if (!this->m_impl.m_key_compare(k, s_key(--before).m_node))
            {
                if (s_right(before.m_node) == 0)
                    return Res(0, before.m_node);
                else
                    return Res(pos.m_node, pos.m_node);
            }
            else
            {
                return m_get_insert_equal_pos(k);
            }
        }
        else
        {
            iterator after = pos;
            if (pos.m_node == m_rightmost())
            {
                return Res(0, m_rightmost());
            }
            else if (!this->m_impl.m_key_compare(s_key((++after).m_node), k))
            {
                if (s_right(pos.m_node) == 0)
                    return Res(0, pos.m_node);
                else
                    return Res(after.m_node, after.m_node);
            }
            else
            {
                return Res(0, 0);
            }
        }
    }

    ft::Pair<iterator, bool> m_insert_unique(const value_type& v)
    {
        typedef ft::Pair<iterator, bool>    Res;
        ft::Pair<Base_ptr, Base_ptr> res = m_get_insert_unique_pos(KeyOfValue()(v));
        if (res.second)
        {
            Alloc_node an(*this);
            return Res(m_insert(res.first, res.second, v, an), true);
        }
        return Res(iterator(res.first), false);
    }

    template<typename InputIter>
    void m_insert_unique(InputIter first, InputIter last)
    {
        Alloc_node an(*this);
        for (; first != last; ++first)
            m_insert_unique(end(), *first, an);
    }

    template<typename NodeGen>
    iterator m_insert_unique(const_iterator pos, const value_type& x, NodeGen& node_gen)
    {
        ft::Pair<Base_ptr, Base_ptr> res = m_get_insert_hint_unique_pos(pos, KeyOfValue()(x));
        if (res.second)
            return m_insert(res.first, res.second, x, node_gen);
        return iterator(res.first);
    }

    iterator m_insert_unique(const_iterator pos, const value_type& x)
    {
        Alloc_node an(*this);
        return m_insert_unique(pos, x, an);
    }

    iterator m_insert_equal(const value_type& x)
    {
        ft::Pair<Base_ptr, Base_ptr> res = m_get_insert_equal_pos(KeyOfValue()(x));
        Alloc_node an(*this);
        return m_insert(res.first, res.second, x, an);
    }

    template<typename InputIter>
    void m_insert_equal(InputIter first, InputIter last)
    {
        Alloc_node an(*this);
        for (; first != last; ++first)
            m_insert_equal(end(), *first, an);
    }

    template<typename NodeGen>
    iterator m_insert_equal(const_iterator pos, const value_type& x, NodeGen& node_gen)
    {
        ft::Pair<Base_ptr, Base_ptr> res = m_get_insert_hint_equal_pos(pos, KeyOfValue()(x));
        if (res.second)
            return m_insert(res.first, res.second, x, node_gen);
        return m_insert_equal_lower(x);
    }

    iterator m_insert_equal(const_iterator pos, const value_type& x)
    {
        Alloc_node an(*this);
        return m_insert_equal(pos, x, an);
    }
    
    void erase(iterator pos)
    {
        if (pos == end())
            throw std::out_of_range("rbtree: erase");
        else
            m_rebalance_erase(pos);
    }

    void erase(const_iterator pos)
    {
        if (pos == end())
            throw std::out_of_range("rbtree: erase");
        else
            m_rebalance_erase(pos);
    }

    void erase(iterator first, iterator last)
    { m_rebalance_erase(first, last); }

    void erase(const_iterator first, const_iterator last)
    { m_rebalance_erase(first, last); }

    size_t erase(const key_type& x)
    {
        ft::Pair<iterator, iterator> p = equal_range(x);
        const size_t old_size = size();
        m_rebalance_erase(p.first, p.second);
        return old_size - size();
    }

    void erase(const key_type* first, const key_type* last)
    {
        while (first != last)
            erase(*first++);
    }

    void clear()
    {
        m_erase(m_begin());
        m_impl.m_reset();
    }

    iterator find(const key_type& k)
    {
        iterator j = m_lower_bound(m_begin(), m_end(), k);
        return (j == end() || m_impl.m_key_compare(k, s_key(j.m_node))) ? end() : j;
    }

    const_iterator find(const key_type& k) const
    {
        const_iterator j = m_lower_bound(m_begin(), m_end(), k);
        return (j == end() || m_impl.m_key_compare(k, s_key(j.m_node))) ? end() : j;
    }

    size_t count(const key_type& k) const
    {
        ft::Pair<const_iterator, const_iterator> p = equal_range(k);
        return std::distance(p.first, p.second);
    }

    iterator lower_bound(const key_type& k)
    { return m_lower_bound(m_begin(), m_end(), k); }

    const_iterator lower_bound(const key_type& k) const
    { return m_lower_bound(m_begin(), m_end(), k); }

    iterator upper_bound(const key_type& k)
    { return m_upper_bound(m_begin(), m_end(), k); }

    const_iterator upper_bound(const key_type& k) const
    { return m_upper_bound(m_begin(), m_end(), k); }

    ft::Pair<iterator, iterator> equal_range(const key_type& k)
    {
        Link_type x = m_begin();
        Base_ptr y = m_end();
        while (x != 0)
        {
            if (m_impl.m_key_compare(s_key(x), k))
            {
                x = s_right(x);
            }
            else if (m_impl.m_key_compare(k, s_key(x)))
            {
                y = x;
                x = s_left(x);
            }
            else
            {
                Link_type xu(x);
                Base_ptr yu(y);
                y = x, x = s_left(x);
                xu = s_right(xu);
                return ft::Pair<iterator, iterator>(
                    m_lower_bound(x, y, k), m_upper_bound(xu, yu, k));
            }
        }
        return ft::Pair<iterator, iterator>(iterator(y), iterator(y));
    }

    ft::Pair<const_iterator, const_iterator> equal_range(const key_type& k) const
    {
        Const_Link_type x = m_begin();
        Const_Base_ptr y = m_end();
        while (x != 0)
        {
            if (m_impl.m_key_compare(s_key(x), k))
            {
                x = s_right(x);
            }
            else if (m_impl.m_key_compare(k, s_key(x)))
            {
                y = x;
                x = s_left(x);
            }
            else
            {
                Const_Link_type xu(x);
                Const_Base_ptr yu(y);
                y = x, x = s_left(x);
                xu = s_right(xu);
                return ft::Pair<const_iterator, const_iterator>(
                    m_lower_bound(x, y, k), m_upper_bound(xu, yu, k));
            }
        }
        return ft::Pair<const_iterator, const_iterator>(
            const_iterator(y), const_iterator(y));
    }

protected:
    template<typename Key_compare>
    struct Rbtree_impl
        : public Node_allocator
        , public Rbtree_key_compare<Key_compare>
        , public Rbtree_header
    {
        typedef Rbtree_key_compare<Key_compare> Base_Key_compare;

        Rbtree_impl() {}

        Rbtree_impl(const Rbtree_impl& x)
            : Node_allocator(x.get_node_allocator())
            , Base_Key_compare(x.m_key_compare) {}

        Rbtree_impl(const Key_compare& comp, const Node_allocator& a)
            : Node_allocator(a), Base_Key_compare(comp) {}
    };

    Link_type m_get_node() // allocate node
    { return this->m_impl.allocate(1); }

    void m_put_node(Link_type p) // deallocate node
    { this->m_impl.deallocate(p, 1); }

    void m_construct_node(Link_type node, const value_type& x) // initialize node's val as x
    {
        try
        {
            get_allocator().construct(node->m_valptr(), x);
        }
        catch(...)
        {
            m_put_node(node);
            throw ;
        }
    }

    Link_type m_create_node(const value_type& x) // allocate node and initialize it's val as x
    {
        Link_type tmp = m_get_node();
        m_construct_node(tmp, x);
        return tmp;
    }
    
    void m_destroy_node(Link_type p) // destroy val
    { get_allocator().destroy(p->m_valptr()); }

    void m_drop_node(Link_type p) // destroy val and deallocate node
    {
        m_destroy_node(p);
        m_put_node(p);
    }

    template<typename NodeGen>
    Link_type m_clone_node(Const_Link_type x, NodeGen& node_gen)
    {
        Link_type tmp = node_gen(*x->m_valptr());
        tmp->m_color = x->m_color;
        tmp->m_left = 0;
        tmp->m_right = 0;
        return tmp;
    }

    Base_ptr& m_root()
    { return this->m_impl.m_header.m_parent; }

    Const_Base_ptr m_root() const
    { return this->m_impl.m_header.m_parent; }

    Base_ptr& m_leftmost()
    { return this->m_impl.m_header.m_left; }

    Const_Base_ptr m_leftmost() const
    { return this->m_impl.m_header.m_left; }

    Base_ptr& m_rightmost()
    { return this->m_impl.m_header.m_right; }

    Const_Base_ptr m_rightmost() const
    { return this->m_impl.m_header.m_right; }

    Link_type m_begin()
    { return static_cast<Link_type>(this->m_impl.m_header.m_parent); }

    Const_Link_type m_begin() const
    { return static_cast<Const_Link_type>(this->m_impl.m_header.m_parent); }

    Base_ptr m_end()
    { return &this->m_impl.m_header; }

    Const_Base_ptr m_end() const
    { return &this->m_impl.m_header; }

    static const_reference s_value(Const_Link_type x)
    { return *x->m_valptr(); }

    static const_reference s_value(Const_Base_ptr x)
    { return *static_cast<Const_Link_type>(x)->m_valptr(); }

    static const Key& s_key(Const_Link_type x)
    { return KeyOfValue()(s_value(x)); }

    static const Key& s_key(Const_Base_ptr x)
    { return KeyOfValue()(s_value(x)); }

    static Link_type s_left(Base_ptr x)
    { return static_cast<Link_type>(x->m_left); }

    static Const_Link_type s_left(Const_Base_ptr x)
    { return static_cast<Const_Link_type>(x->m_left); }

    static Link_type s_right(Base_ptr x)
    { return static_cast<Link_type>(x->m_right); }

    static Const_Link_type s_right(Const_Base_ptr x)
    { return static_cast<Const_Link_type>(x->m_right); }

    static Base_ptr s_minimum(Base_ptr x)
    { return Rbtree_node_base::s_minimum(x); }

    static Const_Base_ptr s_minimum(Const_Base_ptr x)
    { return Rbtree_node_base::s_minimum(x); }

    static Base_ptr s_maximum(Base_ptr x)
    { return Rbtree_node_base::s_maximum(x); }

    static Const_Base_ptr s_maximum(Const_Base_ptr x)
    { return Rbtree_node_base::s_minimum(x); }

    Rbtree_impl<Compare> m_impl;

private:
    class Reuse_or_alloc_node
    {
    public:
        Reuse_or_alloc_node(Rbtree& t)
            : m_root(t.m_root()), m_nodes(t.m_rightmost()), m_t(t)
        {
            if (m_root)
            {
                m_root->m_parent = 0;
                if (m_nodes->m_left)
                    m_nodes = m_nodes->m_left;
            }
            else
            {
                m_nodes = 0;
            }
        }

        ~Reuse_or_alloc_node()
        { m_t.m_erase(static_cast<Link_type>(m_root)); }

        Link_type operator()(const value_type& x) // remove last node and return a node with val x
        {
            Link_type node = static_cast<Link_type>(m_extract());
            if (node)
            {
                m_t.m_destroy_node(node);
                m_t.m_construct_node(node, x);
                return node;
            }
            return m_t.m_create_node(x);
        }

    private:
        Base_ptr m_extract() // cut the connection to last node and update new last node and return that
        {
            if (!m_nodes)
                return m_nodes;
            Base_ptr node = m_nodes;
            m_nodes = m_nodes->m_parent;
            if (m_nodes)
            {
                if (m_nodes->m_right == node)
                {
                    m_nodes->m_right = 0;
                    if (m_nodes->m_left)
                    {
                        m_nodes = m_nodes->m_left;
                        while (m_nodes->m_right)
                            m_nodes = m_nodes->m_right;
                        if (m_nodes->m_left)
                            m_nodes = m_nodes->m_left;
                    }
                }
                else
                {
                    m_nodes->m_left = 0;
                }
            }
            else
            {
                m_root = 0;
            }
            return node;
        }

        Base_ptr m_root;
        Base_ptr m_nodes;
        Rbtree& m_t;
    };

    // simple version of Resue_or_alloc_node 
    struct Alloc_node
    {
    public:
        Alloc_node(Rbtree& t) : m_t(t) {}

        Link_type operator()(const value_type& x) const
        { return m_t.m_create_node(x); }

    private:
        Rbtree& m_t;
    };

    template<typename NodeGen>
    iterator m_insert(Base_ptr x, Base_ptr p, const value_type& v, NodeGen& node_gen)
    {
        bool insert_left = (x != 0 || p == m_end() || this->m_impl.m_key_compare(KeyOfValue()(v), s_key(p)));
        Link_type z = node_gen(v);
        rbtree_insert_and_rebalance(insert_left, z, p, this->m_impl.m_header);
        ++this->m_impl.m_node_count;
        return iterator(z);
    }

    iterator m_insert_lower(Base_ptr p, const value_type& v)
    {
        bool insert_left = (p == m_end() || !m_impl.m_key_compare(s_key(p), KeyOfValue()(v)));
        Link_type z = m_create_node(v);
        rbtree_insert_and_rebalance(insert_left, z, p, this->m_impl.m_header);
        ++this->m_impl.m_node_count;
        return iterator(z);
    }

    iterator m_insert_equal_lower(const value_type& v)
    {
        Link_type x = m_begin();
        Base_ptr y = m_end();
        while (x != 0)
        {
            y = x;
            x = !this->m_impl.m_key_compare(s_key(x), KeyOfValue()(v)) ?
                s_left(x) : s_right(x);
        }
        return m_insert_lower(y, v);
    }

    template<typename NodeGen>
    Link_type m_copy(Const_Link_type x, Base_ptr p, NodeGen& node_gen)
    {
        Link_type top = m_clone_node(x, node_gen);
        top->m_parent = p;
        try
        {
            if (x->m_right)
                top->m_right = m_copy(s_right(x), top, node_gen);
            p = top;
            x = s_left(x);
            while (x != 0)
            {
                Link_type y = m_clone_node(x, node_gen);
                p->m_left = y;
                y->m_parent = p;
                if (x->m_right)
                    y->m_right = m_copy(s_right(x), y, node_gen);
                p = y;
                x = s_left(x);
            }
        }
        catch(...)
        {
            top->m_parent->m_right = 0; //check
            m_erase(top);
            throw ;
        }
        return top;
    }

    template<typename NodeGen>
    Link_type m_copy(const Rbtree& x, NodeGen& node_gen)
    {
        Link_type root = m_copy(x.m_begin(), m_end(), node_gen);
        m_leftmost() = s_minimum(root);
        m_rightmost() = s_maximum(root);
        m_impl.m_node_count = x.m_impl.m_node_count;
        return root;
    }

    Link_type m_copy(const Rbtree& x)
    {
        Alloc_node an(*this);
        return m_copy(x, an);
    }

    void m_erase(Link_type x)
    {
        while (x != 0)
        {
            m_erase(s_right(x));
            Link_type y = s_left(x);
            m_drop_node(x);
            x = y;
        }
    }

    void m_rebalance_erase(const_iterator pos)
    {
        Link_type y = static_cast<Link_type>(rbtree_rebalance_for_erase
            (const_cast<Base_ptr>(pos.m_node), this->m_impl.m_header));
        m_drop_node(y);
        --m_impl.m_node_count;
    }

    void m_rebalance_erase(const_iterator first, const_iterator last)
    {
        if (first == begin() && last == end())
            clear();
        else
            while (first != last)
                m_rebalance_erase(first++);
    }

    iterator m_lower_bound(Link_type x, Base_ptr y, const Key& k)
    {
        while (x != 0)
        {
            if (!m_impl.m_key_compare(s_key(x), k))
                y = x, x = s_left(x);
            else
                x = s_right(x);
        }
        return iterator(y);
    }

    const_iterator m_lower_bound(Const_Link_type x, Const_Base_ptr y, const Key& k) const
    {
        while (x != 0)
        {
            if (!m_impl.m_key_compare(s_key(x), k))
                y = x, x = s_left(x);
            else
                x = s_right(x);
        }
        return const_iterator(y);
    }

    iterator m_upper_bound(Link_type x, Base_ptr y, const Key& k)
    {
        while (x != 0)
        {
            if (m_impl.m_key_compare(k, s_key(x)))
                y = x, x = s_left(x);
            else
                x = s_right(x);
        }
        return iterator(y);
    }

    const_iterator m_upper_bound(Const_Link_type x, Const_Base_ptr y, const Key& k) const
    {
         while (x != 0)
        {
            if (m_impl.m_key_compare(k, s_key(x)))
                y = x, x = s_left(x);
            else
                x = s_right(x);
        }
        return const_iterator(y);
    }
};

template<typename Key, typename Val, typename KeyOfValue,
    typename Compare, typename Alloc>
inline bool operator==(const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& x,
    const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{ return (x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin())); }

template<typename Key, typename Val, typename KeyOfValue,
    typename Compare, typename Alloc>
inline bool operator<(const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& x,
    const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{ return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template<typename Key, typename Val, typename KeyOfValue,
    typename Compare, typename Alloc>
inline bool operator!=(const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& x,
    const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{ return !(x == y); }

template<typename Key, typename Val, typename KeyOfValue,
    typename Compare, typename Alloc>
inline bool operator>(const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& x,
    const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{ return y < x; }

template<typename Key, typename Val, typename KeyOfValue,
    typename Compare, typename Alloc>
inline bool operator<=(const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& x,
    const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{ return !(y < x); }

template<typename Key, typename Val, typename KeyOfValue,
    typename Compare, typename Alloc>
inline bool operator>=(const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& x,
    const Rbtree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{ return !(x < y); }

} // namespace ft

#endif /* FT_RBTREE_HPP */