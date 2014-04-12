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

#include "flukefwd.h"

namespace om636
{
	namespace fluke
	{
		template<class T, class U> 
		struct lexer
		{
			typedef T stream_type; 
			typedef U analyzer_type; 

			virtual ~lexer() = default;
			virtual void split( stream_type &, analyzer_type & ) const = 0;
		};

		template<class T, class U, class V>
		class brute_lexer 
		: public lexer< T, U > 
		{
			typedef lexer< T, U > base_type;
		public:
			using typename base_type::stream_type;
			using typename base_type::analyzer_type;
			typedef V set_type; 

			// markymarker
			typedef std::string string_type; 

			brute_lexer(const set_type & = { ' ', '\n', '\t' } );
			virtual ~brute_lexer() = default;

			void split( stream_type &, analyzer_type & ) const;

			set_type & delimiters();
			const set_type & delimiters() const;

		private: 
			set_type m_delimiters;
		};

    } // fluke
}	// om636

#include "lexer.hxx"

#endif // LEXER_H_8900700