/*
	objective:
		- interpret
		- drive lexer
		- own context
		- manage/own handler
		- only operate on T, type conversion, subscriptionn... are T's job

	blocked:
		- assignment and copy constructor because of lazyness
	
	design choices:
		- composition for lexer and context to minimize dependencies 	
	
	example:
*/

#ifndef _parser_H_8900700
	#define _parser_H_8900700

#include <om636/src/components/context.h>

#include <om636/src/components/componentsfwd.h>
#include <om636/src/parser/parserfwd.h>
#include <om636/src/parser/lexer.h>

#include <functional>

namespace om636
{
    template<class T, class U>
	class parser 
	{
		// undefined
		parser();
		parser(const parser &);
		parser & operator=(const parser &);
	    
	public:

		// types			
		typedef T context_type;
		typedef U lexer_type;
        
		// resources
        template<class V> parser( V &, context_type &);
		virtual ~parser() = default;
        
		// access
		context_type & context();
		const context_type & context() const;
		lexer_type & lexer(); 
		const lexer_type & lexer() const; 
	
		// objective
		context_type & interpret();
			
	private:
    
		context_type & m_context;
		lexer_type m_lexer;
	};
    
}	// om636

#include "parser.hxx"

#endif // _parser_H_8900700