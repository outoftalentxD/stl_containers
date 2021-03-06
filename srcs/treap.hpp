#pragma once

#include <iostream>
#include <limits>
#include <string>

#include "iterators.hpp"
#include "iterators_traits.hpp"
#include "algorithm.hpp"
#include "pair.hpp"

namespace ft {

    enum Path {
        left,
        right,
        both,
        none
    };

    /* Treap node */
    template<class U>
    struct _node {
        typedef U value_type;

        value_type value;
        size_t height;
        _node<value_type>* left;
        _node<value_type>* right;
        _node<value_type>* parent;

        explicit _node(const value_type& value)  : value(value), height(1), left(nullptr), right(nullptr), parent(nullptr) {
        }

        _node(const _node& other) : value(other.value), height(1), left(other.left), right(other.right), parent(other.parent) {
        }

        _node& operator=(const _node& other) {
            if (this != &other) {
                value = other.value;
                height = other.height;
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
    class TreapIter : iterator<T, ft::bidirectional_iterator_tag>{
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
            return *this;
        }

    public:
        node_pointer base() const {
            return _pnode;
        }

        reference operator*() const {
            return _pnode->value;
        }

        pointer operator->() const {
            return &(_pnode->value);
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
                if (parent) {
                    _pnode = parent;
                }
            }
            return *this;
        }

        TreapIter operator++(int) {
            TreapIter<T> temp(*this);

            if (_pnode->right) {
                _pnode = _treap_subtree_min(_pnode->right);
            } else {
                node_pointer parent = _pnode->parent;
                while (parent && parent->right == _pnode) {
                    _pnode = parent;
                    parent = _pnode->parent;
                }
                if (parent) {
                    _pnode = parent;
                }
            }
            return temp;
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
                if (parent) {
                    _pnode = parent;
                }
            }
            return *this;
        }

