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
        class pair_compare {
        private:
            key_compare _cmp;
        public:
            pair_compare(const key_compare& cmp) : _cmp(cmp) {

            }

            bool operator()(const value_type& lhs, const value_type& rhs) const {
                return (_cmp(lhs.first, rhs.first));
            }
        };

    public:
        typedef pair_compare value_compare;

    private:
        typedef Treap<value_type, value_compare, allocator_type> tree_type;
        typedef typename tree_type::node_type node_type;

    public:
        typedef typename tree_type::iterator iterator;
        typedef typename tree_type::const_iterator const_iterator;
        // typedef typename tree_type::reverse_terator reverse_iterator;
        // typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

    public:
        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _allocator(alloc), _cmp(comp),
                                                                                                                    _treap(tree_type(comp, alloc)) {

        }

        map(const map& other) : _allocator(other._allocator), _cmp(other._cmp), _treap(other._treap) {

        }

        map& operator=(const map& other) {
            if (this != &other) {
                _allocator = other._allocator;
                _cmp = other._cmp;
                _treap = other._treap;
            }
            return *this;
        }

        allocator_type get_allocator() const {
            return _allocator;
        }

        ~map() {

        }

    /* Element access */
    public:
        void at(const key_type& key) {
            _treap.find(ft::make_pair(key, mapped_type()));
            // iterator it = _treap.find(ft::make_pair(value.first, value.second));
        }

    /* Iterators */
    public:
        iterator begin() {
            return _treap.begin();
        }

        const_iterator begin() const {
            return _treap.begin();
        }

        iterator end() {
            return _treap.end();
        }

        const_iterator end() const {
            return _treap.end();
        }



    /* Modifiers */
    public:
        void insert(const value_type& value) {
            _treap.push(value);
        }

    /* Element access */
    public:
    /* Element access */
    public:
    /* Element access */
    public:
    /* Element access */
    public:

    private:
        allocator_type _allocator;
        tree_type _treap;
        key_compare _cmp;

    };

}; //namespace ft