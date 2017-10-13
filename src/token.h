/*  
    type: concrete

    objective:  
        - get token from stream 
        - hold token value and type 
 
    todo: 
        - the constructor has some arbitrary logic in it, need to imporove using policy classes
        - need to handle/throw exceptions
        - 
    
*/

#ifndef TOKEN_H_INCLUDEGUARD_0AQ1NPUBNR
#define TOKEN_H_INCLUDEGUARD_0AQ1NPUBNR

#include <sstream>
#include <string>

namespace om636 {
template <class T>
class token {
    struct tester {
        void operator delete(void*);
    };

public:
    typedef T value_type;
    enum token_id { number,
        variable,
        _operator,
        terminator,
        error };

    // resources
    token(const token&) = default;
    token& operator=(const token&) = default;
    ~token() = default;

    token(token_id = terminator, value_type = value_type());
    void swap(token&);

    // access
    const value_type& name() const;
    token_id type() const;
    template <class U>
    U to_value() const;
    operator tester*() const;
    bool operator!() const;

    template <class I>
    static I make_token(I, I, std::function<void(token)>);

private:
    token_id m_type;
    value_type m_name;
};

template <class T>
void swap(token<T>& lhs, token<T>& rhs);

} // om636

#include "token.hxx"

#endif // TOKEN_H_INCLUDEGUARD_0AQ1NPUBNR