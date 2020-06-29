/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#include "Player.hpp"
#include "../Bomb/Bomb.hpp"

Player::Player(std::string meshName, std::string textureName, std::shared_ptr<Irrlicht> irr, irr::EKEY_CODE advance, irr::EKEY_CODE behind, irr::EKEY_CODE left, irr::EKEY_CODE right, irr::EKEY_CODE plantBomb)
{
    this->_irr = irr;
    this->MOVEMENT_SPEED = 5.f;
    this->then = _irr->getDevice()->getTimer()->getTime();
    // this->_joystickInfo = _irr->getJoystickinfo();
    // this->_receiver = _irr->getEventreceiver();
    this->joysticActivated = 0;

    //SetKeyboard
    this->_advance = advance;
    this->_behind = behind;
    this->_left = left;
    this->_right = right;
    this->_plantBomb = plantBomb;

    this->event = std::make_unique<PlayerEvent>(_irr, advance, behind, left, right, plantBomb, this);
    this->initPlayer(meshName, textureName, _irr->getSmgr(), _irr->getDriver());
}

Player::~Player()
{
}

irr::scene::IAnimatedMeshSceneNode* Player::getPlayerOBJ()
{
    return(this->PlayerOBJ);
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

void Player::moveUpKeyboard(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime)
{
    this->PlayerOBJ->setRotation(irr::core::vector3df(0, 180, 0));
    ray.end = ray.start + vector3df(0.0f, 0.0f, 100.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
    }
    PlayerOBJ->setPosition(nodePosition);
}
void Player::moveDownKeyboard(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime)
{
    this->PlayerOBJ->setRotation(irr::core::vector3df(0, 0, 0));
    ray.end = ray.start + vector3df(0.0f, 0.0f, -100.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
    }
    PlayerOBJ->setPosition(nodePosition);
}
void Player::moveRightKeyboard(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime)
{
    this->PlayerOBJ->setRotation(irr::core::vector3df(0, -90, 0));
    ray.end = ray.start + vector3df(100.0f, 0.0f, 0.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
    }
    PlayerOBJ->setPosition(nodePosition);
}
void Player::moveLeftKeyboard(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime)
{
    this->PlayerOBJ->setRotation(irr::core::vector3df(0, 90, 0));
    ray.end = ray.start + vector3df(-100.0f, 0.0f, 0.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
    }
    PlayerOBJ->setPosition(nodePosition);
}

void Player::moveUpControler(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime, irr::f32 moveVertical)
{
    ray.end = ray.start + vector3df(0.0f, 0.0f, 100.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime * moveVertical;
        this->PlayerOBJ->setRotation(irr::core::vector3df(0, 180, 0));
    }
    PlayerOBJ->setPosition(nodePosition);
}
void Player::moveDownControler(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime, irr::f32 moveVertical)
{
    ray.end = ray.start + vector3df(0.0f, 0.0f, -100.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime * moveVertical;
        this->PlayerOBJ->setRotation(irr::core::vector3df(0, 0, 0));
    }
    PlayerOBJ->setPosition(nodePosition);
}
void Player::moveRightControler(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime, irr::f32 moveHorizontal)
{
    ray.end = ray.start + vector3df(100.0f, 0.0f, 0.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        nodePosition.X += MOVEMENT_SPEED * frameDeltaTime * moveHorizontal;
        this->PlayerOBJ->setRotation(irr::core::vector3df(0, -90, 0));
    }
    PlayerOBJ->setPosition(nodePosition);
}
void Player::moveLeftControler(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime, irr::f32 moveHorizontal)
{
    ray.end = ray.start + vector3df(-100.0f, 0.0f, 0.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        nodePosition.X += MOVEMENT_SPEED * frameDeltaTime * moveHorizontal;
        this->PlayerOBJ->setRotation(irr::core::vector3df(0, 90, 0));
    }
    PlayerOBJ->setPosition(nodePosition);
}

void Player::plantBomb(std::shared_ptr<GameMap> map, std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities)
{
    if (map->getMap().at((int)PlayerOBJ->getPosition().Z + int((map->getMapSize().Y / 2))).
        at((int)PlayerOBJ->getPosition().X + int((map->getMapSize().X / 2))) == NULL) {
        entities->push_back(std::make_shared<Bomb>(_irr, PlayerOBJ->getPosition()));
    }
}

void Player::canCollide(bool b)
{

}

void Player::update(std::shared_ptr<GameMap> map, std::shared_ptr<Assets> assets)
{
    if (isRemove == false) {
        const irr::u32 now = _irr->getDevice()->getTimer()->getTime();
        const irr::f32 frameDeltaTime = (irr::f32)(now - this->then) / 1000.f;
        this->then = now;
        if (!this->isAI) {
            event->movementPlayer(map, _irr->getJoystickinfo(), _irr->getEventreceiver(), this->MOVEMENT_SPEED, frameDeltaTime);
            event->plantBomb(map, assets->getEntities());
        }
    }
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