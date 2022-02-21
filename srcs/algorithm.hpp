#pragma once

#include "iterators.hpp"
#include "iterators_traits.hpp"


namespace ft {
    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2 ) {
        size_t size1 = last1 - first1;
        size_t size2 = last2 - first2;
        for ( ; first1 != last1 && first2 != last2; ) {
            if (*first1 >= *first2) {
                return false;
            }
            ++first1; ++first2;
        }
        return (size1 >= size2);
    }

    template< class InputIt1, class InputIt2, class Compare >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              Compare comp ) {
        size_t size1 = last1 - first1;
        size_t size2 = last2 - first2;
        for ( ; first1 != last1 && first2 != last2; ) {
            if (!comp(*first1, *first2)) {
                return false;
            }
            ++first1; ++first2;
        }
        return (size1 >= size2);
    }

    template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2) {
        size_t size1 = last1 - first1;
        size_t size2 = last2 - first2;
        if (size1 == size2) {
            for (; first1 != last1 && first2 != last2;) {
                if (*first1 != *first2)
                    return false;
            }
            return true;
        } else {
            return false;
        }
    }

} //namespace ft
