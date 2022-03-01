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
        _node<value_type>* left;
        _node<value_type>* right;
        _node<value_type>* parent;

        explicit _node(const value_type& value)  : value(value), left(nullptr), right(nullptr), parent(nullptr) {
        }

        _node(const _node& other) : value(other.value), left(other.left), right(other.right), parent(other.parent) {
        }

        _node& operator=(const _node& other) {
            if (this != &other) {
                value = other.value;
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
            TreapIter<value_type> temp = *this;

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
            TreapIter<value_type> temp = *this;
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
    template<class Value, class Compare = ft::less<Value>, class Alloc = std::allocator<Value> >
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
        Treap(const compare_type& cmp, const allocator_type& allocator = Alloc()) : _cmp(cmp), _allocator(allocator), _node_allocator(node_allocator()), _size(0) {
            _header = _node_allocator.allocate(1);
            _node_allocator.construct(_header, value_type());
            _root = _header;
        }

        Treap(const Treap& other) : _cmp(other._cmp), _allocator(other._allocator), _node_allocator(other._node_allocator), _root(other._root), _header(other._header), _size(other._size) {

        }

        Treap& operator=(const Treap& other) {
            if (this != &other) {
                _header = other._header;
                _root = other._root;
                _allocator = other._allocator;
                _cmp = other._cmp;
                _node_allocator = other._node_allocator;
                _size = other._size;
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

    /* Capacity */
    public:
        size_type size() const {
            return _size;
        }

    /* Observers */
    public:
        void print(const node_pointer treap) const {
            if (treap) {
                print(treap->left);
                std::cout << treap->value.first << std::endl;
                print(treap->right);
            }
        }

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

    /* Modifiers */
    public:
        void clear() {
            _delete_treap(_root);
            _size = 0;
            _root = _header;
            _header->left = _header->right = nullptr;
        }

        ft::pair<iterator, bool> insert(const value_type& value) {
            node_pointer pnode = _search(_root, value);
            if (pnode) {
                return ft::make_pair(iterator(pnode), false);
            } else {
                _insert(_root, _create_node(value));
                return ft::make_pair(iterator(_search(_root, value)), true);
            }
        }

        ft::pair<iterator, bool> insert(iterator hint, const value_type& value) {
            node_pointer proot = hint.base();
            node_pointer pnode = _search(_root, value);
            if (pnode) {
                return ft::make_pair(iterator(pnode), false);
            } else {
                _insert(proot, _create_node(value));
                return ft::make_pair(iterator(_search(_root, value), true));
            }
        }

        size_type erase(iterator pos) {
            return _erase(pos.base());

        }

        void visualize(node_pointer treap = nullptr, size_t depth = 0) {
            if (!treap && !depth) {
                treap = _root;
            }
            if (treap) {
                visualize(treap->left, depth + 1);
                for (size_t i = 0; i < depth; ++i) {
                    std::cout << ".";
                }
                std::cout << "\"" << treap->value << "\"" << std::endl;
                visualize(treap->right, depth + 1);
            }
        }

    /* private helpers */
    private:
        size_t _erase(node_pointer pnode) {
            Path leadingPath = _get_leading_path(pnode);
            node_pointer parent = pnode->parent;

            if (parent == _header) {
                _erase_root_node(leadingPath, pnode);
            } else {
                _erase_node(leadingPath, pnode, parent);
            }
            _size--;
            return 1;
        }

        size_type _erase_root_node(Path leadingPath, node_pointer pnode) {
            switch (leadingPath) {
                case none: {
                    _header->left = _header->right = nullptr;
                    _root = _header;
                    _delete_node(pnode);
                    break;
                }
                case left: {
                    _header->left = _header->right = pnode->left;
                    pnode->left->parent = _header;
                    _root = pnode->left;
                    _delete_node(pnode);
                    break;
                }
                case right: {
                    _header->left = _header->right = pnode->right;
                    pnode->right->parent = _header;
                    _root = pnode->right;
                    _delete_node(pnode);
                    break;
                }
                case both: {
                    node_pointer rightSubtreeMinPnode = _subtree_min(pnode->right);
                    node_pointer newNode = _create_node(rightSubtreeMinPnode->value);
                    _header->left = _header->right = newNode;
                    _root = newNode;
                    _assign_paths(pnode, newNode, true);
                    _erase(rightSubtreeMinPnode);
                    _delete_node(pnode);
                    break;
                }
            }
            return 1;
        }

        size_type _erase_node(Path leadingPath, node_pointer pnode, node_pointer parent) {
            Path parentPath = _get_parent_path(pnode);
            switch (leadingPath) {
                case none: {
                    _assign_leading_path(parent, parentPath);
                    _delete_node(pnode);
                    break;
                }
                case left: {
                    pnode->left->parent = pnode->parent;
                    _assign_leading_path(parent, parentPath, pnode->left);
                    _delete_node(pnode);
                    break;
                }
                case right: {
                    pnode->right->parent = pnode->parent;
                    _assign_leading_path(parent, parentPath, pnode->right);
                    _delete_node(pnode);
                    break;
                }
                case both: {
                    node_pointer rightSubtreeMinPnode = _subtree_min(pnode->right);
                    node_pointer newNode = _create_node(rightSubtreeMinPnode->value);
                    _assign_paths(pnode, newNode, true);
                    _assign_leading_path(parent, parentPath, newNode);
                    _erase(rightSubtreeMinPnode);
                    _delete_node(pnode);
                    break;
                }
            }
            return 1;
        }
        void _assign_paths(node_pointer from, node_pointer to, const bool withChilds = false) {
            to->parent = from->parent;
            to->left = from->left;
            to->right = from->right;
            if (withChilds) {
                if (from->left) {
                    from->left->parent = to;
                }
                if (from->right) {
                    from->right->parent = to;
                }
            }
        }

        void _assign_leading_path(node_pointer pnode, Path leadingPath, node_pointer value = nullptr) {
            if (pnode) {
                switch (leadingPath) {
                    case left: {
                        pnode->left = value;
                        break;
                    }
                    case right: {
                        pnode->right = value;
                        break;
                    }
                    case both: {
                        pnode->left = pnode->right = value;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }

        Path _get_parent_path(node_pointer pnode) {
            node_pointer parent = pnode->parent;
            Path parentPath = none;
            if (parent) {
                if (parent->left == pnode) {
                    parentPath = left;
                }
                if (parent->right == pnode) {
                    if (parentPath == left) {
                        parentPath = both;
                    } else {
                        parentPath = right;
                    }
                }
            }
            return parentPath;
        }

        Path _get_leading_path(node_pointer pnode) {
            Path leadingPath;
            if (!pnode->left && !pnode->right) {
                leadingPath = none;
            } else if (pnode->left && !pnode->right) {
                leadingPath = left;
            } else if (!pnode->left && pnode->right) {
                leadingPath = right;
            } else {
                leadingPath = both;
            }
            return leadingPath;
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

        void _insert(node_pointer& treap, node_pointer node, node_pointer prevNode = nullptr) {
            if (!treap || treap == _header) {
                _size++;
                treap = node;
                if (prevNode) {
                    treap->parent = prevNode;
                } else {
                    treap->parent = _header;
                    _header->right = _header->left = treap;
                }
            } else {
                if (_cmp(node->value, treap->value)) {
                    _insert(treap->left, node, treap);
                } else if (_cmp(treap->value, node->value)) {
                    _insert(treap->right, node, treap);
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