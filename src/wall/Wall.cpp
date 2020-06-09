#include <iostream>
#include "../assets/assets.hpp"
#include "Wall.hpp"

Wall::Wall(ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device)
{
    std::cout << ASSETS_PATH("crate3.obj") << std::endl;
    mesh = smgr->getMesh(ASSETS_PATH("crate3.obj"));
    if (!mesh)
    {
        device->drop();
        throw "couldnt create wall mesh";
    }
    node = smgr->addMeshSceneNode(mesh);
    if (node)
    {
        node->setMaterialTexture( 0, driver->getTexture(ASSETS_PATH("crate3.png")) );
        node->setScale(vector3d<float>(30.0f, 30.0f, 30.0f));
        ISceneNodeAnimator* anim = smgr->createRotationAnimator(vector3df(0,0.1f,0));
        node->addAnimator(anim);
        anim->drop();
    }
}

Wall::~Wall()
{
    delete node;
    delete mesh;
}

void Wall::update(void)
{

}

void Wall::draw(void) const
{

}

void Wall::setPosition(const vector3df &pos)
{
    node->setPosition(pos);
}

vector3df Wall::getPosition(void) const
{
    return (node->getPosition());
}
