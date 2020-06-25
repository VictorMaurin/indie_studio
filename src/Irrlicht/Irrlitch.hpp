#ifndef IRRLITCH_HPP
#define IRRLITCH_HPP

#include <irrlicht.h>
#include <memory>

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Irrlitch
{
private:
    std::shared_ptr<IrrlichtDevice> device;
    std::shared_ptr<IVideoDriver> driver;
    std::shared_ptr<ISceneManager> smgr;
    std::shared_ptr<IGUIEnvironment> guienv;

public:
    Irrlitch(/* args */);
    ~Irrlitch();
    std::shared_ptr<IVideoDriver> getDriver() const;
    std::shared_ptr<ISceneManager> getSmgr() const;
    std::shared_ptr<IrrlichtDevice> getDevice() const;
    std::shared_ptr<IGUIEnvironment> getGUIenv() const;
};

#endif