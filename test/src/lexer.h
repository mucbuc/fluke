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
typedef typename std::string::value_type char_type;
typedef token<std::string> token_type;

static auto is_delimiter( [](const char w) -> bool {
    static buffer_type delimiters( { ' ', '\n', '\t', ';' } );
    return std::find(delimiters.begin(), delimiters.end(), w) != delimiters.end();
} );
    
void split_tokens()
{
    stringstream s;
    s << "5;";
    s << "3\n";


    vector<token_type> tokens;
  
    splitter<token_type>::split( s, [](char_type w) -> bool {
	   static buffer_type delimiters( { ' ', '\n', '\t', ';' } );
       return std::find(delimiters.begin(), delimiters.end(), w) != delimiters.end();
    }, 
    [& tokens](token_type t) {
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

    auto handle_delimiter( [& counter](char_type c, const_iterator b, const_iterator e) {
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
    
    splitter<token_type>::split( s, is_delimiter, handle_delimiter );
           
    ASSERT( counter == 2 );
    FOOTER;
}
