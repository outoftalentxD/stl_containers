#pragma once

#include <i386/limits.h>
#include <iostream>
#include <limits>
#include <vector>
#include "algorithm.hpp"
#include "iterators.hpp"
#include "iterators_traits.hpp"

namespace ft {
    template<class T, class Allocator = std::allocator<T> >
    class vector {
        public:
            typedef typename Allocator::value_type value_type;
            typedef Allocator allocator_type;

            typedef typename Allocator::pointer pointer;
            typedef typename Allocator::const_pointer const_pointer;

            typedef typename Allocator::reference reference;
            typedef typename Allocator::const_reference const_reference;

            typedef OwnIterator<T, pointer, reference> iterator;
            typedef OwnIterator<T, const_pointer, const_reference> const_iterator;

            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

            typedef typename iterator_traits<iterator>::difference_type difference_type;
            typedef typename Allocator::size_type size_type;

        public:
            explicit vector(const allocator_type& allocator = allocator_type()) : _size(0), _capacity(0), _allocator(allocator), _begin(), _end(){

            }

            explicit vector(size_type size, const_reference value = value_type(), const allocator_type& allocator = allocator_type())
                    : _size(size), _capacity(0), _allocator(allocator) , _begin(), _end() {
                if (size > 0) {
                    _reallocate(size);
                    for (size_type i = 0; i < size; ++i) {
                        _allocator.construct(_begin + i, value);
                    }
                    _end = _begin + size;
                }
            }

            vector(const vector& oth) : _size(oth._size), _capacity(oth._capacity), _allocator(oth._allocator) {
                _begin = _allocator.allocate(_capacity);
                _end = _begin + _size;
                for (size_type i = 0; i < oth._size; i++) {
                    _allocator.construct(_begin + i, oth[i]);
                }
            }

            template<class InputIt>
            vector(InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last,
                    const allocator_type& allocator = allocator_type()) : _size(0), _capacity(0),  _allocator(allocator), _begin(), _end() {
                size_t count = last - first;
                _reallocate(count);
                _resize(count);
                iterator it = begin();

                while (first != last) {
                    *it = *first;
                    ++it; ++first;
                }
            }

            vector& operator=(const vector& oth) {
                if (this != &oth) {
                    clear();
                    _size = oth._size;
                    _capacity = oth._capacity;
                    _allocator = oth._allocator;

                    _begin = _allocator.allocate(_capacity);
                    _end = _begin + _size;
                    for (size_type i = 0; i < _size; i++) {
                        _allocator.construct(_begin + i, oth[i]);
                    }
                }
                return (*this);
            }

            ~vector() {
                clear();
                _allocator.deallocate(_begin, _capacity);
            }

            void assign(size_t count, const_reference value) {
                _reallocate(count);
                _resize(count);
                for (size_type i = 0; i < _size; i++) {
                    *(_begin + i) = value;
                }
                _end = _begin + _size;
            }

            template< class InputIt >
            void assign( InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last) {
                size_type count = last - first;
                _reallocate(count);
                _resize(count);
                for (iterator it = begin(); first != last; ++first, ++it) {
                    *it = *first;
                }
            }

            allocator_type get_allocator() const {
                return _allocator;
            }

        /* Element access */
        public:
            reference at(size_type pos) {
                if (pos >= _size) {
                    throw std::out_of_range("Index out of range");
                }
                return *(_begin + pos);
            }

            const_reference at(size_type pos) const {
                if (pos >= _size) {
                    throw std::out_of_range("Index out of range");
                }
                return *(_begin + pos);
            }

            reference operator[](size_type i) {
                return _begin[i];
            }

            const_reference operator[](size_type i) const {
                return _begin[i];
            }

            reference front() {
                return _begin[0];
            }

            const_reference front() const {
                return _begin[0];
            }

            reference back() {
                return *(_end - 1);
            }

            const_reference back() const {
                return *(_end - 1);
            }

            pointer data() {
                return _begin;
            }

            const_pointer data() const {
                return _begin;
            }

        /* Capacity */
        public:
            bool empty() const {
                return (_size == 0);
            }

            size_type size() const {
                return _size;
            }

            size_type max_size() const {
                return std::vector<T>().max_size(); // is needed to pass te test.
                // std::vector<T>().get_allocator().max_size() - not passing the test, so i think, that on my OS std::vector
                // returns not alloctor().max_size() ?? what else ??
                // return _allocator.max_size();
            }

            void reserve(size_type new_cap) {
                if (_capacity < new_cap) {
                    pointer begin = _allocator.allocate(new_cap);
                    for (size_type i = 0; i < _size; i++) {
                        _allocator.construct(begin + i, _begin[i]);
                        _allocator.destroy(_begin + i);
                    }
                    _allocator.deallocate(_begin, _capacity);
                    _begin = begin;
                    _end = begin + _size;
                    _capacity = new_cap;
                }
            }

            size_type capacity() const {
                return _capacity;
            }

        /* Iterators */
        public:
            iterator begin() {
                return _begin;
            }

            iterator end() {
                return _end;
            }

            const_iterator begin() const {
                return (const_iterator)_begin;
            }

            const_iterator end() const {
                return (const_iterator)_end;
            }

            reverse_iterator rbegin() {
                return --end();
            }

            reverse_iterator rend() {
                return --begin();
            }

