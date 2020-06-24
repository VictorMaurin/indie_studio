#include "irrlicht.h"
#include <iostream>
#include <unistd.h>
#include <memory>

int main()
{
    irr::IrrlichtDevice *device = irr::createDevice( irr::video::EDT_OPENGL, 
    irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, false, 0);

    if (!device)
        return 1;
    device->setWindowCaption(L"Hello world! - Irrlicht Engine Demo");
    std::shared_ptr<irr::video::IVideoDriver> driver = std::shared_ptr<irr::video::IVideoDriver>(device->getVideoDriver());
    std::shared_ptr<irr::scene::ISceneManager> smg = std::shared_ptr<irr::scene::ISceneManager>(device->getSceneManager());
    std::shared_ptr<irr::gui::IGUIEnvironment> guienv = std::shared_ptr<irr::gui::IGUIEnvironment>(device->getGUIEnvironment());
    guienv->addStaticText(L"Nique tes grands mort!", 
    irr::core::rect<irr::s32>(10, 10, 260, 22), true);

    std::shared_ptr<irr::scene::IMesh> mesh = std::shared_ptr<irr::scene::IMesh>(smg->getMesh("/Users/paul/epitech/OOP_indie_studio_2019/assets/crate3.obj"));
    if (!mesh.get())
    {
        device->drop();
        return 1;
    }
    std::shared_ptr<irr::scene::IMeshSceneNode> node = std::shared_ptr<irr::scene::IMeshSceneNode>(smg->addMeshSceneNode(mesh.get()));

    if (node.get())
    {
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMaterialTexture( 0, driver->getTexture("/Users/paul/epitech/OOP_indie_studio_2019/assets/crate3.png") );
        node->setScale(irr::core::vector3d<float>(30.0f, 30.0f, 30.0f));
        irr::scene::ISceneNodeAnimator* anim = smg->createRotationAnimator(irr::core::vector3df(0,0.1f,0));
        node->addAnimator(anim);
        anim->drop();
    }

    node->remove();

    smg->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));

    float rotation = 0.0;
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