#pragma once

#include "vector.hpp"


namespace ft {
    template<class T, class Container = vector<T> >
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
        public:
            template<class U, class V>
            friend bool operator==(const stack<U, V>& lhs, const stack<U, V>& rhs);

            template<class U, class V>
            friend bool operator!=(const stack<U, V>& lhs, const stack<U, V>& rhs);

            template<class U, class V>
            friend bool operator<(const stack<U, V>& lhs, const stack<U, V>& rhs);

            template<class U, class V>
            friend bool operator>(const stack<U, V>& lhs, const stack<U, V>& rhs);

            template<class U, class V>
            friend bool operator<=(const stack<U, V>& lhs, const stack<U, V>& rhs);

            template<class U, class V>
            friend bool operator>=(const stack<U, V>& lhs, const stack<U, V>& rhs);

        private:
            container_type c;

    };

    template<class T>
    bool operator==(const stack<T>& lhs, const stack<T>& rhs) {
        return lhs.c == rhs.c;
    }


    template<class T>
    bool operator!=(const stack<T>& lhs, const stack<T>& rhs) {
        return lhs.c != rhs.c;
    }


    template<class T>
    bool operator<(const stack<T>& lhs, const stack<T>& rhs) {
        return lhs.c < rhs.c;
    }

    template<class T>
    bool operator>(const stack<T>& lhs, const stack<T>& rhs) {
        return lhs.c == rhs.c;
    }

    template<class T>
    bool operator>=(const stack<T>& lhs, const stack<T>& rhs) {
        return lhs.c == rhs.c;
    }

    template<class T>
    bool operator<=(const stack<T>& lhs, const stack<T>& rhs) {
        return lhs.c == rhs.c;
    }

}; //namespace ft