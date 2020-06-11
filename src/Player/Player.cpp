#include "Player.hpp"
#ifdef IRR_WINDOWS
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
#include <iostream>

Player::Player() : IEntity()
{
}

Player::~Player()
{
}

void Player::setPosition(const irr::core::vector3df &pos)
{
    this->PlayerOBJ->setPosition(pos);
}

irr::core::vector3df Player::getPosition() const
{
    return (this->PlayerOBJ->getPosition());
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

void Player::initJoystic(irr::core::array<irr::SJoystickInfo> &joystickInfo, irr::IrrlichtDevice* device)
{
    if (device->activateJoysticks(joystickInfo))
    {
        std::cout << "Joystick support is enabled and " << joystickInfo.size() << " joystick(s) are present." << std::endl;

        for (irr::u32 joystick = 0; joystick < joystickInfo.size(); ++joystick)
        {
            std::cout << "Joystick " << joystick << ":" << std::endl;
            std::cout << "\tName: '" << joystickInfo[joystick].Name.c_str() << "'" << std::endl;
            std::cout << "\tAxes: " << joystickInfo[joystick].Axes << std::endl;
            std::cout << "\tButtons: " << joystickInfo[joystick].Buttons << std::endl;

            std::cout << "\tHat is: ";

            switch (joystickInfo[joystick].PovHat)
            {
            case irr::SJoystickInfo::POV_HAT_PRESENT:
                std::cout << "present" << std::endl;
                break;

            case irr::SJoystickInfo::POV_HAT_ABSENT:
                std::cout << "absent" << std::endl;
                break;

            case irr::SJoystickInfo::POV_HAT_UNKNOWN:
            default:
                std::cout << "unknown" << std::endl;
                break;
            }
        }
    }
    else
    {
        std::cout << "Joystick support is not enabled." << std::endl;
    }
    irr::core::stringw tmp = L"Irrlicht Joystick Example (";
    tmp += joystickInfo.size();
    tmp += " joysticks)";
    device->setWindowCaption(tmp.c_str());
    //End manette
}

void Player::movementPlayerMouse(MyEventReceiver receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime)
{
    irr::core::vector3df nodePosition = this->getPosition();

    if (this->joysticActivated == 0) {
        if (receiver.IsKeyDown(irr::KEY_KEY_S)) {
            this->PlayerOBJ->setAnimationSpeed(100);
            nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
            this->PlayerOBJ->setRotation(irr::core::vector3df(0, 180, 0));
        }
        else if (receiver.IsKeyDown(irr::KEY_KEY_Z)) {
            this->PlayerOBJ->setAnimationSpeed(100);
            nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
            this->PlayerOBJ->setRotation(irr::core::vector3df(0, 0, 0));
        }
        else if (receiver.IsKeyDown(irr::KEY_KEY_D)) {
            this->PlayerOBJ->setAnimationSpeed(100);
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
            this->PlayerOBJ->setRotation(irr::core::vector3df(0, 90, 0));
        }
        else if (receiver.IsKeyDown(irr::KEY_KEY_Q)) {
            this->PlayerOBJ->setAnimationSpeed(100);
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
            this->PlayerOBJ->setRotation(irr::core::vector3df(0, -90, 0));
        }
        else {
            if (this->joysticActivated == 0)
                this->PlayerOBJ->setFrameLoop(0, 25);
        }
    this->setPosition(nodePosition);
    }
}

void Player::movementPlayerJoystick(irr::core::array<irr::SJoystickInfo> &joystickInfo, MyEventReceiver receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime)
{
    // manette
    bool movedWithJoystick = false;
    irr::core::vector3df nodePosition = this->getPosition();
    if (joystickInfo.size() > 0)
    {
        irr::f32 moveHorizontal = 0.f; // Range is -1.f for full left to +1.f for full right
        irr::f32 moveVertical = 0.f; // -1.f for full down to +1.f for full up.

        const irr::SEvent::SJoystickEvent& joystickData = receiver.GetJoystickState();
        const irr::f32 DEAD_ZONE = 0.05f;

        if (joystickData.ButtonStates == 512)
            this->joysticActivated = 1;
        else if (joystickData.ButtonStates == 256)
            this->joysticActivated = 0;

        if (this->joysticActivated == 1) {
            moveHorizontal =
                (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
            if (fabs(moveHorizontal) < DEAD_ZONE)
                moveHorizontal = 0.f;
            moveVertical =
                (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
            if (fabs(moveVertical) < DEAD_ZONE)
                moveVertical = 0.f;
            const irr::u16 povDegrees = joystickData.POV / 100;
            if (povDegrees < 360)
            {
                if (povDegrees > 0 && povDegrees < 180)
                    moveHorizontal = 1.f;
                else if (povDegrees > 180)
                    moveHorizontal = -1.f;

                if (povDegrees > 90 && povDegrees < 270)
                    moveVertical = -1.f;
                else if (povDegrees > 270 || povDegrees < 90)
                    moveVertical = +1.f;
            }
            if (!irr::core::equals(moveHorizontal, 0.f) || !irr::core::equals(moveVertical, 0.f))
            {
                std::cout << moveHorizontal << std::endl;
                if (moveHorizontal < 0) {
                    this->PlayerOBJ->setAnimationSpeed(100);
                    nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime * moveHorizontal;
                    this->PlayerOBJ->setRotation(irr::core::vector3df(0, -90, 0));
                }
                else if (moveHorizontal > 0) {
                    this->PlayerOBJ->setAnimationSpeed(100);
                    nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime * moveHorizontal;
                    this->PlayerOBJ->setRotation(irr::core::vector3df(0, 90, 0));
                }
                else if (moveVertical > 0) {
                    this->PlayerOBJ->setAnimationSpeed(100);
                    nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime * moveVertical;
                    this->PlayerOBJ->setRotation(irr::core::vector3df(0, 0, 0));
                }
                else if (moveVertical < 0) {
                    this->PlayerOBJ->setAnimationSpeed(100);
                    nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime * moveVertical;
                    this->PlayerOBJ->setRotation(irr::core::vector3df(0, 180, 0));
                }
                movedWithJoystick = true;
            }
            else {
                this->PlayerOBJ->setFrameLoop(0, 25);
            }
        }
    this->PlayerOBJ->setPosition(nodePosition);
    }
}

void Player::movementPlayer(irr::core::array<irr::SJoystickInfo>& joystickInfo, MyEventReceiver receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime)
{
    this->movementPlayerMouse(receiver, MOVEMENT_SPEED, frameDeltaTime);
    this->movementPlayerJoystick(joystickInfo, receiver, MOVEMENT_SPEED, frameDeltaTime);
}

int main(void) {

    MyEventReceiver receiver; //Pour g�r� les event keyboard
    irr::IrrlichtDevice* device =
    irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(640, 480), 16,
        false, false, false, &receiver);
    irr::core::array<irr::SJoystickInfo> joystickInfo;
    std::unique_ptr<Player> BOT = std::make_unique<Player>();
    BOT->initJoystic(joystickInfo, device);
    irr::video::IVideoDriver* driver =                  // creation du driver video
        device->getVideoDriver();
    irr::scene::ISceneManager* sceneManager =           // creation du scene manager
        device->getSceneManager();
    device->getCursorControl()->setVisible(false);   // rend le curseur invisible
    irr::SEvent event;
    BOT->initPlayer(sceneManager, driver);

    sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 5, 10), irr::core::vector3df(0, 0, 0));
    const irr::f32 MOVEMENT_SPEED = 5.f;
    irr::u32 then = device->getTimer()->getTime();

    while (device->run())
    {
        const irr::u32 now = device->getTimer()->getTime();
        const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
        then = now;
        BOT->movementPlayer(joystickInfo, receiver, MOVEMENT_SPEED, frameDeltaTime);
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

        sceneManager->drawAll();
        driver->endScene();
    }
    device->drop();

    return 0;
}

void Player::update(void)
{

}

void Player::draw(void) const
{

}

void Player::setScale(const irr::core::vector3df& scale)
{
    if (this->PlayerOBJ)
        this->PlayerOBJ->setScale(scale);
}

irr::core::vector3df Player::getScale(void) const
{
    if (this->PlayerOBJ)
        return (this->PlayerOBJ->getScale());
    return(irr::core::vector3df(-1, -1, -1));
}
/*
That's it. Compile and run.
**/
