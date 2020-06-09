#include "Wall.hpp"
#include <iostream>

Wall::Wall(ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device) : AEntity()
{
    mesh = smgr->getMesh("/Users/paul/epitech/OOP_indie_studio_2019/crate/crate3.obj");
    if (!mesh)
    {
        device->drop();
        throw "couldnt create wall mesh";
    }
    node = smgr->addMeshSceneNode(mesh);
    if (node)
    {
        node->setMaterialTexture( 0, driver->getTexture("/Users/paul/epitech/OOP_indie_studio_2019/crate/crate3.png") );
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
