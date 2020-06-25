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
    mesh = std::shared_ptr<IMesh>(smgr->getMesh(findAsset(meshName).c_str()));
    if (!mesh) {
        device->drop();
        throw "couldnt create wall mesh";
    }
    node = std::shared_ptr<IMeshSceneNode>(smgr->addMeshSceneNode(mesh.get(), 0, IDFlag_IsPickable));
    if (node) {
        node->setMaterialTexture( 0, driver->getTexture(findAsset(textureName).c_str()) );
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

void Mesh::update()
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
    // if (isRemove == false) {
    //     isRemove = true;
    node->remove();
    node.reset();
    // }
}

void Mesh::canCollide(bool canMeshCollide)
{
    std::unique_ptr<ITriangleSelector> selector = 0;
    if (canMeshCollide) {
        selector = std::unique_ptr<ITriangleSelector>(core->getSmgr()->createTriangleSelector(this->mesh.get(), this->node.get()));
        this->node->setTriangleSelector(selector.get());
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

std::shared_ptr<IMesh> Mesh::getMesh() const
{
    return (mesh);
}

std::shared_ptr<IMeshSceneNode> Mesh::getNode() const
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