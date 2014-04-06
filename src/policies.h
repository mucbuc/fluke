#ifndef POLICIES_H__kszLRt3TVQ7OrvFxqwAjGaSU4MDNhu
#define POLICIES_H__kszLRt3TVQ7OrvFxqwAjGaSU4MDNhu

namespace om636
{
	namespace parser_policies
	{
		
		template<class T, class U>
		struct observer
		{
			// types
			typedef T context_type;
			typedef U token_type;
			
			virtual void on_token( context_type & context, const token_type & token ) = 0; 
		};
		
		template<class T, class U>
		struct push_observer 
		: observer< T, U > 
		{
			// types
			typedef T context_type;
			typedef U token_type;
			typedef observer< context_type, token_type > base_type; 
			
			virtual void on_token( context_type & context, const token_type & token );
		};
		
		template<class T, class U>
		struct push_policy
		: public push_observer< T, U >
		{
			typedef T context_type;
			typedef U token_type;
			typedef observer<context_type, token_type> observer_type;
			typedef typename om636::default_subject::traits<context_type>::value_type container_type;
			typedef std::tuple< container_type, observer_type * > value_type;
			
			template<class V>
			value_type on_init(V &);
			
			template<class V, class W>
			value_type on_init(V &, const W &);
			
			template<class V>
			static V to_value(const context_type &);
			static observer_type * & state(context_type & context);
			static observer_type * state(const context_type & context);
			static container_type & tokens(context_type & context);
			static const container_type & tokens(const context_type & context);
		};

	} 	// parser_policies
}	// om636

#include "policies.hxx"

#endif // __POLICIES_H__kszLRt3TVQ7OrvFxqwAjGaSU4MDNhu