#include <irrlicht/irrlicht.h>

int main()
{
    irr::IrrlichtDevice *device = irr::createDevice( irr::video::EDT_SOFTWARE, 
    irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, false, 0);

    if (!device)
        return 1;
    device->setWindowCaption(L"Hello world! - Irrlicht Engine Demo");
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    irr::scene::ISceneManager *smg = device->getSceneManager();
    irr::gui::IGUIEnvironment *guienv = device->getGUIEnvironment();
    guienv->addStaticText(L"Nique tes grands mort!", 
    irr::core::rect<irr::s32>(10, 10, 260, 22), true);
    smg->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));

    while (device->run())
    {
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        smg->drawAll();
        guienv->drawAll();
        driver->endScene();
    }
    device->drop();
    return (0);
}