#ifndef CORE_HPP
#define CORE_HPP

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include "../Entity/AEntity.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

enum class State : int
{
    NOTHING,
    GAME,
    MENU
};

class Core
{
private:
    IVideoDriver *driver;
    ISceneManager *smgr;
    IGUIEnvironment *guienv;
    IrrlichtDevice *device;
    std::vector<IEntity> entities;
    State statement;

public : 
    Core(/* args */);
    ~Core();
    void run();
    void loop();
    void set_menu();
    void set_game();
    void update_menu();
    void update_game();
    const std::vector<IEntity> &getEntities() const;
    const IVideoDriver *getDriver() const;
    const ISceneManager *getSmgr() const;
    const IrrlichtDevice *getDevice() const;
};

#endif