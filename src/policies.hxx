namespace om636
{
	namespace parser_policies
	{	
		/////////////////////////////////////////////////////////////////////////////////////////////
		// push_observer<T> 
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		void push_observer< T, U >::on_token( context_type & context, const token_type & token )
		{
			context_type::tokens( context ).push_back( token );
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////
		// push_policy<T>
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		template<class V>
		auto push_policy<T, U>::on_init(V &)->value_type
		{ 
			return value_type( container_type(), this ); 
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		template<class V, class W>
		auto push_policy<T, U>::on_init(V &, const W &)->value_type
		{ 
			return value_type( container_type(), this ); 
		}
			
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		template<class V>
		V push_policy<T, U>::to_value(const context_type &)
		{   
			return V(); 
		}
			
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		auto push_policy<T, U>::state(context_type & context)->observer_type * &
		{   return std::get<1>(context.value_ref());    }
			
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		auto push_policy<T, U>::state(const context_type & context)->observer_type *
		{   return std::get<1>(context.value_ref());    }
			
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		auto push_policy<T, U>::tokens(context_type & context)->container_type &
		{   return std::get<0>(context.value_ref());    }
			
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		auto push_policy<T, U>::tokens(const context_type & context)->	const container_type &
		{   return std::get<0>(context.value_ref());    }
	}
}