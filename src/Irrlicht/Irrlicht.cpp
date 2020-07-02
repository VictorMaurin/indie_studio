#include "Irrlicht.hpp"

Irrlicht::Irrlicht()
{
}

Irrlicht::~Irrlicht()
{
}

void Irrlicht::init()
{
    #ifdef __APPLE__
        video::E_DRIVER_TYPE driverType = EDT_OPENGL;
    #else
        video::E_DRIVER_TYPE driverType = driverChoiceConsole();
    #endif
    if (driverType == video::EDT_COUNT)
        throw MyException("unknown driver requested", "Irrlicht.cpp", 19, "Irrlicht::init()");

    device = std::shared_ptr<IrrlichtDevice>(createDevice(driverType, dimension2d<u32>(640, 480), 16, false, false, false, eventReceiver.get()));
    if (!device.get())
        throw MyException("couldn't create device", "Irrlicht.cpp", 23, "Irrlicht::init()");
    device->setResizable(true);
    device->setWindowCaption(L"Hello world! - Irrlicht Engine Demo");
    
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    if (!driver || ! smgr || !guienv)
        throw MyException("couldn't create environment", "Irrlicht.cpp", 30, "Irrlicht::init()");
    
    collMan = smgr->getSceneCollisionManager();
    if (!collMan)
        throw MyException("error with collision manager", "Irrlicht.cpp", 33, "Irrlicht::init()");
    
    smgr->addCameraSceneNode(0, vector3df(0,11,-2), vector3df(0,0,0));
    eventReceiver = std::make_shared<MyEventReceiver>();
    if (!eventReceiver.get())
        throw MyException("event manager creation failed", "Irrlicht.cpp", 37, "Irrlicht::init()");
}

IVideoDriver *Irrlicht::getDriver() const
{
    return (this->driver);
}

ISceneManager *Irrlicht::getSmgr() const
{
    return (this->smgr);
}

std::shared_ptr<IrrlichtDevice> Irrlicht::getDevice() const
{
    return (this->device);
}

IGUIEnvironment *Irrlicht::getGUIenv() const
{
    return (this->guienv);
}

ISceneCollisionManager *Irrlicht::getCollMan() const
{
    return(this->collMan);
}

std::shared_ptr<MyEventReceiver> Irrlicht::getEventreceiver() const
{
    return (this->eventReceiver);
}

irr::core::array<irr::SJoystickInfo> &Irrlicht::getJoystickinfo()
{
    return (this->joystickInfo);
}