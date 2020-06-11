#include "Bomb.hpp"

Bomb::Bomb(Core core, Player player)
{
    device = core.getDevice();
    driver = core.getDriver();
    smgr = core.getSmgr();
    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>(
        "bomb.obj", "bombbody_BaseColor.png",
        smgr, driver, device);
    mesh->setPosition(player.getPosition());
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
    if (now / 1000 >= 3) {
        explode();
    }
}

void Bomb::draw(void) const
{
}

void Bomb::setPos(const irr::core::vector3df pos)
{
}

void Bomb::getPos(void) const
{
}