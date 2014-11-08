#include <iostream>

#include <plank/src/test.h>
#include <lib/ohm/src/quemitter.h>

#include "fluke_test.h"

int main(int argc, const char * argv[])
{
    check_lexer();
    check_parser();
    return 0;
}

