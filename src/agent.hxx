namespace om636
{
	namespace control
	{
		
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		Agent<T>::Agent( callback_type callback )
		: m_dead( 0 )
		, m_callback( callback )
		{}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Agent<T>::invoke()
		{
			assert( !is_dead() );
			m_callback();
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V>
        void Agent<T>::invoke( V v )
		{
			assert( !is_dead() );
			m_callback( v );
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<typename V, typename W>
        void Agent<T>::invoke( V v, W w)
		{
			assert( !is_dead() );
			m_callback( v, w );
		}
		
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Agent<T>::kill()
		{
			m_dead = 1;
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		bool Agent<T>::is_dead()
		{
			return m_dead;
		}

	}	//control
}	// om636
