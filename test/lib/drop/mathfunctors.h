#ifndef MATHFUNCTORS__INCLUDE_GUARD__545334543
	#define MATHFUNCTORS__INCLUDE_GUARD__545334543

namespace om636
{
	// unary functors
	struct Nop 
	{	
		template<class T, class U> 
		T & operator()(T & a, const U &) const { return a; }
		
		template<class T>	
		void operator()(const T &) const {}
		
		template<class T>	
		void operator()(T &) {}
	};

	struct post_increment
	{	
		template<class T>	
		void operator()(T & a) const
		{ a++; }
	};

	struct post_decrement
	{
		template<class T>	
		void operator()(T & a) const
		{ a--; }
	};

	struct pre_increment
	{
		template<class T>
		void operator()(T & a) const
		{ ++a; }
	};

	struct pre_decrement
	{
		template<class T>
		void operator()(T & a) const
		{ --a; }
	};

	struct complement
	{	
		template<class T>
		void operator()(T & a) const
		{  a = ~a; }
	};

	struct mult_inverse
	{
		template<class T>
		void operator()(T & a) const
		{ 	 a = 1/a; }
	};

    struct compare
    {
        compare() : m_result( 0 ) {}
        int result() const { return m_result; }
        
        template<class T, class U>
		bool operator()(const T & a, const U & b)
        {
            if (a > b)
                m_result = 1; 
            else if (a < b)
                m_result = -1; 
            return !m_result; 
        }
        
        template<class T>
		bool operator()(const T & a)
        {
            if (a > 0)
                m_result = 1; 
            else if (a < 0)
                m_result = -1; 
            return !m_result; 
        }
        
    private:
        int m_result; 
    };
    
	struct equal
	{	
        equal() : m_result( false ) {}
        
		template<class T, class U>
		bool operator()(const T & a, const U & b)
        {  
            return m_result = a == b;
        }

        bool result() const { return m_result; }

    private:
        bool m_result; 
    };
    
	struct assignment
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{	return a = b; 	}
	};

	struct _max
	{	
		template<class T, class U>
		const T & operator()(T & a, const U & b) const 
		{ return a = a > b ? a : b; }
	};

	struct _min
	{	
		template<class T, class U>
		const T & operator()(T & a, const U & b) const 
		{  return a = a < b ? a : b; }
	};

	struct binary_or
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{  return a |= b; }
	};

	struct binary_and
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{  return a &= b; }
	};

	struct binary_xor
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{ 	return a ^= b; }
	};

	struct sum
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{
			a += b; 
			return a;	
		}
	};

	struct difference
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{  
			a -= b;
			return a; 
		}
	};

	struct product
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{ 	
			a *= b;
			return a; 	
		}
	};

	struct quotient
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{  
			a /= b; 
			return a; 
		}
	};

	struct remainder
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{ 
			a %= b; 
			return a; 
		}
	};

	struct shift_right
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{	
			a >>=  b; 
			return a; 
		}
	};

	struct shift_left
	{
		template<class T, class U>
		T & operator()(T & a, const U & b) const
		{  
			a <<= b; 
			return a; 
		}
	};
}

#endif // __MATHFUNCTORS__INCLUDE_GUARD__545334543