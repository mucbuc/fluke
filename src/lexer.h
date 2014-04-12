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

namespace om636
{
	namespace lexer
	{
		template<class T, class U, class V>
	    void tokenize( T &, U &, const V & );
        
        void fuck(); 
        
   } // lexer

}	// om636

#include "lexer.hxx"

#endif // LEXER_H_8900700