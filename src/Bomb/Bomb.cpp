#include "Bomb.hpp"

Bomb::Bomb(Core *core, vector3df pos)
{
    core = core;
    device = core->getDevice();
    driver = core->getDriver();
    smgr = core->getSmgr();
    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>(
        "bomb.obj", "bombbody_BaseColor.png",
        smgr, driver, device);
    mesh->setPosition(pos);
    node->setPosition(pos);
}

Bomb::~Bomb()
{
}

void Bomb::createExplodeCube()
{

}

void Bomb::explode()
{
    createExplodeCube();
}

void Bomb::update(void)
{
    now = device->getTimer()->getTime();
    node->setScale(vector3df(0.01f, 0.01f, 0.01f));
    if (now / 1000 >= 3) {
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
     
}