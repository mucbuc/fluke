namespace om636
{
	namespace fluke
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
	    // brute_lexer<T, U, V>
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U, class V>
		brute_lexer<T, U, V>::brute_lexer(const set_type & delimiters)
		: base_type()
		, m_delimiters( delimiters )
		{}
		
		/////////////////////////////////////////////////////////////////////////////////////////////
	    template<class T, class U, class V>
		void brute_lexer<T, U, V>::split( stream_type & stream, analyzer_type & analyzer ) const
		{
	    	string_type value;
	    	string_type::value_type front;
	    	
	    	while (stream.get(front))
	    	{
	    		if (m_delimiters.find(front) != m_delimiters.end())
	    		{
	    			analyzer.emit( front, value );
	    			value.clear(); 
	    		}
	    		else
	    			value += front;
	    	}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
	    template<class T, class U, class V>
		auto brute_lexer<T, U, V>::delimiters() -> set_type & 
		{
			return m_delimiters;
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////
	    template<class T, class U, class V>
		auto brute_lexer<T, U, V>::delimiters() const -> const set_type & 
		{
			return m_delimiters;
		}
	}	// fluke
}	// om636 
