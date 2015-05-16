
#include <iostream>
#include <sstream>
#include <string>
#include <functional>

#include <lib/fluke/src/lexer.h>

void check_lexer()
{
    using namespace std;
    using namespace om636;
    using namespace fluke;
    
    typedef brute_lexer< istream, function<void( string, string ) > > lexer_type;
    
    unsigned counter(0);
    
    stringstream s;
    s << "5;";
    s << "3\n";
    
    lexer_type lexer( { " ", "\n", "\t", ";" } );
    lexer.split( s, [&](string c, string s) 
        {
            switch(counter++) 
            {
                case 0:
                    ASSERT( c == ";" );
                    ASSERT( s == "5" );
                break;
                case 1:
                    ASSERT( c == "\n" );
                    ASSERT( s == "3" );
                break;
            } 
        } );

    ASSERT( counter == 2 );
    FOOTER;
}