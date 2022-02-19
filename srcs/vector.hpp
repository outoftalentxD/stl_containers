#pragma once

#include <iostream>
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
            explicit vector(const allocator_type& allocator = allocator_type()) : _size(0), _capacity(0), _allocator(allocator), _begin(), _end() {

            }

            explicit vector(size_type size, const_reference value = value_type(), const allocator_type& allocator = allocator_type())
                    : _allocator(allocator), _size(size), _begin(), _end() {
                if (size > 0) {
                    _reallocate(size);
                    for (size_type i = 0; i < size; i++) {
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
            vector(InputIt first, InputIt last, const allocator_type& allocator = allocator_type()) {

            }

            vector& operator=(const vector& oth) {
                if (this != &oth) {
                    clear();
                    _size = oth._size;
                    _capacity = oth._capacity;
                    _allocator = oth._allocator;

                    _begin = _allocator.allocate(_begin, _capacity);
                    _end = _begin + _size;
                    for (size_type i = 0; i < _size; i++) {
                        _allocator.construct(_begin, oth[i]);
                    }
                }
                return (*this);
            }

            ~vector() {
                clear();
                _allocator.deallocate(_begin, _capacity);
            }

            void assign(size_type count, const_reference value) {
                _reallocate(count);
                _size = count;
                for (size_type i = 0; i < _size; i++) {
                    *(_begin + i) = value;
                }
                _end = _begin + _size;
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

            const_reference fron() const {
                return _begin[0];
            }

            reference back() {
                return _end[0];
            }

            const_reference back() const {
                return _end[0];
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
                return allocator_type().max_size();
            }

            void reserve(size_type new_cap) {
                if (new_cap > _capacity) {
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

            void clear() {
                for (size_t i = 0; i < _size; i++) {
                    _allocator.destroy(_begin + i);
                }
                _size = 0;
                _end = _begin;
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
                return --_end;
            }

            reverse_iterator rend() {
                return _begin;
            }

            const_reverse_iterator rbegin() const {
                return --end();
            }

            const_reverse_iterator rend() const {
                return _begin();
            }

        private:
            void _reallocate(size_t size) {

                if (size < _size) //is this good decision?
                    return ;
                size_type old_cap = _capacity;
                if (_capacity == 0) {
                    _capacity = size;
                }
                while (_capacity < size) {
                    _capacity *= 2;
                }

                pointer begin, end;
                begin = _allocator.allocate(_capacity);
                end = begin;
                for (size_type i = 0; i < _size; i++) {
                    _allocator.construct(end, _begin[i]);
                    _allocator.destroy(_begin + i);
                    end++;
                } // need to dealloc _begin?
                _allocator.deallocate(_begin, old_cap);
                _begin = begin;
                _end = begin + _size;
            }

        private:
            size_type _size;
            size_type _capacity;
            pointer   _begin;
            pointer   _end;
            allocator_type _allocator;

    };
}
