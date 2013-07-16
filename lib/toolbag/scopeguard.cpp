#include "scopeguard.h"

namespace toolbag
{

	/////////////////////////////////////////////////////////////////////////////////////////////
    // scope_guard_base 
	/////////////////////////////////////////////////////////////////////////////////////////////
	scope_guard_base::scope_guard_base()
	: m_dismissed( false )
	{}
		
	/////////////////////////////////////////////////////////////////////////////////////////////
	scope_guard_base::scope_guard_base( const scope_guard_base & c)
	: m_dismissed( c.m_dismissed )
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	scope_guard_base::~scope_guard_base()
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	void scope_guard_base::dismiss() const throw()
	{	m_dismissed = true; 	}
	 
	/////////////////////////////////////////////////////////////////////////////////////////////
	bool scope_guard_base::is_dismissed()
	{	return m_dismissed;	}
}	// toolbag 
