#include <iostream>

#include <plank/src/test.h>

#include "lexer.h"

//#include "fluke_test.h"

//#include <lib/fluke/src/token.h>

int main(int argc, const char * argv[])
{
    check_lexer();
    check_split_tokens();
//    check_parser();

  //  om636::token<std::string> t;
    return 0;
}

