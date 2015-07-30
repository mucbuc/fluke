/*
om636
Copyright (c) 2013 by Mark Busenitz
www.github.com/mucbuc
*/

#ifndef INTERFACE_H__OP9AqdswJS0HDKNy5lzRIhCvfFXEb3
#define INTERFACE_H__OP9AqdswJS0HDKNy5lzRIhCvfFXEb3

namespace om636
{ 
    template<class T>
    int sign(const T &);
    
    template<class T>
    int cmp(const T &, const T &);

    template<class T, class U>
    int cmp(const T &, const U &);

    template<class T>
    T gcd( const T &, const T &);

    template<class T>
    T euclidian(T, T);

    template<class T, class O>
    std::pair<T, O> euclidian(T, T, O);
}

#include "interface.hxx"

#endif // INTERFACE_H__OP9AqdswJS0HDKNy5lzRIhCvfFXEb3