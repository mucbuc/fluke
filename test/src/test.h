#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include <src/lexer.h>
#include <lib/ohm/src/quemitter.h>

#include "debug.h"

void check_lexer()
{
    using namespace std;
    using namespace om636;
    using namespace fluke;
    
    typedef control::Quemitter< string, function<void( string )> > emitter_type;
    
    emitter_type emitter;
    unsigned counter;

    auto listener( emitter.once( "new line", [&](string val){
        if (val == "3\n")
            ++counter;
    } ) );
    
    auto listener2( emitter.once( "semi colon", [&](string val ){
        if (val == "5;")
            ++counter;
    } ) );
    
    stringstream s;
    s << "5;";
    s << "3\n";
    
    typedef brute_lexer< istream, emitter_type > lexer_type;
    lexer_type lexer;
    lexer.delimiters()['\n'] = "new line";
    lexer.delimiters()[';'] = "semi colon";
    lexer.split( s, emitter );

    ASSERT( counter == 2 );

    cout << "check_lexer passed " << endl;
}
