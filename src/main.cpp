#include "irrlicht.h"
#include <iostream>
#include "Exception/MyException.hpp"
#include "Core/Core.hpp"

int main()
{
    Core core;

    srand(time(0));
    try
    {
        core.init();
        core.run();
    }
    catch(const MyException& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "in file: " << e.get_file() << " in function: " << e.get_func() << ":" << e.get_line() << std::endl;
    }
    catch(const char *e)
    {
        std::cerr << e << std::endl;
    }
    
    return (0);
}