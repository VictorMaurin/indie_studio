#include "Bomb.hpp"

Bomb::Bomb(Core *core, vector3df pos)
{
    core = core;
    device = core->getDevice();
    driver = core->getDriver();
    smgr = core->getSmgr();
    mesh = std::make_unique<Mesh>(
        "bomb.obj", "bombbody_BaseColor.png",
        smgr, driver, device);
    
    mesh->setPosition(pos);
    pos.X -= 2;

    // mesh->setScale(scale);
    mesh->setPosition(pos);
}

Bomb::~Bomb()
{
}

void Bomb::createExplodeCube()
{

}

void Bomb::explode()
{
    std::cout << "bomb explode" << std::endl;
    // mesh->remove();
    createExplodeCube();
}

void Bomb::update(void)
{
    now = device->getTimer()->getTime();
    std::cout << now << std::endl;
    // node->setScale(vector3df(0.01f, 0.01f, 0.01f));
    if (now / 1000 >= 6) {
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