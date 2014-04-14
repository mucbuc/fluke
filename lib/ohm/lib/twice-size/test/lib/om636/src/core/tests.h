#ifndef TESTS_H__aKFXIJVg19rRDhPm7e3stf4Y5MzCOW
#define TESTS_H__aKFXIJVg19rRDhPm7e3stf4Y5MzCOW

namespace om636
{
    namespace tools 
    {
        template<class T>
        struct tester
        {
            template<class U>
            static void test_binary( const T &, const T &, const T &, U );
            
            static void test_comparisons();
            
            static void test_increments();
            
            template<class U>
            static void test_conversions();
            
            static void test_number();
        };

    }   // tools
}   // om636

#include "tests.hxx"
#endif // TESTS_H__aKFXIJVg19rRDhPm7e3stf4Y5MzCOW