namespace om636
{
#pragma mark basic_subject
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	// basic_subject
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    basic_subject<T>::basic_subject()
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    basic_subject<T>::~basic_subject()
    {
        std::for_each( m_observers.begin(), m_observers.end(), [=](observer_type i) {
            i->detach( this );
        } );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void basic_subject<T>::attach( const observer_type & o )
    {
        m_observers.push_back( o );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void basic_subject<T>::detach( const observer_type & o )
    {
        m_observers.erase( find( m_observers.begin(), m_observers.end(), o ) );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void basic_subject<T>::on_swap( context_type & lhs, context_type & rhs )
    {
        std::for_each( m_observers.begin(), m_observers.end(), [&](observer_type i) {
            i->on_swap( lhs, rhs );
        } );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class V>
    typename basic_subject<T>::value_type basic_subject<T>::on_init(V & v)
    {
        return value_type();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class V, class W>
    typename basic_subject<T>::value_type basic_subject<T>::on_init(V &, const W & v)
    {
        return value_type(v);
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class V>
    V basic_subject<T>::to_value(const context_type & c)
    {
        return V( c.value_ref() );
    }
    
#pragma mark safe_subject
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    // safe_subject
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    safe_subject<T>::safe_subject()
    : m_locked( 0 )
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    safe_subject<T>::~safe_subject()
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void safe_subject<T>::attach(const observer_type & o)
    {
        if (m_locked)
            throw locked();
        base_type::attach( o );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void safe_subject<T>::detach(const observer_type & o)
    {
        if (m_locked)
            throw locked();
        base_type::detach( o );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void safe_subject<T>::on_swap(context_type & lhs, context_type & rhs)
    {
        struct guard
        {
            guard( bool & locked )
            : m_locked( locked )
            { m_locked = 1; }
            
            ~guard()
            { m_locked = 0; }
            
            bool & m_locked;
        };
        
        if (m_locked)
            throw locked();
        
        guard g( m_locked );
        base_type::on_swap( lhs, rhs );
    }
    
#pragma mark peristent_subject 
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::persistent_subject()
    : base_type()
    , m_name()
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::persistent_subject( const char * path )
    : base_type()
    , m_name( path )
    {
        singleton_type::instance().open( path );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::~persistent_subject()
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class U>
    auto persistent_subject<T>::on_init(U & lhs, const std::string & name)->value_type
    {
        using std::string;
        using std::stringstream;
        
        base_type::on_init( lhs );
        
        string & value ( singleton_type::instance().storage()[ lhs.name() = name ] );
        
        stringstream strm( value );
        
        value_type result;
        strm >> result;
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent_subject<T>::on_swap(context_type & lhs, context_type & rhs)
    {
        using namespace std;
        
        string & value ( singleton_type::instance().storage()[ name() ] );
        
        stringstream strm2;
        strm2 << rhs.value_ref();
        value = strm2.str();
        
        base_type::on_swap( lhs, rhs );
    }
        
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    std::string & persistent_subject<T>::name()
    {
        return m_name;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    std::string persistent_subject<T>::name() const
    {
        return m_name;
    }
    
#pragma mark state_subject
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	// state_subject<N>
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    state_subject<T>::~state_subject()
    {}
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
	bool state_subject<T>::on_equal( const context_type & lhs, const context_type & rhs ) const
	{
        return state(lhs)->on_equal(lhs, rhs);
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	int state_subject<T>::on_cmp( const context_type & lhs, const context_type & rhs ) const
	{	return state(lhs)->on_cmp( lhs, rhs ); }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	int state_subject<T>::on_sign( const context_type & n ) const
	{	return state(n)->on_sign( n ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	bool state_subject<T>::on_swap( context_type & lhs, context_type & rhs ) const
	{
        return state(lhs)->on_swap( lhs, rhs );
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void state_subject<T>::on_add( context_type & lhs, const context_type & rhs ) const
	{
        state(lhs)->on_add( lhs, rhs );
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void state_subject<T>::on_subtract( context_type & lhs, const context_type & rhs ) const
	{
        state(lhs)->on_subtract( lhs, rhs );
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void state_subject<T>::on_mult( context_type & lhs, const context_type & rhs ) const
	{
        state(lhs)->on_mult( lhs, rhs );
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void state_subject<T>::on_divide( context_type & lhs, const context_type & rhs ) const
	{
        state(lhs)->on_divide( lhs, rhs );
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void state_subject<T>::on_remainder( context_type & lhs, const context_type & rhs ) const
	{
        state(lhs)->on_remainder( lhs, rhs );
    }
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void state_subject<T>::on_inc( context_type & n ) const
	{
        state(n)->on_inc( n );
    }
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void state_subject<T>::on_dec( context_type & n ) const
	{
        state(n)->on_dec( n );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void state_subject<T>::on_invert( context_type & n ) const
	{
        state(n)->on_invert( n );
    }
    
}	// om636