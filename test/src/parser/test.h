#include <cassert>
#define ASSERT( pred ) assert( pred )

#include <om636/src/parser/token.h>
#include <om636/src/parser/lexer.h>
#include <string>
#include <iostream>
#include <sstream>
#include <string>

void check_token_number()
{
    using namespace om636;
	using namespace std;
	
	typedef token< string > token_type;
    stringstream s;

    s << "3\n";
    s << "4\t";
    s << "5 ";
    s << "3.13 ";

    token_type a( s );
    ASSERT( a.type() == token_type::number && a.name() == "3" );
    
    token_type b( s );
    ASSERT( b.type() == token_type::number && b.name() == "4" );
    
    token_type c( s );
    ASSERT( c.type() == token_type::number && c.name() == "5" );    
    
    token_type d( s );
    ASSERT( d.type() == token_type::number && d.name() == "3.13" );
    
    cout << "check_token_number passed " << endl;
}

void check_terminator()
{
 	using namespace om636; 
	using namespace std;
	
	typedef token< string > token_type; 
	typedef lexer< token_type, stringstream > lexer_type;

	stringstream s;
	s << ";";
	lexer_type t( s ); 

    auto type( t.current().type() );
	ASSERT( type == token_type::terminator );

	cout << "check terminator passed " << endl;
}
