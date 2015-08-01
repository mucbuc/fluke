namespace om636
{
    namespace fluke
    {
        /////////////////////////////////////////////////////////////////////////////////////////////
        // split
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class U, class V>
        void
        splitter<T>::split(
                 U & input,
                 std::function<bool(char_type)> delimiter_predicate,
                 std::function<void(char_type,
                                    typename V::const_iterator,
                                    typename V::const_iterator)> analyzer,
                 V & buffer)
        {
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
        template<class U>
        void
        splitter<T>::split(
                 U & input,
                 std::function<bool(char_type)> delimiter_predicate,
                 std::function<void(char_type,
                                    typename std::vector<char_type>::const_iterator,
                                    typename std::vector<char_type>::const_iterator)> analyzer)
        {
            std::vector< char_type > buffer;
            split(input, delimiter_predicate, analyzer, buffer);
        }

        template<class T>
        template<class U, class V>
        void
        splitter<T>::split(
                 U & input,
                 std::function<bool(char_type)> delimiter_predicate,
                 std::function<void(token_type)> analyzer,
                 V & buffer)
        {
            split(input, delimiter_predicate, [& analyzer](char_type d, typename V::const_iterator begin, typename V::const_iterator end) {
                while (begin != end) {
                    begin = token_type::make_token(begin, end, analyzer );
                }
            });
        }

        template<class T>
        template<class U>
        void
        splitter<T>::split(
                 U & input,
                 std::function<bool(char_type)> delimiter_predicate,
                 std::function<void(token_type)> analyzer)
        {
            std::vector< char_type > buffer;

            split( input, delimiter_predicate, analyzer, buffer );
        }


    }   // fluke
}   // om636 
