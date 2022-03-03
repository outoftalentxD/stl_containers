#pragma once

#include "vector.hpp"

namespace ft {
    template<class T, class Container = ft::vector<T> >
    class stack {
        public:
            typedef Container container_type;
            typedef typename Container::value_type value_type;
            typedef typename Container::size_type size_type;
            typedef typename Container::reference reference;
            typedef typename Container::const_reference const_reference;

        public:
            explicit stack( const Container& cont = Container() ) : c(cont){

            }

            stack( const stack& other ) : c(other.c) {

            }

            stack& operator=( const stack& other ) {
                if (this != &other) {
                    c = other.c;
                }
                return *this;
            }

            ~stack() {

            }

        /* element access*/
        public:
            reference top() {
                return c.back();
            }

            const_reference top() const {
                return c.back();
            }

        /* capacity */
        public:
            bool empty() const {
                return c.empty();
            }

            size_type size() const {
                return c.size();
            }

        /* modifiers */
        public:
            void push( const value_type& value ) {
                c.push_back(value);
            }

            void pop() {
                c.pop_back();
            }

        /* comparisions */
        private:
            template<class _value_type, class _container_type>
            friend bool operator==(const ft::stack<_value_type, _container_type>&, const ft::stack<_value_type, _container_type>&);

            template<class _value_type, class _container_type>
            friend bool operator!=(const ft::stack<_value_type, _container_type>&, const ft::stack<_value_type, _container_type>&);

            template<class _value_type, class _container_type>
            friend bool operator<(const ft::stack<_value_type, _container_type>&, const ft::stack<_value_type, _container_type>&);

            template<class _value_type, class _container_type>
            friend bool operator>(const ft::stack<_value_type, _container_type>&, const ft::stack<_value_type, _container_type>&);

            template<class _value_type, class _container_type>
            friend bool operator<=(const ft::stack<_value_type, _container_type>&, const ft::stack<_value_type, _container_type>&);

            template<class _value_type, class _container_type>
            friend bool operator>=(const ft::stack<_value_type, _container_type>&, const ft::stack<_value_type, _container_type>&);

        private:
            container_type c;

    };

    template<class _value, class _container_type>
    inline bool operator==(const ft::stack<_value, _container_type>& _x, const ft::stack<_value, _container_type>& _y) {
        return _x.c == _y.c;
    }

    template<class _value, class _container_type>
    inline bool operator<(const ft::stack<_value, _container_type>& _x, const ft::stack<_value, _container_type>& _y) {
        return _x.c < _y.c;
    }

    template<class _value, class _container_type>
    inline bool operator!=(const ft::stack<_value, _container_type>& _x, const ft::stack<_value, _container_type>& _y) {
        return !(_x == _y);
    }

    template<class _value, class _container_type>
    inline bool operator>(const ft::stack<_value, _container_type>& _x, const ft::stack<_value, _container_type>& _y) {
        return _y < _x;
    }

    template<class _value, class _container_type>
    inline bool operator>=(const ft::stack<_value, _container_type>& _x, const ft::stack<_value, _container_type>& _y) {
        return !(_x < _y);
    }

    template<class _value, class _container_type>
    inline bool operator<=(const ft::stack<_value, _container_type>& _x, const ft::stack<_value, _container_type>& _y) {
        return !(_y < _x);
    }
    
}; //namespace ft