#include "irrlicht.h"
#include <iostream>
#include <exception>
#include "Core/Core.hpp"

int main()
{
    Core core;
    try
    {
        core.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return (0);
}