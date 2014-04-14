#ifndef COMPENETSFWDH__INCLUDE_GUARD__9879878979878
    #define COMPENETSFWDH__INCLUDE_GUARD__9879878979878

//#include <core/corefwd.h>

namespace om636
{
	// context
    template<class> struct empty_subject;
    template<class, template<class> class> class context;//class = empty_subject> class context;
    
	// composite_units
	template<class> class default_unit;
	template<class> class container_unit; 
    
	// compound
	template<class, template<class, class> class, class> class compound;
	
	// range	
	template<int N> class index;
    
    // subjects
    template<class>
    struct basic_subject;
    
    template<class>
    struct safe_subject;
    
    template<class>
    struct persistent_subject;
    
    template<class>
	struct state_subject;

    // observer
    template<class>
    struct observer; 
    
}	// om636 

#endif // __COMPENETSFWDH__INCLUDE_GUARD__9879878979878