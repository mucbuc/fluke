namespace om636
{
	namespace fluke
	{
        /////////////////////////////////////////////////////////////////////////////////////////////
	    // split
		/////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        void
        split(
                 T & input,
                 U delimiter_predicate,
                 std::function<void(typename T::char_type,
                                    typename V::const_iterator,
                                    typename V::const_iterator)> analyzer,
                 V & buffer)
        {
			typedef typename T::char_type char_type;
			
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
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // split
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        void
        split(
                 T & input,
                 U delimiter_predicate,
                 std::function<void(typename T::char_type,
                                    typename std::vector<typename T::char_type>::const_iterator,
                                    typename std::vector<typename T::char_type>::const_iterator)> analyzer)
        {
            std::vector< typename T::char_type > buffer;
            split(input, delimiter_predicate, analyzer, buffer);
        }

	}	// fluke
}	// om636 
