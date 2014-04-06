/*
*/

#ifndef PARSERFWD_H__2o4dFlMz3aCjcPAYgGXN9IiRumnWTK
#define PARSERFWD_H__2o4dFlMz3aCjcPAYgGXN9IiRumnWTK

#include <string>

namespace om636
{
	// parser.h
	template<class context_type, class lexer_type> class parser;
	
	// lexer.h
	template<class, class> class lexer;

	// token.h
	template<class = std::string> class token;

	// states.h
	template<class> struct leaf_handler;
	template<class> struct operator_handler;
	template<class> class builder; 
	
}	// om636 

#endif // __PARSERFWD_H__2o4dFlMz3aCjcPAYgGXN9IiRumnWTK