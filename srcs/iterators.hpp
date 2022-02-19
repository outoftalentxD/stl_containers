#pragma once

#include <iostream>
#include "iterators_traits.hpp"

namespace ft {
    template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };

    template<class T, class Pointer = T*, class Reference = T&, class Distance = std::ptrdiff_t>
    class OwnIterator : public iterator<random_access_iterator_tag, T, Pointer, Reference, Distance> {
        public:
            typedef iterator<random_access_iterator_tag, T> iter;
            typedef typename iter::pointer pointer;
            typedef typename iter::reference reference;

        public:
            OwnIterator(pointer ptr = nullptr) : _ptr(ptr) {

            }

            OwnIterator(const OwnIterator& oth ) : _ptr(oth._ptr) {

            }

            const OwnIterator& operator=(const OwnIterator& oth) {
                if (this != &oth) {
                    _ptr = oth._ptr;
                }
                return (*this);
            }

            ~OwnIterator() {

            }

        public:

            OwnIterator& operator++(void) {
                _ptr++;
                return (*this);
            }

            OwnIterator operator++(int) const {
                OwnIterator ret(*this);

                ret._ptr++;
                return (ret);
            }

            OwnIterator& operator+=(int n) {
                _ptr += n;
                return *this;
            }

            OwnIterator& operator+(int n) const {
                OwnIterator ret(*this);

                ret._ptr += n;
                return ret;
            }

            OwnIterator& operator--(void) {
                _ptr--;
                return *this;
            }

            OwnIterator operator--(int) const {
                OwnIterator ret(*this);

                ret._ptr--;
                return ret;
            }

            OwnIterator& operator-=(int n) {
                _ptr -= n;
                return *this;
            }

            OwnIterator& operator-(int n) const {
                OwnIterator ret(*this);

                ret._ptr -= n;
                return ret;
            }

            reference operator*() const {
                return *_ptr;
            }

            pointer operator->() const {
                return _ptr;
            }

            bool operator==(const OwnIterator& rhs) const {
                return _ptr == rhs._ptr;
            }

            bool operator!=(const OwnIterator& rhs) const {
                return _ptr != rhs._ptr;
            }

            bool operator>=(const OwnIterator& rhs) const {
                return _ptr >= rhs._ptr;
            }

            bool operator>(const OwnIterator& rhs) const {
                return _ptr > rhs._ptr;
            }

            bool operator<=(const OwnIterator& rhs) const {
                return _ptr <= rhs._ptr;
            }

            bool operator<(const OwnIterator& rhs) const {
                return _ptr < rhs._ptr;
            }

        protected:

        private:
            pointer _ptr;
    };

    template<class Iter>
    class reverse_iterator {
        public:
            typedef Iter                            iterator_type;
            // typedef typename iterator_traits<Iter>           traits_type;
            typedef typename iterator_traits<Iter>::iterator_category  iterator_category;
            typedef typename iterator_traits<Iter>::value_type         value_type;
            typedef typename iterator_traits<Iter>::difference_type    difference_type;
            typedef typename iterator_traits<Iter>::pointer            pointer;
            typedef typename iterator_traits<Iter>::reference          reference;

        public:
            reverse_iterator() : _iter() {

            }

            reverse_iterator(iterator_type iter) : _iter(iter) {

            }

            reverse_iterator(const reverse_iterator& oth) : _iter(oth._iter) {

            }

            template<class T>
            reverse_iterator& operator=(const reverse_iterator<T>& oth) {
                if (this != &oth) {
                    _iter = oth._iter;
                }
                return (*this);
            }
            ~reverse_iterator() {

            }

        public:

            iterator_type base() const {
                return _iter;
            }

            reference operator*() const {
                return *_iter;
            }

            pointer operator->() const {
                return &(*_iter);
            }

            reference operator[](difference_type n) {
                return _iter[-n - 1];
            }

            reverse_iterator& operator++() {
                --_iter;
                return *this;
            }

            reverse_iterator operator++(int) {
                reverse_iterator ret(*this);

                --_iter;
                return ret;
            }

            reverse_iterator& operator--() {
                ++_iter;
                return *this;
            }

            reverse_iterator operator--(int) {
                reverse_iterator ret(*this);

                ++_iter;
                return ret;
            }

            reverse_iterator operator+(difference_type n) const {
                reverse_iterator ret(*this);

                ret._iter -= n;
                return ret;
            }

            reverse_iterator operator-(difference_type n) const {
                reverse_iterator ret(*this);

                ret._iter += n;
                return ret;
            }

            reverse_iterator& operator+=(difference_type n) {
                _iter -= n;
                return *this;
            }

            reverse_iterator& operator-=(difference_type n) {
                _iter += n;
                return *this;
            }

            template<class T>
            bool operator==(const reverse_iterator<T>& rhs) const {
                return (_iter == rhs._iter);
            }

            template<class T>
            bool operator!=(const reverse_iterator<T>& rhs) const {
                return (_iter != rhs._iter);
            }

            template<class T>
            bool operator>=(const reverse_iterator<T>& rhs) const {
                return (_iter >= rhs._iter);
            }

            template<class T>
            bool operator<=(const reverse_iterator<T>& rhs) const {
                return (_iter <= rhs._iter);
            }

            template<class T>
            bool operator>(const reverse_iterator<T>& rhs) const {
                return (_iter > rhs._iter);
            }

            template<class T>
            bool operator<(const reverse_iterator<T>& rhs) const {
                return (_iter < rhs._iter);
            }

        private:
            iterator_type _iter;
    };

    template< class Iterator1, class Iterator2 >
    bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
        return (lhs == rhs);
    }

    template< class Iterator1, class Iterator2 >
    bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
        return (lhs != rhs);
    }

    template< class Iterator1, class Iterator2 >
    bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
        return (lhs >= rhs);
    }

    template< class Iterator1, class Iterator2 >
    bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
        return (lhs <= rhs);
    }

    template< class Iterator1, class Iterator2 >
    bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
        return (lhs > rhs);
    }

    template< class Iterator1, class Iterator2 >
    bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
        return (lhs < rhs);
    }

    template< class Iter >
    reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
        return it.base() - n;
    }

    template< class Iterator >
    typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) {
        return rhs.base() - lhs.base();
    }

} //namespace ft
