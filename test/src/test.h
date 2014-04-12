#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include <lib/ohm/src/quemitter.h>

#include <src/lexer.h>
#include <src/parser.h>

#include "debug.h"

void check_parser()
{
    using namespace std;
    using namespace om636;
    using namespace fluke;
    
    typedef control::Quemitter< string, function<void( string )> > emitter_type;
    typedef brute_parser< emitter_type, int > parser_type;

    emitter_type emitter;
    int i;
    parser_type p( i );

    p.interpret( emitter );
    
    emitter.emit( "token", "hello" );
    
    cout << "check_parser passed " << endl;
}

void check_lexer()
{
    using namespace std;
    using namespace om636;
    using namespace fluke;
    
    typedef control::Quemitter< char, function<void( string )> > emitter_type;
    typedef brute_lexer< istream, emitter_type > lexer_type;
    
    emitter_type emitter;
    unsigned counter;

    auto listener( emitter.once( '\n', [&](string val){
        if (val == "3")
            ++counter;
    } ) );
    
    auto listener2( emitter.once( ';', [&](string val ){
        if (val == "5")
            ++counter;
    } ) );
    
    stringstream s;
    s << "5;";
    s << "3\n";
    
    lexer_type lexer;
    lexer.delimiters().insert( ';' );
    lexer.split( s, emitter );

    ASSERT( counter == 2 );

    cout << "check_lexer passed " << endl;
}