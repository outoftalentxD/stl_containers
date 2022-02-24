#pragma once

#include <ostream>

namespace ft {

    template<class F, class S>
    struct pair {
        public:
            typedef F first_type;
            typedef S second_type;

        public:
            first_type first;
            second_type second;

        public:

        pair() : first(), second() {

        }

        pair( const F& x, const S& y ) : first(x), second(y) {

        }

        template<class U, class V>
        pair(const pair<U, V>& other) : first(other.first), second(other.second) {

        }

        pair& operator=(const pair& other ) {
            if (this != &other) {
                first = other.first;
                second = other.second;
            }
            return *this;
        }

        ~pair() {

        }
    };

    template<class F, class S>
    bool operator==(const pair<F, S>& lhs, const pair<F, S>& rhs) {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }


    template<class F, class S>
    bool operator!=(const pair<F, S>& lhs, const pair<F, S>& rhs) {
        return (lhs.first != rhs.first || lhs.second != rhs.second);
    }

    template<class F, class S>
    bool operator<(const pair<F, S>& lhs, const pair<F, S>& rhs) {
        if (lhs.first < rhs.first) {
            return true ;
        } else {
            if (lhs.second < rhs.second) {
                return true;
            } else {
                return false;
            }
        }
    }

    template<class F, class S>
    bool operator<=(const pair<F, S>& lhs, const pair<F, S>& rhs) {
        return (lhs == rhs || lhs < rhs);
    }

    template<class F, class S>
    bool operator>(const pair<F, S>& lhs, const pair<F, S>& rhs) {
        return !(lhs <= rhs);
    }

    template<class F, class S>
    bool operator>=(const pair<F, S>& lhs, const pair<F, S>& rhs) {
        return !(lhs < rhs);
    }

    template<class F, class S>
    pair<F, S> make_pair(F x, S y) {
        return pair<F, S>(x, y);
    }

    template<class F, class S>
    std::ostream& operator<<(std::ostream& os, const pair<F, S>& pair) {
        os << pair.first << " " << pair.second;
        return os;
    }

}; // namespace ft