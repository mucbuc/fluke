#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include <lib/fluke/src/lexer.h>
#include <lib/fluke/src/token.h>

using namespace std;
using namespace om636;
using namespace fluke;

typedef vector<char> buffer_type;
typedef typename buffer_type::const_iterator const_iterator;

static auto is_delimiter( [](const char w) -> bool {
    static buffer_type delimiters( { ' ', '\n', '\t', ';' } );
    return std::find(delimiters.begin(), delimiters.end(), w) != delimiters.end();
} );
    
void split_tokens()
{
    stringstream s;
    s << "5;";
    s << "3\n";

    typedef token<std::string> token_type;
    vector<token_type> tokens;
    
    std::function<void(const token_type)> handle_delimiter( [& tokens](const token_type t) {
        tokens.push_back(t);
    } );
    
    split( s, [](typename std::add_const<typename stringstream::char_type>::type w) -> bool {
	static buffer_type delimiters( { ' ', '\n', '\t', ';' } );
    	return std::find(delimiters.begin(), delimiters.end(), w) != delimiters.end();
    }, [& tokens](const token_type t) {
       	tokens.push_back(t);
    });	
    ASSERT(tokens.size() == 2);
    ASSERT(tokens[0].type() == token_type::number);
    ASSERT(tokens[0].name() == "5");
    ASSERT(tokens[0].to_value<int>() == 5);
    ASSERT(tokens[1].type() == token_type::number);
    ASSERT(tokens[1].name() == "3");
    ASSERT(tokens[1].to_value<int>() == 3);
    
    FOOTER;
}

void split_raw()
{
    stringstream s;
    s << "5;";
    s << "3\n";
    
    unsigned counter(0);

    auto handle_delimiter( [& counter](const char c, const_iterator b, const_iterator e) {
        std::string s(b, e);
        switch(counter++)
        {
          case 0:
              ASSERT( c == ';' );
              ASSERT( s == "5" );
              break;
          case 1:
              ASSERT( c == '\n' );
              ASSERT( s == "3" );
              break;
        } 
    } );
    
//    split( s, is_delimiter, handle_delimiter );
            
    ASSERT( counter == 2 );
    FOOTER;
}
