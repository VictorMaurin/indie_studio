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
    if (meshName.empty() || textureName.empty() || !irr || !irr.get())
        throw MyException("unexpected argument", "Player.cpp", 14, "Player::ctor()");
    this->_irr = irr;
    this->_speed = 5.f;
    this->then = _irr->getDevice()->getTimer()->getTime();

    //SetKeyboard
    this->_advance = advance;
    this->_behind = behind;
    this->_left = left;
    this->_right = right;
    this->_plantBomb = plantBomb;

    this->event = std::make_unique<PlayerEvent>(_irr, advance, behind, left, right, plantBomb, this);
    if (!event || !event.get())
        throw MyException("couldn't create player's event receiver", "Player.cpp", 26, "Player::ctor()");
    this->initPlayer(meshName, textureName);
}

Player::~Player()
{
}

void Player::initPlayer(std::string meshName, std::string textureName)
{
    this->PlayerOBJ = _irr->getSmgr()->addAnimatedMeshSceneNode(_irr->getSmgr()->getMesh(findAsset(meshName).c_str()));
    if (this->PlayerOBJ)
    {
        PlayerOBJ->setFrameLoop(0, 25);
        PlayerOBJ->setAnimationSpeed(0);
        PlayerOBJ->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        PlayerOBJ->setMaterialTexture(0, _irr->getDriver()->getTexture(findAsset(textureName).c_str()));
    } else
        throw MyException("couldn't create player", "Player.cpp", 44, "Player::init()");
}

void Player::moveUp(const irr::f32 frameDeltaTime, irr::f32 moveVertical)
{
    irr::core::vector3df nodePosition = this->getPosition();
    vector3df intersection;
    triangle3df hitTriangle;
    line3df ray;

    ray.start = nodePosition;
    ray.start.Y += 0.3;
    ray.end = ray.start + vector3df(0.0f, 0.0f, 100.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    this->PlayerOBJ->setRotation(irr::core::vector3df(0, 180, 0));
    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        if (this->event->isJoystickActivated())
            nodePosition.Z += _speed * frameDeltaTime * moveVertical;
        else
            nodePosition.Z += _speed * frameDeltaTime;
    }
    PlayerOBJ->setPosition(nodePosition);
}

void Player::moveDown(const irr::f32 frameDeltaTime, irr::f32 moveVertical)
{
    irr::core::vector3df nodePosition = this->getPosition();
    vector3df intersection;
    triangle3df hitTriangle;
    line3df ray;

    ray.start = nodePosition;
    ray.start.Y += 0.3;
    ray.end = ray.start + vector3df(0.0f, 0.0f, -100.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    this->PlayerOBJ->setRotation(irr::core::vector3df(0, 0, 0));
    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        if (this->event->isJoystickActivated())
            nodePosition.Z += _speed * frameDeltaTime * moveVertical;
        else
            nodePosition.Z -= _speed * frameDeltaTime;
    }
    PlayerOBJ->setPosition(nodePosition);
}

void Player::moveRight(const irr::f32 frameDeltaTime, irr::f32 moveHorizontal)
{
    irr::core::vector3df nodePosition = this->getPosition();
    vector3df intersection;
    triangle3df hitTriangle;
    line3df ray;

    ray.start = nodePosition;
    ray.start.Y += 0.3;
    ray.end = ray.start + vector3df(100.0f, 0.0f, 0.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    this->PlayerOBJ->setRotation(irr::core::vector3df(0, -90, 0));
    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        if (this->event->isJoystickActivated())
            nodePosition.X += _speed * frameDeltaTime * moveHorizontal;
        else
            nodePosition.X += _speed * frameDeltaTime;
    }
    PlayerOBJ->setPosition(nodePosition);
}

void Player::moveLeft(const irr::f32 frameDeltaTime, irr::f32 moveHorizontal)
{
    irr::core::vector3df nodePosition = this->getPosition();
    vector3df intersection;
    triangle3df hitTriangle;
    line3df ray;

    ray.start = nodePosition;
    ray.start.Y += 0.3;
    ray.end = ray.start + vector3df(-100.0f, 0.0f, 0.0f);
    _irr->getCollMan()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);

    this->PlayerOBJ->setRotation(irr::core::vector3df(0, 90, 0));
    if ((intersection - nodePosition).getLength() > 0.4f) {
        this->PlayerOBJ->setAnimationSpeed(100);
        if (this->event->isJoystickActivated())
            nodePosition.X += _speed * frameDeltaTime * moveHorizontal;
        else
            nodePosition.X -= _speed * frameDeltaTime;
    }
    PlayerOBJ->setPosition(nodePosition);
}

void Player::plantBomb(std::shared_ptr<GameMap> map, std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities)
{
    if (map->getMap().at((int)PlayerOBJ->getPosition().Z + int((map->getMapSize().Y / 2))).
        at((int)PlayerOBJ->getPosition().X + int((map->getMapSize().X / 2))) == NULL) {
        entities->push_back(std::make_shared<Bomb>(_irr, PlayerOBJ->getPosition()));
        if (!entities->at(entities->size() - 1) || !entities->at(entities->size() - 1).get())
            throw MyException("couldn't create bomb", "Player.cpp", 145, "Player::plantBomb()");
    }
}

void Player::canCollide(bool b)
{
    
}

void Player::update(std::shared_ptr<Assets> assets)
{
    if (isRemove == false) {
        const irr::u32 now = _irr->getDevice()->getTimer()->getTime();
        const irr::f32 frameDeltaTime = (irr::f32)(now - this->then) / 1000.f;
        this->then = now;
        if (!this->isAI) {
            event->movementPlayer(assets->getMap(), frameDeltaTime);
            event->plantBomb(assets->getMap(), assets->getEntities());
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