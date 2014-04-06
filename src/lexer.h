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

#ifndef _lexer_H_8900700
#define _lexer_H_8900700

#include <om636/src/parser/parserfwd.h>

namespace om636
{
	template<class T, class U>
	class lexer
	{
	public:
		// types
		typedef T token_type;
		typedef U stream_type;		
			
        lexer() = delete;
        lexer( const lexer & ) = delete;
        lexer & operator=(const lexer &) = delete;
		~lexer() = default;
        
        // resources
        lexer(stream_type &);
	    
        // access
		const size_t & count() const;
		const token_type & next();
		const token_type & current() const;	
    
    private:
        stream_type & m_stream;
		token_type m_token;
		size_t m_count;
		char m_front;
    };
    
}	// om636

#include "lexer.hxx"

#endif // _lexer_H_8900700