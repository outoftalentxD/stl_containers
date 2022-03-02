#pragma once

#include "iterators.hpp"
#include "iterators_traits.hpp"

namespace ft {

    /* algorithm */
    template<class InputIt>
    typename iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last) {
        typename iterator_traits<InputIt>::difference_type diff = 0;
        while (first != last) {
            ++diff; ++first;
        }
        return diff;
    }

    template<class T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    template<class T>
    struct less {
        bool operator()(const T& lhs, const T& rhs) const {
            return (lhs < rhs);
        }
    };

    /* lexicographical_compare */
    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2 ) {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2) {
                return true;
            }
            if (*first2 < *first1) {
                return false;
            }
        }
        return (first1 == last1) && (first2 != last2);
    }

    template< class InputIt1, class InputIt2, class Compare >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              Compare comp) {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (comp(*first1, *first2)) {
                return true;
            }
            if (comp(*first2, *first1)) {
                return false;
            }
        }
        return (first1 == last1) && (first2 != last2);
    }

    /* equal */
    template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2) {
        size_t size1 = ft::distance(first1, last1);
        size_t size2 = ft::distance(first2, last2);
        if (size1 == size2) {
            for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
                if (*first1 != *first2)
                    return false;
            }
            return true;
        } else {
            return false;
        }
    }

    template<class InputIt1, class InputIt2, class BinaryPredicate>
    bool equal(InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2, BinaryPredicate p) {
        size_t size1 = last1 - first1;
        size_t size2 = last2 - first2;
        if (size1 == size2) {
            for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
                if (!p(*first1, *first2))
                    return false;
            }
        }
        return (size1 == size2);
    }

    /* is_integral */
    template<class T, bool v>
    struct integral_constant {
        static const bool value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
    };

    template<class T> struct is_integral : public integral_constant<T, false> {};
    template<> struct is_integral<bool> : public integral_constant<bool, true> {};
    template<> struct is_integral<char> : public integral_constant<char, true> {};
    template<> struct is_integral<char16_t> : public integral_constant<char16_t, true> {};
    template<> struct is_integral<char32_t> : public integral_constant<char32_t, true> {};
    template<> struct is_integral<wchar_t> : public integral_constant<wchar_t, true> {};
    template<> struct is_integral<short> : public integral_constant<short, true> {};
    template<> struct is_integral<int> : public integral_constant<int, true> {};
    template<> struct is_integral<long> : public integral_constant<long, true> {};
    template<> struct is_integral<long long> : public integral_constant<long long, true> {};
    template<> struct is_integral<unsigned short> : public integral_constant<unsigned short, true> {};
    template<> struct is_integral<unsigned int> : public integral_constant<unsigned int, true> {};
    template<> struct is_integral<unsigned long> : public integral_constant<unsigned long, true> {};
    template<> struct is_integral<unsigned long long> : public integral_constant<unsigned long long, true> {};

    /* enable_if */
    template<bool B, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

} //namespace ft
