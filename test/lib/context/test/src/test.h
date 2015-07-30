#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

#include <lib/context/src/interface.h>
#include <lib/context/src/forward_policy.h>
#include "base.h"

namespace
{
	template<class T>
	void run_math_test()
	{
		using namespace std;
		using namespace om636;
		
		typedef context< int, forward_policy > number_type;
        tools::tester< number_type >::test_number();
        FOOTER;
    }
}
