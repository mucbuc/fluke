#ifndef DEFAULT_SUBJECT_H_HYJ7766FHF65
#define DEFAULT_SUBJECT_H_HYJ7766FHF65

namespace om636
{
    namespace default_subject
    {
        template<class T>
        struct traits
        {
            typedef typename T::value_type value_type;
        };
        
        template<class T, template<class> class U>
        struct traits< context< T, U > >
        {
            typedef T value_type;
        };

        template<class T>
        struct policy
        {
            typedef T context_type;
            typedef typename traits<context_type>::value_type value_type;
            
            void on_swap( const context_type &, const context_type & );
            
            template<class V>
            static value_type on_init( V & );
            
            template<class V, class W>
            static value_type on_init( V &, const W & );
            
            template<class V>
            static V to_value( const context_type & );
            
            template<class U>
            static U & on_write( U &, const context_type & );
            
            template<class U>
            static U & on_read( U &, context_type & );
        };

        namespace Private
        {
            template<class>
            struct stream_in;
            
            template<class>
            struct stream_out;
        }   
    }   //  default_subject
}   // om636

#include "default_subject.hxx"

#endif // DEFAULT_SUBJECT_H_HYJ7766FHF65