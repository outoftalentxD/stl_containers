#pragma once

#include <iostream>
#include <string>

#include "iterators.hpp"
#include "iterators_traits.hpp"
#include "algorithm.hpp"
#include "pair.hpp"

namespace ft {

    /* Treap node */
    template<class U>
    struct _node {
        typedef U value_type;

        value_type value;
        size_t size;
        size_t weight;
        _node<value_type>* left;
        _node<value_type>* right;
        _node<value_type>* parent;

        explicit _node(const value_type& value)  : value(value), weight(rand()), size(1), left(nullptr), right(nullptr), parent(nullptr){
        }

        _node(const _node& other) : value(other.value), weight(other.weight), size(other.size), left(other.left), right(other.right), parent(other.parent) {

        }

        _node& operator=(const _node& other) {
            if (this != &other) {
                value = other.value;
                weight = other.weight;
                size = other.size;
                left = other.left;
                right = other.right;
                parent = other.parent;
            }
        }

        ~_node( ) {
        }

    };

    /* Treap iterator */
    template<typename T>
    class TreapIter {
    public:
        typedef ft::bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<T*>::value_type 		value_type;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::reference 		reference;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef _node<value_type>* node_pointer;

    public:
        TreapIter() {

        }

        TreapIter(node_pointer other) {
            _pnode = other;
        }

        TreapIter(const TreapIter& other) {
            _pnode = other._pnode;
        }

        TreapIter& operator=(const TreapIter& other) {
            if (this != &other) {
                _pnode = other._pnode;
            }
        }

    public:

        node_pointer base() const {
            return _pnode;
        }

        reference operator*() const {
            return *(_pnode->value);
        }

        pointer operator->() const {
            return _pnode->value;
        }

        TreapIter& operator++() {
            if (_pnode->right) {
                _pnode = _treap_subtree_min(_pnode->right);
            } else {
                node_pointer parent = _pnode->parent;
                while (parent && parent->right == _pnode) {
                    _pnode = parent;
                    parent = _pnode->parent;
                }
                _pnode = _pnode->parent;
            }
            return *this;
        }

        TreapIter& operator++(int) {
            TreapIter<value_type> temp = *this;
            if (_pnode->right) {
                _pnode = _treap_subtree_min(_pnode->right);
            } else {
                node_pointer parent = _pnode->parent;
                while (parent && parent->right == _pnode) {
                    _pnode = parent;
                    parent = _pnode->parent;
                }
                _pnode = _pnode->parent;
            }
            return *this;return temp;
        }

        TreapIter& operator--() {
            if (_pnode->left) {
                _pnode = _treap_subtree_max(_pnode->left);
            } else {
                node_pointer parent = _pnode->parent;
                while(parent && parent->left == _pnode) {
                    _pnode = parent;
                    parent = _pnode->parent;
                }
                _pnode = _pnode->parent;
            }
            return *this;
        }

        TreapIter& operator--(int) {
            TreapIter<value_type> temp = *this;
            if (_pnode->left) {
                _pnode = _treap_subtree_max(_pnode->left);
            } else {
                node_pointer parent = _pnode->parent;
                while(parent && parent->left == _pnode) {
                    _pnode = parent;
                    parent = _pnode->parent;
                }
                _pnode = _pnode->parent;
            }
            return temp;
        }

    private:
        node_pointer _treap_subtree_max(node_pointer ptreap) const {
            if (!ptreap->right) {
                return ptreap;
            } else {
                return _treap_subtree_max(ptreap->right);
            }
        }

        node_pointer _treap_subtree_min(node_pointer ptreap) const {
            if (!ptreap->left) {
                return ptreap;
            } else {
                return _treap_subtree_min(ptreap->left);
            }
        }

    private:
        node_pointer _pnode;
    };

    template<class U>
    bool operator==(const TreapIter<U>& lhs, const TreapIter<U>& rhs) {
        return (lhs.base() == rhs.base());
    }

    template<class U>
    bool operator!=(const TreapIter<U>& lhs, const TreapIter<U>& rhs) {
        return (lhs.base() != rhs.base());
    }

    /* Treap */
    template<class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
    class Treap {
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef Compare compare_type;
        typedef _node<T> node_type;

        typedef typename allocator_type::template rebind<node_type>::other node_allocator;

        typedef typename node_allocator::difference_type difference_type;
        typedef typename node_allocator::size_type size_type;
        typedef typename node_allocator::pointer node_pointer;
        typedef typename node_allocator::const_pointer const_node_pointer;
        typedef typename node_allocator::reference node_reference;
        typedef typename node_allocator::const_reference const_node_reference;
        typedef TreapIter<value_type> iterator;
        typedef TreapIter<const value_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    public:


        Treap(compare_type& cmp, const allocator_type& allocator = Alloc()) : _cmp(cmp), _allocator(allocator), _node_allocator(node_allocator()), _size(0) {
            _root = _node_allocator.allocate(1);
            _node_allocator.construct(_root, value_type());
        }

        Treap(const Treap& other) : _cmp(other._cmp), _allocator(other._allocator), _node_allocator(other._node_allocator), _root(other._root), _size(other._size) {

        }

        Treap& operator=(const Treap& other) {
            if (this != &other) {
                _root = other._root;
                _allocator = other._allocator;
                _cmp = other._cmp;
                _node_allocator = other._node_allocator;
                _size = other._size;
            }
            return *this;
        }

        ~Treap() {
            _delete_treap();
        }

    public:
        void push(const value_type& value) {
            _root._insert(_root, new ft::_node<value_type>(value));
        }

    public:
        void _split(node_pointer treap, value_type& value, node_pointer& left, node_pointer& right) {
            if (!treap) {
                left = right = nullptr;
            } else if (_cmp(value, treap->value)) {
                _split(treap->left, value, left, treap->left);
                right = treap;
            } else {
                _split(treap->right, value, treap->right, right);
            }
        }

        void _merge(node_pointer& treap, node_pointer left, node_pointer right) {
            if (!left || !right) {
                treap = left ? left : right;
            } else if (left->weight > right->weight) {
                _merge(left->right, left->right, right);
                treap = left;
            } else {
                _merge(right->left, left, right->left);
                treap = right;
            }
        }

        void _insert(node_pointer& treap, node_pointer node) {
            if (!treap) {
                treap = node;
            } else if (node->weight > treap->weight) {
                _split(treap, node->value, node->left, node->right);
                treap = node;
            } else {
                if (_cmp(node->value, treap->value)) {
                    _insert(treap->left, node);
                } else if (_cmp(treap->value, node->value)) {
                    _insert(treap->right, node);
                } else { // if is equal, test later
                    treap->value = node->value;
                    return ;
                }
            }
        }

        void _delete_treap(node_pointer root) {
            if (root) {
                _delete_treap(root->left);
                _delete_treap(root->right);
                _node_allocator.destroy(root);
                _node_allocator.deallocate(root, 1);
            }
        }

    private:
        allocator_type _allocator;
        node_allocator _node_allocator;
        compare_type _cmp;
        node_pointer _root;
        size_type _size;
    };
} //namespace ft;