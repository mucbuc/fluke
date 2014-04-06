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
	token<T>::token( U & in )
	{
		char temp;
		bool result( in.get(temp) );
		ASSERT(result);	// should probably throw here

		read_next( in, temp );
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	template<class U>
	token<T>::token( U & in, char & front )
	{
		read_next( in, front );
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	template<class U>
	void token<T>::read_next( U & in, char & front )
	{
		while (isspace(front))
			if (!in.get(front))
			{
				m_type = terminator;
				return;		
			}
	
		enum { period = '.', semicolon = ';' };
		if (isalpha(front))
		{
			m_type = variable;                          // every alphabetic is a variable ??? 
			do
				m_name.push_back(front);
			while (in.get(front) && isalpha(front) ); // this seems arbitrary, what about the variables names including numbers
		}
		else if (isdigit(front) || front == period)
		{	
		#ifdef NDEBUG
			bool _period( front == period );
		#endif 
			
			m_type = number;
			
			do
			{		
			#ifdef NDEBUG	
				ASSERT( !_period || front != period );
				_period = front == period;
			#endif 	
				
				m_name.push_back(front);
				in.get(front);
			}
			while (isdigit(front) || front == period);
		}
		else if (front == semicolon)
			m_type = terminator;
		else
		{ 
			m_type = _operator;
			m_name.push_back(front);
			in.get(front);
		}
	}

} // om636
