#include "Player.hpp"

Player::Player(std::string meshName, std::string textureName, Core *core, irr::EKEY_CODE advance, irr::EKEY_CODE behind, irr::EKEY_CODE left, irr::EKEY_CODE right, irr::EKEY_CODE plantBomb)
{
    this->_core = core;
    this->_device = core->getDevice();
    this->MOVEMENT_SPEED = 5.f;
    this->then = core->getDevice()->getTimer()->getTime();
    this->_joystickInfo = core->getJoystickinfo();
    this->_receiver = core->getEventreceiver();
    this->joysticActivated = 0;

    //SetKeyboard
    this->_advance = advance;
    this->_behind = behind;
    this->_left = left;
    this->_right = right;
    this->_plantBomb = plantBomb;

    this->initPlayer(meshName, textureName, core->getSmgr(), core->getDriver());
    this->initJoystic(this->_joystickInfo, this->_device);
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

void Player::initPlayer(std::string meshName, std::string textureName, irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver)
{
    this->PlayerOBJ =
        sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh(findAsset(meshName).c_str()));
    if (this->PlayerOBJ)
    {
        PlayerOBJ->setFrameLoop(0, 25);
        PlayerOBJ->setAnimationSpeed(0);
        PlayerOBJ->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        PlayerOBJ->setMaterialTexture(0, driver->getTexture(findAsset(textureName).c_str()));
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

void Player::movementPlayerKeyBoard(std::shared_ptr<GameMap> map, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime)
{
    vector3df nodePosition = this->getPosition();
    line3df ray;
    vector3df intersection;
    triangle3df hitTriangle;
    
    if (this->joysticActivated == 0) {
        ray.start = nodePosition;
        ray.start.Y += 0.3;
        
        if (receiver->IsKeyDown(this->_advance)) {
            this->PlayerOBJ->setRotation(irr::core::vector3df(0, 180, 0));
            ray.end = ray.start + vector3df(0.0f, 0.0f, 100.0f);
            this->_core->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

            if ((intersection - nodePosition).getLength() > 0.4f) {
                this->PlayerOBJ->setAnimationSpeed(100);
                nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
            }
        } else if (receiver->IsKeyDown(this->_behind)) {
            this->PlayerOBJ->setRotation(irr::core::vector3df(0, 0, 0));
            ray.end = ray.start + vector3df(0.0f, 0.0f, -100.0f);
            this->_core->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

            if ((intersection - nodePosition).getLength() > 0.4f) {
                this->PlayerOBJ->setAnimationSpeed(100);
                nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
            }
        } else if (receiver->IsKeyDown(this->_left)) {
            this->PlayerOBJ->setRotation(irr::core::vector3df(0, 90, 0));
            ray.end = ray.start + vector3df(-100.0f, 0.0f, 0.0f);
            this->_core->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

            if ((intersection - nodePosition).getLength() > 0.4f) {
                this->PlayerOBJ->setAnimationSpeed(100);
                nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
            }
        } else if (receiver->IsKeyDown(this->_right)) {
            this->PlayerOBJ->setRotation(irr::core::vector3df(0, -90, 0));
            ray.end = ray.start + vector3df(100.0f, 0.0f, 0.0f);
            this->_core->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

            if ((intersection - nodePosition).getLength() > 0.4f) {
                this->PlayerOBJ->setAnimationSpeed(100);
                nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
            }
        } else {
            if (this->joysticActivated == 0)
                this->PlayerOBJ->setFrameLoop(0, 25);
        }
        this->setPosition(nodePosition);
    }
}

void Player::movementPlayerJoystick(std::shared_ptr<GameMap> map, irr::core::array<irr::SJoystickInfo> &joystickInfo, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime)
{
    // manette
    bool movedWithJoystick = false;
    irr::core::vector3df nodePosition = this->getPosition();
    line3df ray;
    vector3df intersection;
    triangle3df hitTriangle;

    if (joystickInfo.size() > 0)
    {
        irr::f32 moveHorizontal = 0.f; // Range is -1.f for full left to +1.f for full right
        irr::f32 moveVertical = 0.f; // -1.f for full down to +1.f for full up.

        const irr::SEvent::SJoystickEvent& joystickData = receiver->GetJoystickState();
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
                ray.start = nodePosition;
                ray.start.Y += 0.3;
                if (moveHorizontal < 0) {
                    ray.end = ray.start + vector3df(-100.0f, 0.0f, 0.0f);
                    this->_core->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);
                    
                    if ((intersection - nodePosition).getLength() > 0.4f) {
                        this->PlayerOBJ->setAnimationSpeed(100);
                        nodePosition.X += MOVEMENT_SPEED * frameDeltaTime * moveHorizontal;
                        this->PlayerOBJ->setRotation(irr::core::vector3df(0, 90, 0));
                    }
                }
                else if (moveHorizontal > 0) {
                    ray.end = ray.start + vector3df(100.0f, 0.0f, 0.0f);
                    this->_core->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);
                    
                    if ((intersection - nodePosition).getLength() > 0.4f) {
                        this->PlayerOBJ->setAnimationSpeed(100);
                        nodePosition.X += MOVEMENT_SPEED * frameDeltaTime * moveHorizontal;
                        this->PlayerOBJ->setRotation(irr::core::vector3df(0, -90, 0));
                    }
                }
                else if (moveVertical > 0) {
                    ray.end = ray.start + vector3df(0.0f, 0.0f, 100.0f);
                    this->_core->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);
                    
                    if ((intersection - nodePosition).getLength() > 0.4f) {
                        this->PlayerOBJ->setAnimationSpeed(100);
                        nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime * moveVertical;
                        this->PlayerOBJ->setRotation(irr::core::vector3df(0, 180, 0));
                    }
                }
                else if (moveVertical < 0) {
                    ray.end = ray.start + vector3df(0.0f, 0.0f, -100.0f);
                    this->_core->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);
                    
                    if ((intersection - nodePosition).getLength() > 0.4f) {
                        this->PlayerOBJ->setAnimationSpeed(100);
                        nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime * moveVertical;
                        this->PlayerOBJ->setRotation(irr::core::vector3df(0, 0, 0));
                    }
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

void Player::movementPlayer(std::shared_ptr<GameMap> map, irr::core::array<irr::SJoystickInfo> &joystickInfo, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime)
{
    if (!this->isAI) {
        movementPlayerKeyBoard(map, receiver, MOVEMENT_SPEED, frameDeltaTime);
        movementPlayerJoystick(map, joystickInfo, receiver, MOVEMENT_SPEED, frameDeltaTime);
    }
}

void Player::plantBomb(std::shared_ptr<GameMap> map)
{
    if (this->_receiver->IsKeyDown(this->_plantBomb)) {
        if (map->getMap().at((int)getPosition().Z + int((map->getMapSize().Y / 2))).
        at((int)getPosition().X + int((map->getMapSize().X / 2))) == NULL)
            this->_core->getEntities()->push_back(std::make_shared<Bomb>(this->_core, this->getPosition()));
    }
    if (this->joysticActivated == 1) {
        if (this->_receiver->GetJoystickState().ButtonStates == 2) {
            if (map->getMap().at((int)getPosition().Z + int((map->getMapSize().Y / 2))).
        at((int)getPosition().X + int((map->getMapSize().X / 2))) == NULL) {
                this->_core->getEntities()->push_back(std::make_shared<Bomb>(this->_core, this->getPosition()));
            }
        }
    }

}

void Player::canCollide(bool b)
{

}

//int main(void) {
//
//    MyEventReceiver receiver; //Pour g�r� les event keyboard
//    irr::IrrlichtDevice* device =
//    irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(640, 480), 16,
//        false, false, false, &receiver);
//    irr::core::array<irr::SJoystickInfo> joystickInfo;
//    std::unique_ptr<Player> BOT = std::make_unique<Player>();
//    BOT->initJoystic(joystickInfo, device);
//    irr::video::IVideoDriver* driver =                  // creation du driver video
//        device->getVideoDriver();
//    irr::scene::ISceneManager* sceneManager =           // creation du scene manager
//        device->getSceneManager();
//    device->getCursorControl()->setVisible(false);   // rend le curseur invisible
//    irr::SEvent event;
//    BOT->initPlayer(sceneManager, driver);
//
//    sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 5, 10), irr::core::vector3df(0, 0, 0));
//    irr::u32 then = device->getTimer()->getTime();
//
//    while (device->run())
//    {
//        const irr::u32 now = device->getTimer()->getTime();
//        const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
//        then = now;
//        BOT->movementPlayer(joystickInfo, receiver, MOVEMENT_SPEED, frameDeltaTime);
//        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
//
//        sceneManager->drawAll();
//        driver->endScene();
//    }
//    device->drop();
//
//    return 0;
//}

void Player::update(std::shared_ptr<GameMap> map)
{
    if (isRemove == false) {
        const irr::u32 now = this->_device->getTimer()->getTime();
        const irr::f32 frameDeltaTime = (irr::f32)(now - this->then) / 1000.f;
        this->then = now;
        this->movementPlayer(map, this->_joystickInfo, this->_receiver, this->MOVEMENT_SPEED, frameDeltaTime);
        this->plantBomb(map);
    }
}

void Player::draw(void) const
{
}

void Player::remove(void)
{
    if (this->PlayerOBJ && isRemove == false) {
        isRemove = true;
        this->PlayerOBJ->remove();
    }
}

bool Player::isBreakable(void)
{
    return (true);
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

void Player::SetIsAI(bool isAI)
{
    this->isAI = isAI;
}