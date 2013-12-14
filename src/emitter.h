#ifndef EMITTER_INCLUDE_GUARD
	#define EMITTER_INCLUDE_GUARD

#include <cassert>
#include <map>
#include <memory>
#include <set>

namespace core
{
	namespace events 
	{
		template<typename T, typename U> 
		struct Traits
		{
		    typedef T event_type;
			typedef U callback_type;
		};

		template<typename T, typename U> 
		class Emitter 
		: public Traits< T, U >
		{
			struct Agent;
            typedef std::shared_ptr< Agent > pointer_type;

		public: 

		    typedef Traits< T, U > traits_type;
		    using typename traits_type::event_type;
		    using typename traits_type::callback_type;

            struct Listener
			{
				Listener( pointer_type );
				~Listener();
				Listener( const Listener & ) = default;
                Listener & operator=(const Listener &) = default;
                Listener() = default;
         	    void remove();
                
			private:
		        
				pointer_type m_agent;
			};
            
			Emitter() = default;
			virtual ~Emitter() = default;
            Emitter(const Emitter &) = delete;
            Emitter & operator=(const Emitter &) = delete;
			
			Listener on( event_type, callback_type );
			Listener once( event_type, callback_type );
			
			void removeListeners( event_type );
			void removeAllListeners();

			void emit( event_type );
			
			template<class V> 
			void emit( event_type, V );
			
			template<typename V, typename W> 
			void emit( event_type, V, W );
            
		private:

			struct Agent
			{
				Agent( callback_type );
                
				void invoke();
               
                template<class V>
				void invoke(V);
                
                template<typename V, typename W>
                void invoke(V, W);
                
				void kill();
				bool is_dead();

			private: 
				bool m_dead; 
				callback_type m_callback;
			};

            typedef std::multiset< pointer_type > batch_type;
			typedef std::map< event_type, batch_type > map_type;
			
            static void process( const batch_type & );
            
            template<typename V>
            static void process( const batch_type &, V );
            
            template<typename V, typename W>
            static void process( const batch_type &, V, W );
            
            batch_type copy_batches(event_type);
            void merge_batches();
            
            static void merge_maps(map_type &, map_type &);
            static void kill_all(batch_type &);
            static void kill_all(map_type &);
            
			map_type m_repeat;
            map_type m_repeat_add;
			map_type m_once;
			map_type m_once_add;
		};
	}	//emitter
}	// core

#include "emitter.hxx"

#endif 