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

}
