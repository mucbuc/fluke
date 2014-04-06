#include <cassert>
#define ASSERT( pred ) assert( pred )

#include <fluke/src/lexer.h>
#include <fluke/ohm/src/quemitter.h>
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


    stringstream s;
    emitter_type emitter;
    map_type map;

    auto listener( emitter.once( "new line", [](string val){
        cout << "new line" << val << endl;
    } ) );
    
    auto listener2( emitter.once( "semi colon", [](string val ){
        cout << "semi colon" << val << endl;
    } ) );
    
    map['\n'] = "new line";
    map[';'] = "semi colon";
    
    s << "5;";
    s << "3\n";
    
    
    lexer::tokenize( s, emitter, map );

    cout << "check_tokenize passed " << endl;
}
