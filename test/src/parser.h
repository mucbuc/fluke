#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include <lib/ohm/src/quemitter.h>

#include <lib/fluke/src/lexer.h>
#include <lib/fluke/src/parser.h>


void check_parser()
{
    using namespace std;
    using namespace om636;
    using namespace fluke;
    
    typedef control::Quemitter< string, function<void( string )> > emitter_type;
    typedef brute_parser< emitter_type, int > parser_type;
    typedef brute_lexer< istream, emitter_type > lexer_type;
    
    emitter_type emitter;
    int i;
    parser_type p( i );

    p.interpret( emitter );

    unsigned passed( 0 ); 
    
    auto listener_word( emitter.on( "word", [&](const string & value){
        if (value == "hello")
            ++passed;
    } ) );

    auto listener_number( emitter.on( "number", [&](const string & value){
        if (value == "3.1416")
            ++passed;
    } ) );
    
    auto listener_operator( emitter.on( "operator", [&](const string & value){
        if (value == "+=")
            ++passed;
    } ) );
    
    stringstream s;
    s << "hello 3.1416 += ";
    
    lexer_type lexer( { " " } );
    lexer.split( s, emitter );
    
    ASSERT( passed == 3 );

    FOOTER;
}
