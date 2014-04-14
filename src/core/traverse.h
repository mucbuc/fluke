/*
om636
Copyright (c) 2013 by Mark Busenitz
www.github.com/mucbuc

objective:
    - std::tuple traversal functions
 
dependancies:
    - std::tuple

usage: 
    - the last argument is the functor handling the elements
    - the tuples can be passed by left reference, right reference or const reference
    - '_if' versions cancel traversal if the functor returns false
    
    unary:
    - traverse::elements( tuple< a, b, c >(), f );
        ==> f( a ); f( b ); b( c );
    - traverse::combinations( tuple< a, b, c >(), f );
        ==> f( a, b ); f( a, c ); f( b, c );
    - traverse::pairs( tuple< a, b, c >(), f );
        ==> f( a ); f( a, b ); f( b, c );
    - traverse::reduce( tuple< a, b, c >(), f );
        ==> f( f( a, b ), c );
 
    binary:
    - traverse::parallel( tuple< a, b, c >(), tuple< d, e >(), f );
        ==> f( a, d ); f( b, e );
    - traverse::combinations( tuple< a, b, c >(), tuple< d, e >(), f );
        ==> f( a, d ); f( a, e ); f( b, d ); f( b, e ); f( c, d ); f( c, e );
 
todo: 
    - test

 */

#ifndef TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq
#define TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq

#include <tuple>

namespace om636
{
    namespace traverse
    {

    //  unary
        template<class T, class U> U elements(T &, U);
        template<class T, class U> U elements(T &&, U);
        template<class T, class U> U elements(const T &, U);
        
        template<class T, class U> U elements_if(T &, U);
        template<class T, class U> U elements_if(T &&, U);
        template<class T, class U> U elements_if(const T &, U);

        template<class T, class U> U combinations(T &, U);
        template<class T, class U> U combinations(T &&, U);
        template<class T, class U> U combinations(const T &, U);
        
        template<class T, class U> U combinations_if(T &, U);
        template<class T, class U> U combinations_if(T &&, U);
        template<class T, class U> U combinations_if(const T &, U);

        template<class T, class U> U pairs(T &, U);
        template<class T, class U> U pairs(T &&, U);
        template<class T, class U> U pairs(const T &, U);
        
        template<class T, class U> U pairs_if(T &, U);
        template<class T, class U> U pairs_if(T &&, U);
        template<class T, class U> U pairs_if(const T &, U);
        
        template<class T, class U, class V> std::tuple<T, V> reduce(U &, V);
        template<class T, class U, class V> std::tuple<T, V> reduce(U &&, V);
        template<class T, class U, class V> std::tuple<T, V> reduce(const U &, V);
        
    //  binary
        template<class T, class V> V parallel(T &, T &, V);
        template<class T, class V> V parallel(T &, T &&, V);
        template<class T, class V> V parallel(T &, const T &, V);
        
        template<class T, class V> V parallel(T &&, T &, V);
        template<class T, class V> V parallel(T &&, T &&, V);
        template<class T, class V> V parallel(T &&, const T &, V);
        
        template<class T, class V> V parallel(const T &, T &, V);
        template<class T, class V> V parallel(const T &, T &&, V);
        template<class T, class V> V parallel(const T &, const T &, V);
        
        template<class T, class U, class V> V parallel(T &, U &, V);
        template<class T, class U, class V> V parallel(T &, U &&, V);
        template<class T, class U, class V> V parallel(T &, const U &, V);
        
        template<class T, class U, class V> V parallel(T &&, U &, V);
        template<class T, class U, class V> V parallel(T &&, U &&, V);
        template<class T, class U, class V> V parallel(T &&, const U &&, V);
        
        template<class T, class U, class V> V parallel(const T &, U &, V);
        template<class T, class U, class V> V parallel(const T &, U &&, V);
        template<class T, class U, class V> V parallel(const T &, const U &&, V);
        
        template<class T, class V> V parallel_if(T &, T &, V);
        template<class T, class V> V parallel_if(T &, T &&, V);
        template<class T, class V> V parallel_if(T &, const T &, V);
        
        template<class T, class V> V parallel_if(T &&, T &, V);
        template<class T, class V> V parallel_if(T &&, T &&, V);
        template<class T, class V> V parallel_if(T &&, const T &, V);
        
        template<class T, class V> V parallel_if(const T &, T &, V);
        template<class T, class V> V parallel_if(const T &, T &&, V);
        template<class T, class V> V parallel_if(const T &, const T &, V);
        
        template<class T, class U, class V> V parallel_if(T &, U &, V);
        template<class T, class U, class V> V parallel_if(T &, U &&, V);
        template<class T, class U, class V> V parallel_if(T &, const U &, V);
        
