#include <om636/src/core/assert.h>
#include <iostream>

int main( int argc, char * argv[] )
{
	std::cout << " <om636/src/core/assert.h> ";

	int i = 44;

	ASSERT( i == 44 )( i );
  	return 0;
}
