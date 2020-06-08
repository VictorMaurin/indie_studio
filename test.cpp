#include <irrlicht/irrlicht.h>
#include <iostream>
/*
int main()
{
    //irr::video::EDT_SOFTWARE
    irr::IrrlichtDevice *device = irr::createDevice( irr::video::EDT_OPENGL, 
    irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, false, 0);

    if (!device)
        return 1;
    device->setWindowCaption(L"Hello world! - Irrlicht Engine Demo");
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    irr::scene::ISceneManager *smg = device->getSceneManager();
    irr::gui::IGUIEnvironment *guienv = device->getGUIEnvironment();
    guienv->addStaticText(L"Nique tes grands mort!", 
    irr::core::rect<irr::s32>(10, 10, 260, 22), true);

    irr::scene::IMesh *mesh = smg->getMesh("crate/crate3.obj");
    if (!mesh)
    {
        device->drop();
        return 1;
    }
    irr::scene::IMeshSceneNode *node = smg->addMeshSceneNode(mesh);

    if (node)
    {
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMaterialTexture( 0, driver->getTexture("crate/crate3.png") );
        node->setScale(irr::core::vector3d<float>(30.0f, 30.0f, 30.0f));
        irr::scene::ISceneNodeAnimator* anim = smg->createRotationAnimator(irr::core::vector3df(0,0.1f,0));
        node->addAnimator(anim);
        anim->drop();
    }


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
}*/