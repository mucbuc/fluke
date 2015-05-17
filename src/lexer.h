/* 
	type: ??? should i block copy ???

	objective:
		- lexical analysis

	blocked:
		- assignment: lazyness
		- i cant think of a good reason to block, but cant think of a good reason to allow

	todo: 	
		- specialize for c style strings 

	design change:

*/

#ifndef LEXER_H_8900700
#define LEXER_H_8900700

#include <utility>
#include <vector>

namespace om636
{
	namespace fluke
	{
        template<class T, class U, class V>
        void
        splitAll(
                 T & input,
                 U delimiter_predicate,
                 std::function<void(typename T::char_type,
                                    typename V::const_iterator,
                                    typename V::const_iterator)>,
                 V & buffer);
        
        template<class T, class U>
        void
        splitAll(
                 T & input,
                 U delimiter_predicate,
                 std::function<void(typename T::char_type,
                                    typename std::vector<typename T::char_type>::const_iterator,
                                    typename std::vector<typename T::char_type>::const_iterator)>);
        
        
    } // fluke
}	// om636

#include "lexer.hxx"

#endif // LEXER_H_8900700