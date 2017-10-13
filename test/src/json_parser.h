#include <iostream>
#include <sstream>
#include <string>

#include <lib/fluke/src/lexer.h>

using namespace std;
using namespace om636;
using namespace fluke;

typedef token<std::string> token_type;
typedef vector<char> buffer_type;
typedef typename buffer_type::const_iterator const_iterator;
typedef typename std::string::value_type char_type;

void parse_json()
{
    stringstream json;
    json << R"({ "hello": "joe" })";

    buffered_splitter<token_type>::split(json, [](const char w) -> bool {
         return w == '{' || w == '}' || w == '"' || w == ':';// || w == '[' || w == ']'; }, [](char_type c, const_iterator b, const_iterator e) {
        switch (c) {
        	case '{': 
        		cout << "object open";
        		break;
        	case '}':
				cout << "object close";
        		break;
        	case '"':
        		cout << "double quote";
        		break;
        	case ':':
        		cout << "define as";
        		break;
       //  	case '[':
       //  		cout << "array open";
       //  		break;
       //  	case ']':
    			// cout << "array close";
    			// break;
    	}; 

    	cout << endl; });
}