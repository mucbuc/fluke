namespace om636
{
	namespace fluke
	{
			
		/////////////////////////////////////////////////////////////////////////////////////////////
	    // brute_lexer<T, U, V>
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U, class V>
		brute_lexer<T, U, V>::brute_lexer(const map_type & delimiters)
		: m_delimiters( delimiters )
		{}
		
		/////////////////////////////////////////////////////////////////////////////////////////////
	    template<class T, class U, class V>
		void brute_lexer<T, U, V>::split( stream_type & stream, analyzer_type & analyzer ) const
		{
	    	string_type value;
	    	string_type::value_type front;
	    	
	    	while (stream.get(front))
	    	{
	    		value += front;

	    		auto p( m_delimiters.find(front) );
	    		if (p != m_delimiters.end())
	    		{
	    			analyzer.emit( p->second, value );
	    			value.clear(); 
	    		}
	    	}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
	    template<class T, class U, class V>
		auto brute_lexer<T, U, V>::delimiters() -> map_type & 
		{
			return m_delimiters;
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////
	    template<class T, class U, class V>
		auto brute_lexer<T, U, V>::delimiters() const -> const map_type & 
		{
			return m_delimiters;
		}
	}	// fluke
}	// om636 
