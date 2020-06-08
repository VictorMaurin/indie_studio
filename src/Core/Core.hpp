#ifndef CORE_HPP
#define CORE_HPP

#include <irrlicht/irrlicht.h>
#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include "../Entity/AEntity.hpp"

class Core
{
private:
    irr::video::IVideoDriver *driver;
    irr::scene::ISceneManager *smgr;
    irr::gui::IGUIEnvironment *guienv;
    irr::IrrlichtDevice *device;
public : 
    Core(/* args */);
    void run();
    ~Core();
};

#endif