#ifndef CORE_HPP
#define CORE_HPP

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include "../Mesh/Mesh.hpp"
#include "../Event/Event.hpp"
#include "../Player/Player.hpp"

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
    std::vector<std::shared_ptr<IEntity>> entities;
    State statement;
    MyEventReceiver *eventReceiver;
    irr::core::array<irr::SJoystickInfo> joystickInfo;

public : 
    Core(/* args */);
    ~Core();
    void run();
    void init();
    const std::vector<std::shared_ptr<IEntity>> &getEntities() const;
    void set_menu();
    void set_game();
    void update_menu();
    void update_game();
    IVideoDriver *getDriver() const;
    ISceneManager *getSmgr() const;
    IrrlichtDevice *getDevice() const;
};

#endif