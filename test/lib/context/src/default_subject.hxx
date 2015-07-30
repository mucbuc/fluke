namespace om636
{
    namespace default_subject
    {
        namespace Private
        {
            template<class T>
            struct stream_out
            {
                stream_out( const stream_out & ) = default;
                
                template<class U>
                U operator()(const U & u) const
                {
                    m_stream << u;
                    return u;
                }
                
                template<class U, class V>
                V operator()(const U & u, const V & v) const
                {
                    m_stream << " " << v;
                    return v;
                }
                
                T m_stream;
            };
        
            template<class T>
            struct stream_in
            {
                stream_in( const stream_in & ) = default;
                
                template<class U>
                U operator()(U & u) const
                {
                    m_stream >> u;
                    return u;
                }
                
                template<class U, class V>
                V operator()(U & u, V & v) const
                {
                    m_stream >> v;
                    return v;
                }
                
                T m_stream;
            };
        }
            
        /////////////////////////////////////////////////////////////////////////////////////////////
        // policy
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V>
        auto policy<T>::on_init( V & ) -> value_type
        {
            return value_type();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V, class W>
        auto policy<T>::on_init( V &, const W & v ) -> value_type
        {
            return value_type(v);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V>
        V policy<T>::to_value( const context_type & c )
        {
            return V( c.value_ref() );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void policy<T>::on_swap( const context_type &, const context_type & )
        {}
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class U>
        U & policy<T>::on_write( U & s, const context_type & c )
        {
            Private::stream_out<U &> op = { s };
            traverse::pairs( c.value_ref(), op );
            return s;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class U>
        U & policy<T>::on_read( U & s, context_type & c )
        {
            Private::stream_in<U &> op = { s };
            traverse::pairs( c.value_ref(), op );
            return s;
        }
    }
}	// om636