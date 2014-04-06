namespace om636
{
	using std::string;
	
	/////////////////////////////////////////////////////////////////////////////////////////////
    // lexer<T, U>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	lexer<T, U>::lexer(stream_type & _s)
    : m_stream( _s )
    , m_token()
    , m_count(0)
    , m_front(0)
    {
		bool result( m_stream.get(m_front) );
		ASSERT(result);
		next();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	const size_t & lexer<T, U>::count() const
	{	return m_count;	}
		
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	auto lexer<T, U>::current() const -> const token_type & 
	{	return m_token;	}
		
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	auto lexer<T, U>::next() -> const token_type &
	{
        m_count++;
        return m_token = token_type(m_stream, m_front);
	}
    
}	// om636
