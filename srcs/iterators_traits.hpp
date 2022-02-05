#pragma once

#include <iostream>

namespace ft {

    template <class Iter>
    struct iterator_traits {
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::value_type value_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_categoty iterator_category;
    };

    template<class T>
    struct iterator_traits<T*> {
        typedef std::ptrdiff_t  difference_type;
        typedef T value_type    T;
        typedef T* pointer      T*;
        typedef T& reference    T&;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template<class T>
    struct iterator_traits<const T*> {
        typedef std::ptrdiff_t  difference_type;
        typedef T value_type    T;
        typedef T* pointer      T*;
        typedef T& reference    T&;
        typedef std::random_access_iterator_tag iterator_category;
    };
}