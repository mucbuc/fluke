namespace om636
{
	namespace lexer
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
	    // tokenize<T, U, V>
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U, class V>
		void tokenize(T & stream, U & analyzer, const V & event_map ) 
		{
	    	typedef typename T::char_type char_type;
	    	typedef typename U::callback_type::argument_type value_type;

	    	char_type front;
	    	value_type value;

	    	while (stream.get(front))
	    	{
	    		value += front;

	    		auto p( event_map.find(front) );
	    		if (p != event_map.end())
	    		{
	    			analyzer.emit( p->second, value );
	    			value.clear(); 
	    		}
	    	}
	    }
	}	// lexer
}	// om636
