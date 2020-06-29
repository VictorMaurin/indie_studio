/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerEvent
*/

#include "PlayerEvent.hpp"
#include "../Bomb/Bomb.hpp"

PlayerEvent::PlayerEvent(std::shared_ptr<Irrlicht> irr, irr::EKEY_CODE advance, irr::EKEY_CODE behind, irr::EKEY_CODE left, irr::EKEY_CODE right, irr::EKEY_CODE plantBomb, irr::scene::IAnimatedMeshSceneNode* _PlayerOBJ, std::shared_ptr<Player> _player)
{
    this->joysticActivated = 0;
    this->_irr = irr;

    this->_advance = advance;
    this->_behind = behind;
    this->_left = left;
    this->_right = right;
    this->_plantBomb = plantBomb;

    this->PlayerOBJ = _PlayerOBJ;
    player = _player;

    this->initJoystic(_irr->getJoystickinfo(), _irr->getDevice());
}

PlayerEvent::~PlayerEvent()
{

}

void PlayerEvent::initJoystic(irr::core::array<irr::SJoystickInfo>& joystickInfo, std::shared_ptr<irr::IrrlichtDevice> device)
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

void PlayerEvent::movementPlayer(std::shared_ptr<GameMap> map, irr::core::array<irr::SJoystickInfo>& joystickInfo, std::shared_ptr<MyEventReceiver> receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime)
{
    this->movementPlayerKeyBoard(map, receiver, MOVEMENT_SPEED, frameDeltaTime);
    this->movementPlayerJoystick(map, joystickInfo, receiver, MOVEMENT_SPEED, frameDeltaTime);
}

void PlayerEvent::movementPlayerKeyBoard(std::shared_ptr<GameMap> map, std::shared_ptr<MyEventReceiver> receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime)
{
    vector3df nodePosition = player->getPosition();
    line3df ray;
    vector3df intersection;
    triangle3df hitTriangle;

    if (this->joysticActivated == 0) {
        ray.start = nodePosition;
        ray.start.Y += 0.3;

        if (receiver->IsKeyDown(this->_advance)) {
            player->moveUpKeyboard(ray, intersection, hitTriangle, nodePosition, frameDeltaTime);
        }
        else if (receiver->IsKeyDown(this->_behind)) {
            player->moveDownKeyboard(ray, intersection, hitTriangle, nodePosition, frameDeltaTime);
        }
        else if (receiver->IsKeyDown(this->_left)) {
            player->moveLeftKeyboard(ray, intersection, hitTriangle, nodePosition, frameDeltaTime);
        }
        else if (receiver->IsKeyDown(this->_right)) {
            player->moveRightKeyboard(ray, intersection, hitTriangle, nodePosition, frameDeltaTime);

        }
        else {
            if (this->joysticActivated == 0)
                player->getPlayerOBJ()->setFrameLoop(0, 25);
        }
    }
}

void PlayerEvent::movementPlayerJoystick(std::shared_ptr<GameMap> map, irr::core::array<irr::SJoystickInfo>& joystickInfo, std::shared_ptr<MyEventReceiver> receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime)
{
    // manette
    bool movedWithJoystick = false;
    irr::core::vector3df nodePosition = player->getPosition();
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
                    player->moveLeftControler(ray, intersection, hitTriangle, nodePosition, frameDeltaTime, moveHorizontal);
                }
                else if (moveHorizontal > 0) {
                    player->moveRightControler(ray, intersection, hitTriangle, nodePosition, frameDeltaTime, moveHorizontal);
                }
                else if (moveVertical > 0) {
                    player->moveUpControler(ray, intersection, hitTriangle, nodePosition, frameDeltaTime, moveVertical);
                }
                else if (moveVertical < 0) {
                    player->moveDownControler(ray, intersection, hitTriangle, nodePosition, frameDeltaTime, moveVertical);
                }
                movedWithJoystick = true;
            }
            else {
                player->getPlayerOBJ()->setFrameLoop(0, 25);
            }
        }
    }
}

void PlayerEvent::plantBomb(std::shared_ptr<GameMap> map, std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities)
{
    if (_irr->getEventreceiver()->IsKeyDown(this->_plantBomb)) {
        if (map->getMap().at((int)player->getPlayerOBJ()->getPosition().Z + int((map->getMapSize().Y / 2))).
            at((int)player->getPlayerOBJ()->getPosition().X + int((map->getMapSize().X / 2))) == NULL)
            entities->push_back(std::make_shared<Bomb>(_irr, player->getPlayerOBJ()->getPosition()));
    }
    if (this->joysticActivated == 1) {
        if (_irr->getEventreceiver()->GetJoystickState().ButtonStates == 2) {
            if (map->getMap().at((int)player->getPlayerOBJ()->getPosition().Z + int((map->getMapSize().Y / 2))).
                at((int)player->getPlayerOBJ()->getPosition().X + int((map->getMapSize().X / 2))) == NULL) {
                entities->push_back(std::make_shared<Bomb>(_irr, player->getPlayerOBJ()->getPosition()));
            }
        }
    }

}