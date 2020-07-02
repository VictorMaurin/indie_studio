/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerEvent
*/

#include "PlayerEvent.hpp"
#include "Bomb/Bomb.hpp"

PlayerEvent::PlayerEvent(std::shared_ptr<Irrlicht> irr, irr::EKEY_CODE advance, irr::EKEY_CODE behind, irr::EKEY_CODE left, irr::EKEY_CODE right, irr::EKEY_CODE plantBomb, Player* _player)
{
    this->joysticActivated = 0;
    this->_irr = irr;

    this->_advance = advance;
    this->_behind = behind;
    this->_left = left;
    this->_right = right;
    this->_plantBomb = plantBomb;

    player = _player;
    _irr->getDevice()->activateJoysticks(_irr->getJoystickinfo());
}

PlayerEvent::~PlayerEvent()
{

}

void PlayerEvent::movementPlayer(std::shared_ptr<GameMap> map, const irr::f32 frameDeltaTime)
{
    this->movementPlayerKeyBoard(map, frameDeltaTime);
    this->movementPlayerJoystick(map, frameDeltaTime);
}

void PlayerEvent::movementPlayerKeyBoard(std::shared_ptr<GameMap> map, const irr::f32 frameDeltaTime)
{
    if (this->joysticActivated == 0) {
        if (_irr->getEventreceiver()->IsKeyDown(this->_advance))
            player->moveUp(frameDeltaTime, 0.0f);
        else if (_irr->getEventreceiver()->IsKeyDown(this->_behind))
            player->moveDown(frameDeltaTime, 0.0f);
        else if (_irr->getEventreceiver()->IsKeyDown(this->_left))
            player->moveLeft(frameDeltaTime, 0.0f);
        else if (_irr->getEventreceiver()->IsKeyDown(this->_right))
            player->moveRight(frameDeltaTime, 0.0f);
        else {
            if (this->joysticActivated == 0)
                player->getPlayerOBJ()->setFrameLoop(0, 25);
        }
    }
}

void PlayerEvent::movementPlayerJoystick(std::shared_ptr<GameMap> map, const irr::f32 frameDeltaTime)
{
    bool movedWithJoystick = false;

    if (_irr->getJoystickinfo().size() > 0)
    {
        irr::f32 moveHorizontal = 0.f; // Range is -1.f for full left to +1.f for full right
        irr::f32 moveVertical = 0.f; // -1.f for full down to +1.f for full up.

        const irr::SEvent::SJoystickEvent& joystickData = _irr->getEventreceiver()->GetJoystickState();
        const irr::f32 DEAD_ZONE = 0.05f;

        if (joystickData.ButtonStates == 512)
            this->joysticActivated = 1;
        else if (joystickData.ButtonStates == 256)
            this->joysticActivated = 0;

        if (this->joysticActivated == 1) {
            moveHorizontal = (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
            if (fabs(moveHorizontal) < DEAD_ZONE)
                moveHorizontal = 0.f;
            moveVertical = (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
            if (fabs(moveVertical) < DEAD_ZONE)
                moveVertical = 0.f;
            const irr::u16 povDegrees = joystickData.POV / 100;
            if (povDegrees < 360) {
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
                if (moveHorizontal < 0)
                    player->moveLeft(frameDeltaTime, moveHorizontal);
                else if (moveHorizontal > 0)
                    player->moveRight(frameDeltaTime, moveHorizontal);
                else if (moveVertical > 0)
                    player->moveUp(frameDeltaTime, moveVertical);
                else if (moveVertical < 0)
                    player->moveDown(frameDeltaTime, moveVertical);
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
        player->plantBomb(map, entities);
    }
    if (this->joysticActivated == 1) {
        if (_irr->getEventreceiver()->GetJoystickState().ButtonStates == 2) {
            player->plantBomb(map, entities);
        }
    }

}

bool PlayerEvent::isJoystickActivated(void) const
{
    return (this->joysticActivated);
}