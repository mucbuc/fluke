/*	
	type: concrete

	objective:	
		- get token from stream 
		- hold token value and type 
 
    todo: 
        - the constructor has some arbitrary logic in it, need to imporove using policy classes
        - need to handle/throw exceptions
        - 
    
*/

#ifndef _token_H_8900700
#define _token_H_8900700

#include <string>
#include <sstream>
#include <om636/src/parser/parserfwd.h>

namespace om636
{
	template<class T>
	class token 
	{
		struct tester
		{	void operator delete(void*);	};

		template<class U>
		void read_next( U & in, char & front );

    public:
		
        typedef T value_type; 
        enum token_id { number, variable, _operator, terminator, error };
		
		// resources
		token();
		template<class U> token( U & );
		template<class U> token( U &, char & );
		token( const token & );
		token & operator=( token );
		void swap( token & );	
		
		// access
		const value_type & name() const;
		token_id type() const;
		template<class U> void to_value(U & v) const;
		operator tester*() const;
		bool operator!() const;

	private:
		
		token_id m_type;
		value_type	m_name;
	};

	template<class T>
	void swap( token<T> & lhs, token<T> & rhs );
	
} // om636	

#include "token.hxx"

#endif // _token_H_8900700