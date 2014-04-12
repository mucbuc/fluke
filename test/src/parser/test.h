#include <src/lexer.h>
#include <lib/ohm/src/quemitter.h>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

void check_tokenize()
{
    using namespace om636;
	using namespace std;
    using namespace lexer;
    
	typedef map< char, string > map_type; 
    typedef control::Quemitter< string, function<void( string )> > emitter_type;

    unsigned counter;
    stringstream s;
    emitter_type emitter;
    map_type map;

    auto listener( emitter.once( "new line", [&](string val){
        if (val == "3\n")
        {
            ++counter;
        }
    } ) );
    
    auto listener2( emitter.once( "semi colon", [&](string val ){
        if (val == "5;")
        {
            ++counter;
        }
    } ) );
    
    map['\n'] = "new line";
    map[';'] = "semi colon";
    
    s << "5;";
    s << "3\n";
    
    lexer::tokenize( s, emitter, map );

    ASSERT( counter == 2 );
    
    cout << "check_tokenize passed " << endl;
}
