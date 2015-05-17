namespace om636
{
    namespace fluke
    {
        /////////////////////////////////////////////////////////////////////////////////////////////
        // split
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        void
        split(
                 T & input,
                 std::function<bool(typename T::char_type)> delimiter_predicate,
                 std::function<void(typename T::char_type,
                                    typename U::const_iterator,
                                    typename U::const_iterator)> analyzer,
                 U & buffer)
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
        template<class T>
        void
        split(
                 T & input,
                 std::function<bool(typename T::char_type)> delimiter_predicate,
                 std::function<void(typename T::char_type,
                                    typename std::vector<typename T::char_type>::const_iterator,
                                    typename std::vector<typename T::char_type>::const_iterator)> analyzer)
        {
            std::vector< typename T::char_type > buffer;
            split(input, delimiter_predicate, analyzer, buffer);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        // split
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        void
        split(
                 T & input,
                 std::function<bool(typename T::char_type)> delimiter_predicate,
                 std::function<void(U)> analyzer,
                 V & buffer)
        {
            typedef typename T::char_type char_type;
            typedef U token_type;

            split(input, delimiter_predicate, [& analyzer](char_type d, typename V::const_iterator begin, typename V::const_iterator end) {
                while (begin != end) {
                    begin = token_type::make_token(begin, end, analyzer );
                }
            });
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // split
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        void
        split(
                 T & input,
                 std::function<bool(typename T::char_type)> delimiter_predicate,
                 std::function<void(U)> analyzer)
        {
            typedef typename T::char_type char_type;
            std::vector< typename T::char_type > buffer;

            split( input, delimiter_predicate, analyzer, buffer );
        }

    }   // fluke
}   // om636 
