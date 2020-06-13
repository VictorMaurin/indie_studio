#include "Bomb.hpp"

Bomb::Bomb(Core *core, vector3df pos)
{
    core = core;
    device = core->getDevice();
    driver = core->getDriver();
    smgr = core->getSmgr();
    mesh = std::make_unique<Mesh>(
        "bomb2.obj", "bombbody_BaseColor.png",
        core, smgr, driver, device);
    
    mesh->setPosition(pos);
    vector3di posInt;
    posInt.X = (int)pos.X;
    posInt.Y = (int)pos.Y;
    posInt.Z = (int)pos.Z;
    // posInt.X -= 2;
    vector3df posFloat;
    posFloat.X = (float)posInt.X;
    posFloat.Y = (float)posInt.Y;
    posFloat.Z = (float)posInt.Z;
    // mesh->setScale(scale);
    then = device->getTimer()->getRealTime();
    mesh->setPosition(posFloat);
}

Bomb::~Bomb()
{
}

void Bomb::createExplodeCube()
{
    // _core->getEntities()->push_back(std::make_shared<Explosion>(this->_core, mesh->getPosition()));
    mesh->remove();
}

void Bomb::explode()
{
    createExplodeCube();
}

void Bomb::update(std::shared_ptr<GameMap> map)
{
    now = device->getTimer()->getRealTime();
    // node->setScale(vector3df(0.01f, 0.01f, 0.01f));
    if ((now - then) / 1000 >= 3 && passed == false) {
        passed = true;
        explode();
    }
}

void Bomb::draw(void) const
{
}

void Bomb::canCollide(__attribute__((unused)) bool b)
{

}

void Bomb::setPosition(const irr::core::vector3df &pos)
{
    node->setPosition(pos);
}

irr::core::vector3df Bomb::getPosition() const
{
    return (node->getPosition());
}

void Bomb::setScale(const irr::core::vector3df &scale)
{
    node->setScale(scale);
}

irr::core::vector3df Bomb::getScale() const
{
    return (node->getScale());
}

void Bomb::remove()
{

}

bool Bomb::isBreakable()
{
    return (true);
}