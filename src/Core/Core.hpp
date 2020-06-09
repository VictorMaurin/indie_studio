#ifndef CORE_HPP
#define CORE_HPP

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include "../Entity/AEntity.hpp"
#include "../wall/Wall.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Core
{
private:
    IVideoDriver *driver;
    ISceneManager *smgr;
    IGUIEnvironment *guienv;
    IrrlichtDevice *device;
    std::vector<std::shared_ptr<IEntity>> entities;

public : 
    Core(/* args */);
    ~Core();
    void run();
    void init();
    const std::vector<std::shared_ptr<IEntity>> &getEntities() const;
    const IVideoDriver *getDriver() const;
    const ISceneManager *getSmgr() const;
    const IrrlichtDevice *getDevice() const;
};

#endif