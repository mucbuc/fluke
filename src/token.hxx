namespace om636
{
	/////////////////////////////////////////////////////////////////////////////////////////////
    // token<T>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	token<T>::token()
    : m_type( terminator )
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	token<T>::token( const token & t)
    : m_name( t.m_name )
    , m_type( t.m_type ) 
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	token<T> & token<T>::operator=(token t)
	{	
		swap( t );
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void token<T>::swap(token & t)
	{	
		token_id temp( t.m_type );
		t.m_type = m_type;
		m_type = temp;
		
		m_name.swap( t.m_name );
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	auto token<T>::name() const->const value_type &
	{	return m_name;	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	auto token<T>::type() const->token_id
	{	return m_type;	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	template<class U>
	void token<T>::to_value(U & v) const
	{
		using std::stringstream;
		stringstream s( m_name, stringstream::in );
		s >> v;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	token<T>::operator token<T>::tester*() const
	{	
		static tester test;
		return m_type == terminator ? 0 : & test;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	bool token<T>::operator!() const
	{	return m_type == terminator;	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void swap(token<T> & lhs, token<T> & rhs)
	{	lhs.swap( rhs );	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	template<class U>
	token<T>::token( U & in, char & _front )
	{
		while (isspace(_front))
			if (!in.get(_front))
			{
				m_type = terminator;
				return;		
			}
	
		enum { period = '.', semicolon = ';' };
		if (isalpha(_front))
		{
			m_type = variable;                          // every alphabetic is a variable ??? 
			do
				m_name.push_back(_front);
			while (in.get(_front) && isalpha(_front) ); // this seems arbitrary, what about the variables names including numbers
		}
		else if (isdigit(_front) || _front == period)
		{	
		#ifdef NDEBUG
			bool _period( _front == period );
		#endif 
			
			m_type = number;
			
			do
			{		
			#ifdef NDEBUG	
				ASSERT( !_period || _front != period );
				_period = _front == period;
			#endif 	
				
				m_name.push_back(_front);
				in.get(_front);
			}
			while (isdigit(_front) || _front == period);
		}
		else if (_front == semicolon)
			m_type = terminator;
		else
		{ 
			m_type = _operator;
			m_name.push_back(_front);
			in.get(_front);
		}
	}
} // om636
