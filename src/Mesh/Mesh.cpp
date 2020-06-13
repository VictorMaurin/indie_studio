/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Mesh
*/

#include "Mesh.hpp"

Mesh::Mesh(std::string meshName, std::string textureName, Core *core_param, ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device)
{
    this->core = core_param;
    mesh = core->getSmgr()->getMesh(findAsset(meshName).c_str());
    if (!mesh)
    {
        core->getDevice()->drop();
        throw "couldnt create wall mesh";
    }
    node = core->getSmgr()->addMeshSceneNode(mesh);
    if (node)
    {
        node->setMaterialTexture( 0, driver->getTexture(findAsset(textureName).c_str()) );
        // node->setScale(vector3d<float>(30.0f, 30.0f, 30.0f));
        // ISceneNodeAnimator* anim = smgr->createRotationAnimator(vector3df(0,0.1f,0));
        // node->addAnimator(anim);
        // anim->drop();
    }
}

Mesh::~Mesh()
{
    // node->drop();
    // mesh->drop();
    // node->remove();
    // delete node;
    // delete mesh;
}

void Mesh::update(std::shared_ptr<GameMap> map)
{
}

void Mesh::draw(void) const
{
}

bool Mesh::isBreakable(void)
{
    return (false);
}

void Mesh::remove(void)
{
    if (node) {
        node->remove();
    }
}

void Mesh::canCollide(bool b)
{
    ITriangleSelector *selector = 0;

    selector = core->getSmgr()->createTriangleSelector(this->mesh, this->node);
    this->node->setTriangleSelector(selector);
    selector->drop();
}

void Mesh::setPosition(const vector3df &pos)
{
    if (node)
        node->setPosition(pos);
}

vector3df Mesh::getPosition(void) const
{
    if (node)
        return (node->getPosition());
    return(vector3df(0, 0, 0));
}

void Mesh::setScale(const vector3df &scale)
{
    if (node)
        node->setScale(scale);
}

vector3df Mesh::getScale(void) const
{
    if (node)
        return (node->getScale());
    return(vector3df(-1, -1, -1));
}

irr::scene::IMesh *Mesh::getMesh() const
{
    return (mesh);
}

IMeshSceneNode *Mesh::getNode() const
{
    return (node);
}