#include "Player.hpp"
#include "../Event/Event.hpp"
#include <memory>

#ifdef IRR_WINDOWS
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
#include <iostream>

Player::Player() : AEntity()
{
}

Player::~Player()
{

}


void Player::initPlayer(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver)
{
    this->PlayerOBJ =
        sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../build/assets/Bomberman.MD3"));
    if (this->PlayerOBJ)
    {
        PlayerOBJ->setFrameLoop(0, 25);
        PlayerOBJ->setAnimationSpeed(0);
        PlayerOBJ->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        PlayerOBJ->setMaterialTexture(0, driver->getTexture("../build/assets/BlackBombermanTextures.png"));
    }
}

int main(void) {

    MyEventReceiver receiver; //Pour g�r� les event keyboard
    irr::IrrlichtDevice* device =
        irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(640, 480), 16,
            false, false, false, &receiver);
    irr::video::IVideoDriver* driver =                  // creation du driver video
        device->getVideoDriver();
    irr::scene::ISceneManager* sceneManager =           // creation du scene manager
        device->getSceneManager();
    device->getCursorControl()->setVisible(false);   // rend le curseur invisible
    irr::SEvent event;
    std::unique_ptr<Player> BOT = std::make_unique<Player>();

    //BOT->initPlayer(sceneManager, driver);

    BOT->PlayerOBJ =
        sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../build/assets/Bomberman.MD3"));
    if (BOT->PlayerOBJ)
    {
        BOT->PlayerOBJ->setFrameLoop(0, 25);
        BOT->PlayerOBJ->setAnimationSpeed(0);
        BOT->PlayerOBJ->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        BOT->PlayerOBJ->setMaterialTexture(0, driver->getTexture("../build/assets/BlackBombermanTextures.png"));
    }

    sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 5, 10), irr::core::vector3df(0, 0, 0));
    const irr::f32 MOVEMENT_SPEED = 5.f;
    irr::u32 then = device->getTimer()->getTime();

    while (device->run())
    {
        const irr::u32 now = device->getTimer()->getTime();
        const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
        then = now;
        irr::core::vector3df nodePosition = BOT->PlayerOBJ->getPosition();


        if (receiver.IsKeyDown(irr::KEY_KEY_S)) {
            BOT->PlayerOBJ->setAnimationSpeed(100);
            nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
            BOT->PlayerOBJ->setRotation(irr::core::vector3df(0, 180, 0));

        }
        else if (receiver.IsKeyDown(irr::KEY_KEY_Z)) {
            BOT->PlayerOBJ->setAnimationSpeed(100);
            nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
            BOT->PlayerOBJ->setRotation(irr::core::vector3df(0, 0, 0));
        }
        else if (receiver.IsKeyDown(irr::KEY_KEY_D)) {
            BOT->PlayerOBJ->setAnimationSpeed(100);
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
            BOT->PlayerOBJ->setRotation(irr::core::vector3df(0, 90, 0));
        }
        else if (receiver.IsKeyDown(irr::KEY_KEY_Q)) {
            BOT->PlayerOBJ->setAnimationSpeed(100);
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
            BOT->PlayerOBJ->setRotation(irr::core::vector3df(0, -90, 0));
        }
        else {
            //BOT->setRotation(irr::core::vector3df(0, 0, 0));
            BOT->PlayerOBJ->setAnimationSpeed(0);
            BOT->PlayerOBJ->setFrameLoop(0, 25);
        }
        BOT->PlayerOBJ->setPosition(nodePosition);
        //BOT->setFrameLoop(0, 0);
        //BOT->setAnimationSpeed(0);
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

        sceneManager->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}

/*
That's it. Compile and run.
**/