        TreapIter operator--(int) {
            TreapIter<T> temp(*this);
            if (_pnode->left) {
                _pnode = _treap_subtree_max(_pnode->left);
            } else {
                node_pointer parent = _pnode->parent;
                while(parent && parent->left == _pnode) {
                    _pnode = parent;
                    parent = _pnode->parent;
                }
                if (parent) {
                    _pnode = parent;
                }
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
    template<class Value, class Compare = std::less<Value>, class Alloc = std::allocator<Value> >
    class Treap {
    public:
        typedef Value value_type;
        typedef Alloc allocator_type;
        typedef Compare compare_type;
        typedef _node<Value> node_type;

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
        Treap(const compare_type& cmp, const allocator_type& allocator = allocator_type()) : _allocator(allocator), _node_allocator(node_allocator()), _cmp(cmp), _size(0) {
            _header = _node_allocator.allocate(1);
            _node_allocator.construct(_header, value_type());
            _root = _header;
        }

        Treap(const Treap& other) : _allocator(other._allocator), _node_allocator(other._node_allocator), _cmp(other._cmp), _size(0) {
            if (this != &other) {
                _header = _node_allocator.allocate(1);
                _node_allocator.construct(_header, value_type());
                _root = _header;
                _insert_all_nodes(_root, other._root);
            }
        }

        Treap& operator=(const Treap& other) {
            if (this != &other) {
                _allocator = other._allocator;
                _node_allocator = other._node_allocator;
                _cmp = other._cmp;
                _size = 0;
                if (_root != _header) {
                    _delete_treap(_root);
                }
                _root = _header;
                _header->left = _header->right = nullptr;
                if (other._size > 0) {
                    _insert_all_nodes(_root, other._root);
                }
            }
            return *this;
        }

        ~Treap() {
            if (_root != _header) {
                _delete_treap(_root);
            }
            _node_allocator.destroy(_header);
            _node_allocator.deallocate(_header, 1);
        }

    /* iterators */
    public:
        iterator begin() {
            return iterator(_subtree_min(_root));
        }

        const_iterator begin() const {
            return const_iterator(_subtree_min(_root));
        }

        iterator end() {
            return iterator(_header);
        }

        const_iterator end() const {
            return const_iterator(_header);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

    /* Capacity */
    public:
        size_type size() const {
            return _size;
        }

    /* Modifiers */
    public:
        void clear() {
            if (_root != _header) {
                _delete_treap(_root);
                _size = 0;
                _root = _header;
                _header->left = _header->right = nullptr;
            }
        }

        ft::pair<iterator, bool> insert(const value_type& value) {
            node_pointer pnode = nullptr;
            if (_root != _header) {
                pnode = _search(_root, value);
            }
            if (pnode) {
                return ft::make_pair(iterator(pnode), false);
            } else {
                _insert_avl(value);
                return ft::make_pair(iterator(_search(_root, value)), true);
            }
        }

        iterator insert(iterator hint, const value_type& value) {
            (void)hint;
            return insert(value).first;
        }

        size_type erase(iterator pos) {
            if (pos != end()) {
                _root = __erase(_root, pos.base()->value);
                _assign_paths_header();
                --_size;
                return 1;
            } else {
                return 0;
            }
        }

        void swap(Treap& other) {
            ft::swap(_allocator, other._allocator);
            ft::swap(_node_allocator, other._node_allocator);
            ft::swap(_cmp, other._cmp);
            ft::swap(_root, other._root);
            ft::swap(_header, other._header);
            ft::swap(_size, other._size);
        }

    /* Lookup */
    public:
        iterator find(const value_type& value) {
            node_pointer pnode = _search(_root, value);
            if (pnode) {
                return iterator(pnode);
            } else {
                return end();
            }
        }

        const_iterator find(const value_type& value) const {
            node_pointer pnode = _search(_root, value);
            if (pnode) {
                return const_iterator(pnode);
            } else {
                return end();
            }
        }

        iterator lower_bound(const value_type& value) {
            node_pointer less = nullptr;
            if (_cmp(*--end(), value)) {
                return end();
            }
            _first_less_than(_root, value, less);
            if (less) {
                return iterator(less);
            } else {
                return begin();
            }
        }

        const_iterator lower_bound(const value_type& value) const {
            node_pointer less = nullptr;
            if (_cmp(*--end(), value)) {
                return end();
            }
            _first_less_than(_root, value, less);
            if (less) {
                return const_iterator(less);
            } else {
                return begin();
            }
        }

        iterator upper_bound(const value_type& value) {
            node_pointer greater = nullptr;
            _first_greater_than(_root, value, greater);
            if (greater) {
                return iterator(greater);
            } else {
                return end();
            }
        }

        const_iterator upper_bound(const value_type& value) const {
            node_pointer greater = nullptr;
            _first_greater_than(_root, value, greater);
            if (greater) {
                return const_iterator(greater);
            } else {
                return end();
            }
        }

    /* Observers */
    public:
        compare_type value_comp() {
            return _cmp;
        }

    /* private helpers */
    private:
        size_type _height(node_pointer pnode) {
            if (pnode) {
                return pnode->height;
            } else {
                return 0;
            }
        }

        int _bfactor(node_pointer pnode) {
            return _height(pnode->right) - _height(pnode->left);
        }

        void _fix_height(node_pointer pnode) {
            size_t hl = _height(pnode->left);
            size_t hr = _height(pnode->right);
            pnode->height = (hl > hr ? hl : hr) + 1;
        }

        node_pointer _rotate_right(node_pointer p) { //need to assign parents
            node_pointer q = p->left;
            q->parent = p->parent;
            p->left = q->right;
            if (q->right) {
                q->right->parent = p;
            }
            q->right = p;
            p->parent = q;
            _fix_height(p);
            _fix_height(q);
            return q;
        }

        node_pointer _rotate_left(node_pointer q) {
            node_pointer p = q->right;
            p->parent = q->parent;
            q->right = p->left;
            if (p->left) {
                p->left->parent = q;
            }
            p->left = q;
            q->parent = p;
            _fix_height(q);
            _fix_height(p);
            return p;
        }

        node_pointer _balance(node_pointer pnode) {
            _fix_height(pnode);
            if (_bfactor(pnode) == 2) {
                if (_bfactor(pnode->right) < 0) {
                    pnode->right = _rotate_right(pnode->right);
                }
                return _rotate_left(pnode);
            }
            if (_bfactor(pnode) == -2 ) {
                if (_bfactor(pnode->left) > 0) {
                    pnode->left = _rotate_left(pnode->left);
                }
                return _rotate_right(pnode);
            }
            return pnode;
        }

        node_pointer __erase(node_pointer pnode, const value_type& value) // ???????????????? ?????????? k ???? ???????????? p
        {
            if(!pnode) {
                return nullptr;
            }
            if(_cmp(value, pnode->value)) {
                pnode->left = __erase(pnode->left, value);
                if (pnode->left) {
                    pnode->left->parent = pnode;
                }
            } else if(_cmp(pnode->value, value)) {
                pnode->right = __erase(pnode->right, value);
                if (pnode->right) {
                    pnode->right->parent = pnode;
                }
            } else {
                node_pointer q = pnode->left;
                node_pointer r = pnode->right;
                if (!r) {
                    if (q) {
                        q->parent = pnode->parent;
                    }
                    _delete_node(pnode);
                    return q;
                }
                node_pointer min = _subtree_min(r);
                min->right = __erase_subtree_min(r);
                if (min->right) {
                    min->right->parent = min;
                }
                min->left = q;
                if (q) {
                    q->parent = min;
                }
                return _balance(min);
            }
            return _balance(pnode);
        }

        node_pointer __erase_subtree_min(node_pointer p)
        {
            if (!p->left) {
                return p->right;
            }
            p->left = __erase_subtree_min(p->left);
            if (p->left) {
                p->left->parent = p;
            }
            return _balance(p);
        }

        void _insert_avl(const value_type& value) {
            if (_root == _header) {
                _root = __insert(nullptr, value);
                _assign_paths_header();
                ++_size;
            }
            else if (!_search(_root, value)) {
               _root = __insert(_root, value);
                _assign_paths_header();
                ++_size;
            }
        }

        node_pointer __insert(node_pointer root, const value_type& value) {
            if (!root) {
                root = _create_node(value);
            } else {
                if (_cmp(value, root->value)) {
                    root->left = __insert(root->left, value);
                    root->left->parent = root;
                } else if (_cmp(root->value, value)) {
                    root->right = __insert(root->right, value);
                    root->right->parent = root;
                }
            }
            return _balance(root);
        }

        void _assign_paths_header() {
            _header->left = _header->right = _root;
            if (_root) {
                _root->parent = _header;
            }
        }

        void _insert_all_nodes(node_pointer to, node_pointer from) {
            if (from) {
                _insert_avl(from->value);
                _insert_all_nodes(to, from->left);
                _insert_all_nodes(to, from->right);
            }
        }

        void _first_less_than(node_pointer pnode, const value_type& than, node_pointer& less) const {
            if (pnode) {
                if (_cmp(than, pnode->value)) {
                    _first_less_than(pnode->left, than, less);
                } else if (_cmp(pnode->value, than)) {
                    less = _max_node(less, pnode);
                    _first_less_than(pnode->right, than, less);
                } else {
                    less = pnode;
                }
            }
        }

        void _first_greater_than(node_pointer pnode, const value_type& than, node_pointer& greater) const {
            if (pnode) {
                if (_cmp(than, pnode->value)) {
                    greater = _min_node(greater, pnode);
                    _first_greater_than(pnode->left, than, greater);
                } else {
                    _first_greater_than(pnode->right, than, greater);
                }
            }
        }

        node_pointer _max_node(node_pointer lhs, node_pointer rhs) const {
            if (!lhs) {
                return rhs;
            } else if (!rhs) {
                return lhs;
            }
            if (_cmp(lhs->value, rhs->value)) {
                return rhs;
            } else {
                return lhs;
            }
        }

        node_pointer _min_node(node_pointer lhs, node_pointer rhs) const {
            if (!lhs) {
                return rhs;
            } else if (!rhs) {
                return lhs;
            }
            if (_cmp(lhs->value, rhs->value)) {
                return lhs;
            } else {
                return rhs;
            }
        }

        node_pointer _subtree_min(node_pointer treap) const {
            while (treap->left) {
                treap = treap->left;
            }
            return treap;
        }

        node_pointer _subtree_max(node_pointer treap) const {
            while (treap->right) {
                treap = treap->right;
            }
            return treap;
        }

        node_pointer _create_node(const value_type& value) {
            node_pointer pnode = _node_allocator.allocate(1);
            _node_allocator.construct(pnode, value);
            return pnode;
        }

        node_pointer _search(node_pointer treap, const value_type& value) const {
            if (!treap) {
                return nullptr;
            } else {
                if (_cmp(value, treap->value)) {
                    return _search(treap->left, value);
                } else if (_cmp(treap->value, value)) {
                    return _search(treap->right, value);
                } else {
                    return treap;
                }
            }
        }

        void _delete_treap(node_pointer root) {
            if (root) {
                _delete_treap(root->left);
                _delete_treap(root->right);
                _delete_node(root);
            }
        }

        void _delete_node(node_pointer node) {
            _node_allocator.destroy(node);
            _node_allocator.deallocate(node, 1);
        }

    private:
        allocator_type _allocator;
        node_allocator _node_allocator;
        compare_type _cmp;
        node_pointer _root;
        node_pointer _header;
        size_type _size;
    };

} //namespace ft;