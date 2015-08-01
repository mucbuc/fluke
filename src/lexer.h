#ifndef LEXER_H_8900700
#define LEXER_H_8900700

#include <vector>
#include <functional>
#include <type_traits> 

namespace om636
{
    namespace fluke
    {
        template<class T> 
        struct splitter
        {
            typedef T token_type; 
            typedef typename token_type::value_type string_type;
            typedef typename string_type::value_type char_type; 

            template<class U, class V>
            void
            static split(
                     U &,
                     std::function<bool(char_type)>,
                     std::function<void(char_type,
                                        typename V::const_iterator,
                                        typename V::const_iterator)>,
                     V &);
            
            template<class U>
            void
            static split(
                     U &,
                     std::function<bool(char_type)>,
                     std::function<void(char_type,
                                        typename std::vector<char_type>::const_iterator,
                                        typename std::vector<char_type>::const_iterator)>);


            template<class U, class V>
            void
            static split(
                     U &,
                     std::function<bool(char_type)>,
                     std::function<void(token_type)>,
                     V &);

            template<class U>
            void
            static split(
                     U &,
                     std::function<bool(char_type)>,
                     std::function<void(token_type)>);

        };


        // template<class T, class U, class V, class W>
        // void
        // split(
        //          T &,
        //          std::function<bool(W)>,
        //          std::function<void(U)>,
        //          V &);
        
        // template<class T, class U, class V>
        // void
        // split(
        //          T &,
        //          std::function<bool(V)>,
        //          std::function<void(U)>);

        
    } // fluke
}   // om636

#include "lexer.hxx"

#endif // LEXER_H_8900700