/**
 * \file
 * Main source file for executable
 */
#include <iostream>
#include <cstdlib>
#include "binimlib.h"
using namespace binim;
int main()
{
    srand(time(NULL));
    enable_logging();
    BinImage a;
    a.resize(1, 5);
    fill_random(a);
    BinImage b;
    b.resize(1, 5);
    fill_random(b);
    BinImage c;
    std::cout << a << b << std::endl;
    std::cout << a + b << a * b << a * 0 << b + 1;
    getchar();
    return 0;
}
