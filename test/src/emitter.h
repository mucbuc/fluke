#include <cassert>
#include <iostream>
#include <vector>
#include <ohm/src/emitter.h>

/////////////////////////////////////////////////////////////////
void check_modify_while_traversal()
{
    using namespace std;
    typedef om636::control::Emitter<> emitter_type;

    static emitter_type emitter;
    static unsigned trap( 0 );
    static string event( "load" );
    struct tester
    {
        static void trigger_trap()
        {
            ++trap;
        }
        
        static void remove()
        {
            ++trap;
            emitter.removeListeners( event );
        }
        
        static void removeAll()
        {
            ++trap;
            emitter.removeAllListeners();
        }
    };
    
    vector< typename emitter_type::listener_type > listeners;

    // test remove while traverse
    listeners.push_back( emitter.on( event, tester::remove ) );
    listeners.push_back( emitter.on( event, tester::remove ) );
    listeners.push_back( emitter.once( event, tester::remove ) );
    emitter.emit( event );
    assert( trap == 1 );
    
    // test removeAll while traverse
    listeners.push_back( emitter.on( event, tester::removeAll ) );
    listeners.push_back( emitter.on( event, tester::removeAll ) );
    listeners.push_back( emitter.once( event, tester::removeAll ) );
    emitter.emit( event );
    assert( trap == 2 );
    
    // test insert while traverse
    listeners.push_back( emitter.once( event, [&](){
        listeners.push_back( emitter.on( event, tester::trigger_trap ) );
        listeners.push_back( emitter.once( event, tester::trigger_trap ) );
    }));
    emitter.emit( event );
    assert( trap == 2 );
    
    emitter.emit( event );
    assert( trap == 4 );

    emitter.emit( event );
    assert( trap == 5 );
    
    cout << __FUNCTION__ << " passed" << endl;
}

/////////////////////////////////////////////////////////////////
void check_dispatch_logic()
{
    static unsigned trap( 0 );
    struct tester
    {
        static void trigger_trap()
        {
            ++trap;
        }
    };
    
    using namespace std;
    typedef om636::control::Emitter<> emitter_type;
    
    emitter_type emitter;
    vector< typename emitter_type::listener_type > listeners;
    string event( "calculate answer to L.U. and E." );
    
    trap = 0;
    
    // check dead agent
    emitter.once( event, tester::trigger_trap );
    emitter.emit( event );
    assert( trap == 0 );
    
    // check once
    listeners.push_back( emitter.once( event, tester::trigger_trap ) );
    emitter.emit( event );
    assert( trap == 1 );
    emitter.emit( event );
    assert( trap == 1 );
    
    // check on
    listeners.push_back( emitter.on( event, tester::trigger_trap ) );
    emitter.emit( event );
    assert( trap == 2 );
    emitter.emit( event );
    assert( trap == 3 );
    
    // check duplicate
    listeners.push_back( emitter.on( event, tester::trigger_trap ) );
    emitter.emit( event );
    assert( trap == 5 );
    
    cout << __FUNCTION__ << " passed" << endl;
}

/////////////////////////////////////////////////////////////////
void check_agent_life_time()
{
    struct dummy_callback
    {
        dummy_callback()
        {
            ++instance_counter();
        }
        
        dummy_callback(const dummy_callback &)
        : dummy_callback()
        {}
        
        ~dummy_callback()
        {
            --instance_counter();
        }
        
        dummy_callback & operator=(const dummy_callback &) = default;
        
        static size_t & instance_counter()
        {
            static size_t counter( 0 );
            return counter;
        }
    };
    
    using namespace std;
    typedef om636::control::Emitter< string, dummy_callback > emitter_type;
    
    static string event( "init" );
    emitter_type emitter;
    
    if (1)
    {
        auto listener( emitter.on( event, dummy_callback() ) );
        emitter.removeListeners( event );
        
        // this reference is owned by the listener
        assert( dummy_callback::instance_counter() == 1 );
    }
    assert( !dummy_callback::instance_counter() );
    
    if (1)
    {
        auto listener( emitter.on( event, dummy_callback() ) );
        emitter.removeAllListeners();
        
        // this reference is owned by the listener
        assert( dummy_callback::instance_counter() == 1 );
    }
    assert( !dummy_callback::instance_counter() );

    if (1)
    {
        emitter_type::listener_type listener;
        if(1)
        {
            auto temp( emitter.on( event, dummy_callback() ) );
            assert( dummy_callback::instance_counter() == 1 );
        
            listener = temp;
            
            assert( dummy_callback::instance_counter() == 1 );
        }
        
        // this reference is owned by the emitter
        assert( dummy_callback::instance_counter() == 1 );
    }
    
    emitter.removeListeners( event );
    assert( !dummy_callback::instance_counter() );
    
    cout << __FUNCTION__ << " passed" << endl;
}