namespace om636
{
    namespace tools 
    {
        template<class T>
        template<class U>
        void tester<T>::test_binary( const T & a, const T & b, const T & result, U f )
		{
			ASSERT( (a.*f)(b) == result );
			ASSERT( !((a.*f)(b) != result) );
		}
		
  		template<class T>
		void tester<T>::test_comparisons()
		{
			T a(0), b(0), c(1), d(-1);
			
			ASSERT( a == 0 );
			ASSERT( !(a != 0) );
			
			ASSERT( a == b );
			ASSERT( !(a != b) );
			
			ASSERT( a != 1 );
			ASSERT( !(a == 1) );
			
			ASSERT( a != c );
			ASSERT( !(a == c) );
			
			ASSERT( d == -1 );
			ASSERT( !(d != -1) );
			
			ASSERT( d == -c );
			ASSERT( !(d != -c) );
			
			ASSERT( d != 1 );
			ASSERT( !(d == 1) );
			
			ASSERT( d != c );
			ASSERT( !(d == c) );
			
			ASSERT( a >= 0 );
			ASSERT( !(a < 0) );
			
			ASSERT( a >= b );
			ASSERT( !(a < b) );
			
			ASSERT( a <= 0 );
			ASSERT( !(a > 0) );
			
			ASSERT( a <= b );
			ASSERT( !(a > b) );
			
			ASSERT( a < 1 );
			ASSERT( !(a >= 1) );
			
			ASSERT( a < c );
			ASSERT( !(a >= c) );
			
			ASSERT( c > 0 );
			ASSERT( !(c <= 0) );
			
			ASSERT( c > a );
			ASSERT( !(c <= a) );
			
			ASSERT( a < -d );
			ASSERT( !(a >= -d) );
			
			ASSERT( -d > 0 );
			ASSERT( !(-d <= 0) );
			
			ASSERT( -d > a );
			ASSERT( !(-d <= a) );
		}

        template<class T>
        void tester<T>::test_increments()
        {
			using namespace std;
			typedef T(T::*signature_type)(const T &) const;
			
			T a(0), b(1), c(1), d(-1);
			
			test_binary<signature_type>( a, c, b, & T::operator+ );
			test_binary<signature_type>( c, d, a, & T::operator+ );
			test_binary<signature_type>( b, c, a, & T::operator- );
			test_binary<signature_type>( a, c, d, & T::operator- );
			
			ASSERT( a + 1 >= b );
			ASSERT( !(a + 1 < b) );
			
			ASSERT( b - 1 >= a );
			ASSERT( !(a + 1 < b) );
			
			ASSERT( b - c >= a );
			ASSERT( !(b - c < a) );
			
			ASSERT( ++a == 1 );
			ASSERT( a++ == 1 );
			
			ASSERT( --a == 1 );
			ASSERT( a-- == 1 );
			
			ASSERT( ++b == 2 );
			ASSERT( b++ == 2 );
			
			ASSERT( --b == 2 );
			ASSERT( b-- == 2 );
			
			ASSERT( ++d == 0 );
			ASSERT( d++ == 0 );
			
			ASSERT( --d == 0 );
			ASSERT( d-- == 0 );
		}
		
		template<class T>
        template<class U>
		void tester<T>::test_conversions()
		{
			T a(0);
			
			ASSERT( a.template to_value<U>() == 0 );
			
			++a;
			ASSERT( a.template to_value<U>() == 1 );
		}
		
		template<class T>
        void tester<T>::test_number()
		{
			using namespace om636::tools;
			om636::tools::tester<T>::test_comparisons();
			om636::tools::tester<T>::test_increments();
			om636::tools::tester<T>::template test_conversions<int>();
			om636::tools::tester<T>::template test_conversions<float>();
		}

    }   // tools
}   // om636
