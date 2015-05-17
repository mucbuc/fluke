
#include <iostream>
#include <sstream>
#include <string>
#include <functional>

#include <lib/fluke/src/lexer.h>

void tester()
{}

void check_lexer()
{
    using namespace std;
    using namespace om636;
    using namespace fluke;
    
    typedef std::vector<char> buffer_type;
    
    unsigned counter(0);
    
    stringstream s;
    s << "5;";
    s << "3\n";
    
    auto is_delimiter( [](char w) -> bool {
        static buffer_type delimiters( { ' ', '\n', '\t', ';' } );
        return std::find(delimiters.begin(), delimiters.end(), w) != delimiters.end();
    } );

    typedef typename buffer_type::const_iterator const_iterator;
    auto handle_delimiter( [& counter](char c, const_iterator b, const_iterator e) {
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
    
    split( s, is_delimiter, handle_delimiter );
            
    ASSERT( counter == 2 );
    FOOTER;
}