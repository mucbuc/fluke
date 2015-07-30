#include <iostream>
#include <tuple>
#include <string>

#include "test.h"

#include <lib/traverse/interface.h>

struct dummy 
{
	template<class T> 
	void operator()( const T & e ) const
	{
		std::cout << e << " ";
	}
};

int main(int argc, const char * argv[])
{
	using namespace std;
	using namespace om636;

	tuple< int, string > t( 5, "hello" ); 

	traverse::elements( t, dummy() ); 

	cout << endl;
	return 0;
}