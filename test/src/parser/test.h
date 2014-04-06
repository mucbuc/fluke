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

    auto listener( emitter.once( "new line", [](string){
        cout << "new line" << endl;
    } ) );
    
    
    map['\n'] = "new line";
    
    
    
    s << "3\n";
    
    lexer::tokenize( s, emitter, map );
    
    
    cout << "check_tokenize passed " << endl;
}
