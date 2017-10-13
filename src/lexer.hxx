namespace om636 {
namespace fluke {
    /////////////////////////////////////////////////////////////////////////////////////////////
    // splitter<T, U>::split
    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    template <class V, class W>
    void
    splitter<T, U>::split(
        V& input,
        std::function<bool(char_type)> delimiter_predicate,
        std::function<void(token_type)> analyzer,
        W& buffer)
    {
        typedef typename W::const_iterator const_iterator;
        buffered_splitter<T>::split(
            input,
            delimiter_predicate,
            [&analyzer](char_type d, const_iterator begin, const_iterator end) {
                while (begin != end) {
                    begin = token_type::make_token(begin, end, analyzer);
                }
            });
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // splitter<T, U>::split
    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    template <class V>
    void
    splitter<T, U>::split(
        V& input,
        std::function<bool(char_type)> delimiter_predicate,
        std::function<void(token_type)> analyzer)
    {
        std::vector<char_type> buffer;
        split(input, delimiter_predicate, analyzer, buffer);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // buffered_splitter<T, U>::split
    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    template <class V>
    void
    buffered_splitter<T, U>::split(
        V& input,
        std::function<bool(char_type)> delimiter_predicate,
        std::function<void(char_type,
            const_iterator,
            const_iterator)>
            analyzer,
        U& buffer)
    {
        char_type front;
        while (input.get(front)) {
            if (delimiter_predicate(front)) {
                analyzer(front, buffer.begin(), buffer.end());
                buffer.clear();
            } else
                buffer.push_back(front);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // buffered_splitter<T, U>::split
    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    template <class V>
    void
    buffered_splitter<T, U>::split(
        V& input,
        std::function<bool(char_type)> delimiter_predicate,
        std::function<void(char_type,
            const_iterator,
            const_iterator)>
            analyzer)
    {
        std::vector<char_type> buffer;
        split(input, delimiter_predicate, analyzer, buffer);
    }
} // fluke
} // om636
