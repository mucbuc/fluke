namespace om636
{
	/////////////////////////////////////////////////////////////////////////////////////////////
    // token<T>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	token<T>::token(token_id type, value_type value)
    : m_type( type )
    , m_name( value )
	{}
    
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
	auto token<T>::name() const -> const value_type &
	{	return m_name;	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	auto token<T>::type() const -> token_id
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
	template<class I>
	I token<T>::make_token( I begin, I end, std::function<void(token)> cb )
	{

		while (begin != end && isspace(* begin))
			++begin;
		
		if (begin == end) 
			return begin;
		
		value_type name;
		token_id type( terminator );
		
		enum { period = '.', semicolon = ';' };
		if (isalpha(* begin))
		{
			type = variable;                          // every alphabetic is a variable ??? 
			do
				name.push_back(* begin);
			while (++begin != end && isalpha(* begin) ); // this seems arbitrary, what about the variables names including numbers
		}
		else if (isdigit(* begin) || * begin == period)
		{	
		#ifdef NDEBUG
			bool _period( * begin == period );
		#endif 
			
			type = number;
			
			do
			{		
			#ifdef NDEBUG	
				ASSERT( !_period || * begin != period );
				_period = * begin == period;
			#endif 	
				
				name.push_back(* begin);
			}
			while (++begin != end && (isdigit(* begin) || * begin == period));
		}
		else if (* begin != semicolon)
		{ 
			type = _operator;
			name.push_back(* begin);
			++begin;
		}
        cb( token( type, name ) );
		return begin;
	}
} // om636
