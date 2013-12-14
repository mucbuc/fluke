#ifndef CORE_FWD_INCLUDE_GUARD
#define CORE_FWD_INCLUDE_GUARD

#include <functional>
#include <string>

namespace core
{
    namespace events
    {
        template<typename = std::string, typename U = std::function<void()> >
		class Emitter;
    }
    
}	//core

#endif
