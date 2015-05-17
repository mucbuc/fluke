#ifndef LEXER_H_8900700
#define LEXER_H_8900700

#include <vector>
#include <functional>

namespace om636
{
	namespace fluke
	{
        template<class T, class U, class V>
        void
        split(
                 T &,
                 std::function<bool(typename T::char_type)>,
                 std::function<void(typename T::char_type,
                                    typename V::const_iterator,
                                    typename V::const_iterator)>,
                 V &);
        
        template<class T, class U>
        void
        split(
                 T &,
                 U,
                 std::function<void(typename T::char_type,
                                    typename std::vector<typename T::char_type>::const_iterator,
                                    typename std::vector<typename T::char_type>::const_iterator)>);
        
        
    } // fluke
}	// om636

#include "lexer.hxx"

#endif // LEXER_H_8900700