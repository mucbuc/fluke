namespace core
{
	namespace events
	{
		
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		Emitter<T, U>::Agent::Agent( callback_type callback )
		: m_dead( 0 )
		, m_callback( callback )
		{}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		void Emitter<T, U>::Agent::invoke()
		{
			assert( !is_dead() );
			m_callback();
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
        template<typename V>
        void Emitter<T, U>::Agent::invoke( V v )
		{
			assert( !is_dead() );
			m_callback( v );
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		template<typename V, typename W>
        void Emitter<T, U>::Agent::invoke( V v, W w)
		{
			assert( !is_dead() );
			m_callback( v, w );
		}
		
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		void Emitter<T, U>::Agent::kill()
		{
			m_dead = 1;
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		bool Emitter<T, U>::Agent::is_dead()
		{
			return m_dead;
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
        Emitter<T, U>::Listener::Listener( pointer_type agent )
		: m_agent( agent )
		{}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
        Emitter<T, U>::Listener::~Listener()
		{
            // this is the only listener, the other owner is the batch
            if (m_agent.use_count() == 2)
                m_agent->kill();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
        void Emitter<T, U>::Listener::remove()
        {
            m_agent->kill();
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		auto Emitter<T, U>::on( event_type e, callback_type c ) -> Listener
		{
            pointer_type agent( new Agent( c ) );
            m_repeat_add[e].insert( agent );
			return Listener( agent );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		auto Emitter<T, U>::once( event_type e, callback_type c ) -> Listener
		{
            pointer_type agent( new Agent( c ) );
            m_once_add[e].insert( agent );
			return Listener( agent );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		void Emitter<T, U>::removeListeners( event_type e )
		{
            kill_all( m_once[e] );
            kill_all( m_once_add[e] );
            kill_all( m_repeat[e] );
            kill_all( m_repeat_add[e] );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		void Emitter<T, U>::removeAllListeners()
		{
            kill_all( m_once );
            kill_all( m_once_add );
            kill_all( m_repeat );
            kill_all( m_repeat_add );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		void Emitter<T, U>::emit( event_type e)
		{
            merge_batches();
            const batch_type & batches( copy_batches( e ) );
            process( batches );
            m_once.clear();
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		template<class V>
		void Emitter<T, U>::emit( event_type e, V arg)
		{
            merge_batches();
            const batch_type & batches( copy_batches( e ) );
            process( batches, arg );
            m_once.clear();
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
		template<typename V, typename W>
		void Emitter<T, U>::emit( event_type e, V first_arg, W second_arg )
		{
            merge_batches();
            const batch_type & batches( copy_batches( e ) );
            process( batches, first_arg, second_arg );
            m_once.clear();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
        void Emitter<T, U>::process( const batch_type & batch )
        {
            for_each( batch.begin(), batch.end(), [](pointer_type p) {
                if (!p->is_dead())
                    p->invoke();
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
        template<typename V>
        void Emitter<T, U>::process( const batch_type & batch, V v )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                    p->invoke(v);
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
        template<typename V, typename W>
        void Emitter<T, U>::process( const batch_type & batch, V v, W w )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                    p->invoke(v, w);
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
        auto Emitter<T, U>::copy_batches(event_type e) -> batch_type
        {
            batch_type copy( m_once[e] );
            const batch_type & repeaters( m_repeat[ e ] );
            copy.insert( repeaters.begin(), repeaters.end() );
            return copy;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
        void Emitter<T, U>::merge_batches()
        {
            merge_maps( m_repeat, m_repeat_add );
            merge_maps( m_once, m_once_add );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename U>
        void Emitter<T, U>::merge_maps( map_type & dst, map_type & src )
        {
            for_each( src.begin(), src.end(), [&](typename map_type::value_type & v) {
                dst[v.first].insert( v.second.begin(), v.second.end() );
            } );
            src.clear();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename U>
        void Emitter<T, U>::kill_all(batch_type & batch)
        {
            for_each( batch.begin(), batch.end(), [](pointer_type p) {
                p->kill();
            } );
            batch.clear();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename U>
        void Emitter<T, U>::kill_all(map_type & map)
        {
            for_each( map.begin(), map.end(), [](typename map_type::value_type & p) {
                kill_all( p.second );
            } );
            map.clear();
        }
        
    } 	// events
}	// core