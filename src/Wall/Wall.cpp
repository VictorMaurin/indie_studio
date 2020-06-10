#include <iostream>
#include "../assets/assets.hpp"
#include "Wall.hpp"

Wall::Wall(ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device)
{
    std::cout << GetCurrentWorkingDir("crate3.obj") << std::endl;
    mesh = smgr->getMesh(GetCurrentWorkingDir("crate3.obj").c_str());
    if (!mesh)
    {
        device->drop();
        throw "couldnt create wall mesh";
    }
    node = smgr->addMeshSceneNode(mesh);
    if (node)
    {
        node->setMaterialTexture( 0, driver->getTexture(GetCurrentWorkingDir("crate3.png").c_str()) );
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
    if (node)
        node->setPosition(pos);
}

vector3df Wall::getPosition(void) const
{
    if (node)
        return (node->getPosition());
    return(vector3df(0, 0, 0));
}

void Wall::setScale(const vector3df &scale)
{
    if (node)
        node->setScale(scale);
}

vector3df Wall::getScale(void) const
{
    if (node)
        return (node->getScale());
    return(vector3df(-1, -1, -1));
}