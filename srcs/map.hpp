#pragma once

#include "iterators_traits.hpp"
#include "pair.hpp"
#include "algorithm.hpp"
#include "treap.hpp"
#include <limits>
#include <stdexcept>

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
        mapped_type& at(const key_type& key) {
            iterator it = _treap.find(ft::make_pair(key, mapped_type()));
            if (it == end()) {
                throw std::out_of_range("No such element");
            } else {
                return it->second;
            }
        }

        const mapped_type& at(const key_type& key) const {
            iterator it = _treap.find(ft::make_pair(key, mapped_type()));
            if (it == end()) {
                throw std::out_of_range("No such element");
            } else {
                return it->second;
            }
        }

        mapped_type& operator[](const key_type& key) {
            return (_treap.insert(ft::make_pair(key, mapped_type())).first)->second;
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

    /* Capacity*/
    public:
        size_type size() const {
            return _treap.size();
        }

        bool empty() const {
            return (_treap.size() == 0);
        }

        size_type max_size() const {
            return std::numeric_limits<difference_type>::max();
        }

    /* Modifiers */
    public:
        void clear() {
            _treap.clear();
        }

        ft::pair<iterator, bool> insert(const value_type& value) {
            return _treap.insert(value);
        }

        ft::pair<iterator, bool> insert(iterator hint, const value_type& value) {
            return _treap.insert(hint, value);
        }

        template< class InputIt >
        void insert( InputIt first, InputIt last ) {
            for (; first != last; ) {
                insert(*first);
                ++first;
            }
        }

        void erase(iterator pos) {
            _treap.erase(pos);
        }

        size_type erase(const key_type& key) {
            iterator it = _treap.find(value_type(key, mapped_type()));
            if (it == end()) {
                return 0;
            } else {
                return _treap.erase(it);
            }
        }

        void erase(iterator first, iterator last) {
            for ( ; first != last; ) {
                _treap.erase(first);
                ++first;
            }
        }

        void swap(map& other) {
            ft::swap(_treap, other._treap);
        }

        void visualize() {
            _treap.visualize();
        }

    /* Lookup */
    public:
        size_type count(const key_type& key) const {
            if (_treap.find(value_type(key, mapped_type())) != end()) {
                return 1;
            } else {
                return 0;
            }
        }

        iterator find(const key_type& key) {
            return _treap.find(value_type(key, mapped_type()));
        }

        const_iterator find(const key_type& key) const {
            return _treap.find(value_type(key, mapped_type()));
        }

        ft::pair<iterator, iterator> equal_range(const key_type& key) {
            value_type value = value_type(key, mapped_type());
            return ft::make_pair(_treap.lower_bound(value), _treap.upper_bound(value));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
            value_type value = value_type(key, mapped_type());
            return ft::make_pair(_treap.lower_bound(value), _treap.upper_bound(value));
        }

        iterator lower_bound(const key_type& key) {
            return _treap.lower_bound(value_type(key, mapped_type()));
        }

        const_iterator lower_bound(const key_type& key) const {
            return _treap.lower_bound(value_type(key, mapped_type()));
        }

        iterator upper_bound(const key_type& key) {
            return _treap.upper_bound(value_type(key, mapped_type()));
        }

        const_iterator upper_bound(const key_type& key) const {
            return _treap.upper_bound(value_type(key, mapped_type()));
        }

    /* Observers */
    public:
        key_compare key_comp() {
            return _cmp;
        }

        value_compare value_comp() {
            return _treap.value_comp();
        }

    /* Compare operators */
    public:
        friend bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
                                const ft::map<Key, T, Compare, Alloc>& rhs);

    private:
        allocator_type _allocator;
        tree_type _treap;
        key_compare _cmp;

    };

    template< class Key, class T, class Compare, class Alloc >
    bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs,
                    const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return true;
    }



}; //namespace ft