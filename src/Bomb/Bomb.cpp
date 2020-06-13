#include "Bomb.hpp"

Bomb::Bomb(Core *core, vector3df pos)
{
    _core = core;
    device = _core->getDevice();
    driver = _core->getDriver();
    smgr = _core->getSmgr();
    mesh = std::make_shared<Mesh>(
        "bomb2.obj", "bombbody_BaseColor.png",
        smgr, driver, device);
    
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

void Bomb::update(void)
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