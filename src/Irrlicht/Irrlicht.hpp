#ifndef IRRLITCH_HPP
#define IRRLITCH_HPP

#include <irrlicht.h>
#include <memory>
#include "Exception/MyException.hpp"
#include "Event/Event.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Irrlicht
{
private:
    std::shared_ptr<IrrlichtDevice> device;
    IVideoDriver *driver;
    ISceneManager *smgr;
    IGUIEnvironment *guienv;
    ISceneCollisionManager *collMan;
    std::shared_ptr<MyEventReceiver> eventReceiver;
    irr::core::array<irr::SJoystickInfo> joystickInfo;

public:
    Irrlicht();
    ~Irrlicht();
    void init();

    std::shared_ptr<MyEventReceiver> getEventreceiver() const;
    irr::core::array<irr::SJoystickInfo> &getJoystickinfo();
    ISceneCollisionManager *getCollMan() const;
    std::shared_ptr<IrrlichtDevice> getDevice() const;
    IVideoDriver *getDriver() const;
    ISceneManager *getSmgr() const;
    IGUIEnvironment *getGUIenv() const;
};

#endif