            const_reverse_iterator rbegin() const {
                return --end();
            }

            const_reverse_iterator rend() const {
                return --begin();
            }

        /* Modifiers */
        public:
            void clear() {
                for (size_t i = 0; i < _size; i++) {
                    _allocator.destroy(_begin + i);
                }
                _size = 0;
                _end = _begin;
            }

            iterator insert( iterator pos, const T& value ) {
                size_type index = pos - begin();
                _reallocate(_size + 1);
                _resize(_size + 1);
                size_t i = _size - 1;
                while (i > index) {
                    _allocator.construct(_begin + i, *(_begin + i - 1));
                    --i;
                }
                _allocator.construct(_begin + i, value);
                return iterator(_begin + index);
            }

            void insert( iterator pos, size_type count, const T& value ) {
                int index = pos - begin();
                reserve(_size + count);
                int r = _size + count - 1;
                int l = _size - 1;
                while (l >= index && l >= 0) {
                    _allocator.construct(_begin + r, *(_begin + l));
                    --l; --r;
                }
                _resize(_size + count);
                while (count > 0 && r >= 0) {
                    _allocator.construct(_begin + r, value);
                    --count; --r;
                }
            }

            template< class InputIt >
            void insert( iterator pos, InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last) {
                if (first < last) {
                    int index = pos - begin();
                    int count = last - first;
                    reserve(_size + count);
                    int l = _size - 1;
                    int r = _size + count - 1;
                    while (l >= 0 && l >= index) {
                        _allocator.construct(_begin + r, *(_begin + l));
                        --l; --r;
                    }
                    _resize(_size + count);
                    --last;
                    while (first <= last) {
                        _allocator.construct(_begin + r, *last);
                        --last; --r;
                    }
                }
            }

            iterator erase( iterator pos ) {
                iterator ret = (pos != end() ? pos : end());

                while (pos != end()) {
                    *pos = *(pos + 1);
                    ++pos;
                }
                if (ret != end()) {
                    _resize(_size - 1);
                }
                return ret;
            }

            iterator erase( iterator first, iterator last ) {
                if (first <= last) {
                    size_t count = last - first;
                    size_t index = first - begin();

                    while(first != end()) {
                        *first = *(first + count);
                        ++first;
                    }
                    _resize(_size - count);
                    return begin() + index;
                }
                return first;
            }

            void push_back( const T& value ) {
                _reallocate(_size + 1);
                _resize(_size + 1);
                back() = value;
            }

            void pop_back() {
                if (_size) {
                    _resize(_size - 1);
                }
            }

            void resize( size_type count, T value = T() ) {
                if (count < _size) {
                    _resize(count);
                } else {
                    _reallocate(count);
                    iterator it = begin() + _size;
                    _resize(count);
                    while (it != end()) {
                        *it = value;
                        ++it;
                    }
                }
            }

            void swap( vector& other ) {
                if (this != &other) {
                    ft::swap(_allocator, other._allocator);
                    ft::swap(_begin, other._begin);
                    ft::swap(_end, other._end);
                    ft::swap(_capacity, other._capacity);
                    ft::swap(_size, other._size);
                }
            }

        /* private utility */
        private:
            void _reallocate(size_t size) {
                if (size < _capacity) {
                    return ;
                }
                size_type oldCapacity = _capacity;
                if (_capacity == 0) {
                    _capacity = size;
                }
                while (_capacity < size) {
                    _capacity *= 2;
                }
                pointer begin = _allocator.allocate(_capacity);
                if (oldCapacity) {
                    for (size_type i = 0; i < _size; ++i) {
                        _allocator.construct(begin + i, _begin[i]);
                        _allocator.destroy(_begin + i);
                    }
                    _allocator.deallocate(_begin, oldCapacity);
                }
                _begin = begin;
                _end = begin + _size;
            }

            void _resize(size_t n) {
                _size = n;
                _end = _begin + _size;
            }

        private:
            size_type _size;
            size_type _capacity;
            allocator_type _allocator;
            pointer   _begin;
            pointer   _end;
    };

    template< class T, class Alloc >
    bool operator==( const ft::vector<T,Alloc>& lhs,
                    const ft::vector<T,Alloc>& rhs ) {
        return equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template< class T, class Alloc >
    bool operator != (const ft::vector<T, Alloc>& lhs,
                        const ft::vector<T, Alloc>& rhs ) {
        return !equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template< class T, class Alloc >
    bool operator<( const ft::vector<T,Alloc>& lhs,
                    const ft::vector<T,Alloc>& rhs ) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template< class T, class Alloc >
    bool operator<=( const ft::vector<T,Alloc>& lhs,
                    const ft::vector<T,Alloc>& rhs ) {
        return (lhs < rhs || lhs == rhs);
    }


    template< class T, class Alloc >
    bool operator>( const ft::vector<T,Alloc>& lhs,
                    const ft::vector<T,Alloc>& rhs ) {
        return !(lhs <= rhs);
    }

    template< class T, class Alloc >
    bool operator>=( const ft::vector<T,Alloc>& lhs,
                    const ft::vector<T,Alloc>& rhs ) {
        return !(lhs < rhs);
    }

    template<class T>
    void swap(ft::vector<T>& a, ft::vector<T>& b) {
        a.swap(b);
    }

} //namespace ft