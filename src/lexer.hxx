namespace om636
{
	namespace fluke
	{
        /////////////////////////////////////////////////////////////////////////////////////////////
	    // brute_lexer<T, U, V>
		/////////////////////////////////////////////////////////////////////////////////////////////
//		template<class T, class U>
//        std::vector<typename T::char_type> splitAll(T & input, U delimiters_begin, U delimiters_end, std::function<void(T::char_type, typename std::vector<typename T::char_type>::iterator, typename std::vector<typename T::char_type>::iterator)>)
//                                                                                                                        
//                                                                                                        //                std::vector<typename T::char_type>analyzer)
//		{
        
        // std::find(delimiters_begin, delimiters_end, front) != delimiters_end)
        template<class T, class U, class V>
        void
        splitAll(
                 T & input,
                 U delimiter_predicate,
                 std::function<void(typename T::char_type,
                                    typename V::const_iterator,
                                    typename V::const_iterator)> analyzer,
                 V & buffer)
        {
			typedef typename T::char_type char_type;
			
            buffer.clear();
			char_type front;
	    	while (input.get(front))
	    	{
	    		if (delimiter_predicate(front))
	   			{
	   				analyzer( front, buffer.begin(), buffer.end() );
	   				buffer.clear();
	   			}
	   			else 
	    			buffer.push_back( front );
	    	}

	    }
        
        
        
        template<class T, class U>
        void
        splitAll(
                 T & input,
                 U delimiter_predicate,
                 std::function<void(typename T::char_type,
                                    typename std::vector<typename T::char_type>::const_iterator,
                                    typename std::vector<typename T::char_type>::const_iterator)> analyzer)
        {
            std::vector< typename T::char_type > buffer;
            splitAll(input, delimiter_predicate, analyzer, buffer);
        }

	}	// fluke
}	// om636 
