#ifndef LEXER_H_8900700
#define LEXER_H_8900700

#include <vector>
#include <functional>

namespace om636
{
    namespace fluke
    {
        template<class T, class U>
        void
        split(
                 T &,
                 std::function<bool(const typename T::char_type)>,
                 std::function<void(const typename T::char_type,
                                    typename U::const_iterator,
                                    typename U::const_iterator)>,
                 U &);
        
        template<class T>
        void
        split(
                 T &,
                 std::function<bool(const typename T::char_type)>,
                 std::function<void(const typename T::char_type,
                                    typename std::vector<typename T::char_type>::const_iterator,
                                    typename std::vector<typename T::char_type>::const_iterator)>);

        template<class T, class U, class V>
        void
        split(
                 T &,
                 std::function<bool(const typename T::char_type)>,
                 std::function<void(U)>,
                 V &);
        
        template<class T, class U>
        void
        split(
                 T &,
                 std::function<bool(const typename T::char_type)>,
                 std::function<void(U)>);

        
    } // fluke
}   // om636

#include "lexer.hxx"

#endif // LEXER_H_8900700