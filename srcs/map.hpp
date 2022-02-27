#pragma once

#include "iterators_traits.hpp"
#include "pair.hpp"
#include "algorithm.hpp"
#include "treap.hpp"

namespace ft {

    template<class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
    class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

    private:
        typedef Treap<value_type, key_compare, allocator_type> tree_type;
        typedef typename tree_type::node_type node_type;

    public:
        typedef typename tree_type::iterator iterator;
        typedef typename tree_type::const_iterator const_iterator;
        typedef typename tree_type::reverse_terator reverse_iterator;
        typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

    public:
        
    private:
        allocator_type _allocator;
        tree_type _treap;
        key_compare _cmp;

    };

}; //namespace ft