        template<class T, class U, class V> V parallel_if(T &&, U &, V);
        template<class T, class U, class V> V parallel_if(T &&, U &&, V);
        template<class T, class U, class V> V parallel_if(T &&, const U &&, V);
        
        template<class T, class U, class V> V parallel_if(const T &, U &, V);
        template<class T, class U, class V> V parallel_if(const T &, U &&, V);
        template<class T, class U, class V> V parallel_if(const T &, const U &, V);
        
        template<class T, class V> V combinations(T &, T &, V);
        template<class T, class V> V combinations(T &, T &&, V);
        template<class T, class V> V combinations(T &, const T &, V);
        
        template<class T, class V> V combinations(T &&, T &, V);
        template<class T, class V> V combinations(T &&, T &&, V);
        template<class T, class V> V combinations(T &&, const T &, V);
        
        template<class T, class V> V combinations(const T &, T &, V);
        template<class T, class V> V combinations(const T &, T &&, V);
        template<class T, class V> V combinations(const T &, const T &, V);
        
        template<class T, class U, class V> V combinations(T &, U &, V);
        template<class T, class U, class V> V combinations(T &, U &&, V);
        template<class T, class U, class V> V combinations(T &, const U &, V);
        
        template<class T, class U, class V> V combinations(T &&, U &, V);
        template<class T, class U, class V> V combinations(T &&, U &&, V);
        template<class T, class U, class V> V combinations(T &&, const U &&, V);
        
        template<class T, class U, class V> V combinations(const T &, U &, V);
        template<class T, class U, class V> V combinations(const T &, U &&, V);
        template<class T, class U, class V> V combinations(const T &, const U &&, V);
        
        template<class T, class V> V combinations_if(T &, T &, V);
        template<class T, class V> V combinations_if(T &, T &&, V);
        template<class T, class V> V combinations_if(T &, const T &, V);
        
        template<class T, class V> V combinations_if(T &&, T &, V);
        template<class T, class V> V combinations_if(T &&, T &&, V);
        template<class T, class V> V combinations_if(T &&, const T &, V);
        
        template<class T, class V> V combinations_if(const T &, T &, V);
        template<class T, class V> V combinations_if(const T &, T &&, V);
        template<class T, class V> V combinations_if(const T &, const T &, V);
        
        template<class T, class U, class V> V combinations_if(T &, U &, V);
        template<class T, class U, class V> V combinations_if(T &, U &&, V);
        template<class T, class U, class V> V combinations_if(T &, const U &, V);
        
        template<class T, class U, class V> V combinations_if(T &&, U &, V);
        template<class T, class U, class V> V combinations_if(T &&, U &&, V);
        template<class T, class U, class V> V combinations_if(T &&, const U &&, V);
        
        template<class T, class U, class V> V combinations_if(const T &, U &, V);
        template<class T, class U, class V> V combinations_if(const T &, U &&, V);
        template<class T, class U, class V> V combinations_if(const T &, const U &, V);
    
        namespace Private
        {
            // elements_impl
            template<int, int, class>
            struct elements_impl;
            
            template<int M, class T>
            struct elements_impl< M, M, T >;
            
            
            // combinations_impl
            template<int, int, int, class >
            struct combinations_impl;
            
            template<int M, int N, class T>
            struct combinations_impl< M, N, N, T >;
            
            template<int M, int N, class T >
            struct combinations_impl< M, N, M, T >;
            

            // pairs_impl
            template<int, int, class>
            struct pairs_impl;
            
            template<int M, class T>
            struct pairs_impl< 2, M, T>;
            
            template<int M, class T>
            struct pairs_impl< M, M, T>;
            
            template<class T>
            struct pairs_impl<2, 2, T>;
            
            template<class T>
            struct pairs_impl<2, 1, T>;
            
            
            // reduce_impl
            template<int, int, class, class>
            struct reduce_impl;
            
            template<int M, class T, class U>
            struct reduce_impl< M, M, T, U>;
            
            template<class T, class U>
            struct reduce_impl<2, 1, T, U>;
            
            
            // parallel_impl
            template<int, int, class, class>
            struct parallel_impl;
            
            template<int M, class T, class U>
            struct parallel_impl< M, M, T, U >;
            
            
            // combinations_binary_impl
            template<int, int, int, int, class, class>
            struct combinations_binary_impl;
            
            template<int M, int N, int O, class T, class U>
            struct combinations_binary_impl< M, N, O, N, T, U >;
            
            template<int M, int N, int O, class T, class U>
            struct combinations_binary_impl< M, N, M, O, T, U >;
            
        }   // Private
    }   // traverse
}   //  om636

#include "traverse.hxx"

#endif // __TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq
