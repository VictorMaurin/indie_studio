/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Mesh
*/

#include "Mesh.hpp"

Mesh::Mesh(std::string meshName, std::string textureName, Core *core_param, ISceneManager *smgr, IVideoDriver *driver, std::shared_ptr<IrrlichtDevice> device)
{
    this->core = core_param;
    mesh = core->getSmgr()->getMesh(findAsset(meshName).c_str());
    if (!mesh) {
        core->getDevice()->drop();
        throw "couldnt create wall mesh";
    }
    node = core->getSmgr()->addMeshSceneNode(mesh, 0, IDFlag_IsPickable);
    if (node) {
        node->setMaterialTexture( 0, driver->getTexture(findAsset(textureName).c_str()) );
    }
}

Mesh::~Mesh()
{
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
    if (isRemove == false) {
        isRemove = true;
        node->remove();
    }
}

void Mesh::canCollide(bool canMeshCollide)
{
    ITriangleSelector *selector = 0;
    if (canMeshCollide) {
        selector = core->getSmgr()->createTriangleSelector(this->mesh, this->node);
        this->node->setTriangleSelector(selector);
        selector->drop();
    }
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

void Mesh::setTexture(std::string assets)
{
    if (node)
    {
        node->setMaterialTexture(0, core->getDriver()->getTexture(findAsset(assets).c_str()));
    }
}