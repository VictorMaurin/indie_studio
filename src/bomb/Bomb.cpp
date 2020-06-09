#include "Bomb.hpp"

Bomb::Bomb(Core core, Player player)
{
    driver = core.getDriver();
    device = core.getDevice();
    smgr = core.getSmgr();
    this->then = device->getTimer()->getTime();
    mesh = smgr->getMesh("../../assets/bomb.obj");
    if (!mesh) {
        device->drop();
        throw "device drop";
    }
    node = smgr->addMeshSceneNode(mesh);
    if (node) {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMaterialTexture(0, driver->getTexture("../../assets/bombbody_BaseColor.png"));
    }
    // pos = player.getPos();
}

Bomb::~Bomb()
{
}

void Bomb::explode()
{
    
}

void Bomb::update(void)
{
    now = device->getTimer()->getTime();
    if (now - then > 3) {
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