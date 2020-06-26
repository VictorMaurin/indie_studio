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
        throw("Problem in driver"); 
    //create device
    device = std::shared_ptr<IrrlichtDevice>(createDevice(driverType, dimension2d<u32>(640, 480), 16, false, false, false, eventReceiver.get()));
    if (!device)
        throw("Problem in device");
    device->setResizable(true);
    device->setWindowCaption(L"Hello world! - Irrlicht Engine Demo");
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    collMan = smgr->getSceneCollisionManager();
    eventReceiver = std::make_shared<MyEventReceiver>();
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