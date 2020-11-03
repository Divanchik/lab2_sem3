/**
 * \file
 * Main source file
 */
#include <iostream>
#include <cstdlib>
#include "binimlib.h"
using namespace binim;
/**
 * Body of program
 * \return Exit code('0' if program is successfully closed)
 */
int main()
{
    try
    {
        srand(time(NULL));
        enable_logging();
        BinImage a;
        a.resize(5, 5);
        //BinImage a(0,-1,false); // Should throw an exception
        //a.resize(0,0); // Should throw an exception
        fill_random(a);
        //log("#1\n");
        BinImage b(a); // Should be copy constructor
        //log("#2\n");
        BinImage c = std::move(a+b); // Should be move constructor
        //log("#3\n");
        std::cout << a << b << c << std::endl;
        c = a * false;
        c = b;
        std::cout << c.coefficient() << std::endl;
        c = !c;
        std::cout << c.coefficient() << std::endl;
        std::cout << c.coefficient() << std::endl;
        std::cout << a << b << c << std::endl;
        getchar();
    }
    catch(const char* exception)
    {
        std::cout << "Program throwed an exception: " << exception << std::endl;
    }
    return 0;
}
