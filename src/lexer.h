#ifndef LEXER_H_8900700
#define LEXER_H_8900700

#include <vector>
#include <functional>
#include <type_traits> 

namespace om636
{
    namespace fluke
    {
        template<class T, class U = typename T::value_type::value_type> 
        struct splitter
        {
            typedef T token_type; 
            typedef typename token_type::value_type::value_type char_type; 

            template<class V, class W>
            static 
            void split(
                     V &,
                     std::function<bool(char_type)>,
                     std::function<void(token_type)>,
                     W &);
            
            template<class V>
            static void split(
                     V &,
                     std::function<bool(char_type)>,
                     std::function<void(token_type)>);
        };

        template<class T, class U = std::vector< typename T::value_type::value_type > >
        struct buffered_splitter
        : splitter<T, typename U::value_type>
        {
            typedef T token_type; 
            typedef U buffer_type;
            typedef typename buffer_type::value_type char_type; 
            typedef typename buffer_type::const_iterator const_iterator;

            template<class V>
            void
            static split(
                     V &,
                     std::function<bool(char_type)>,
                     std::function<void(char_type, const_iterator, const_iterator)>,
                     U &);
            
            template<class V>
            void
            static split(
                     V &,
                     std::function<bool(char_type)>,
                     std::function<void(char_type, const_iterator, const_iterator)>);
        };
    } // fluke
}   // om636

#include "lexer.hxx"

#endif // LEXER_H_8900700