/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Mesh
*/

#ifndef MESH_HPP_
#define MESH_HPP_

class Mesh;

#include <memory>
#include <irrlicht.h>

#include "../assets/assets.hpp"
#include "../Core/Core.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

enum
{
    // I use this ISceneNode ID to indicate a scene node that is
    // not pickable by getSceneNodeAndCollisionPointFromRay()
    ID_IsNotPickable = 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be picked by ray selection.
    IDFlag_IsPickable = 1 << 0,
};

class Mesh : public IEntity
{
    public:
        Mesh(std::string meshName, std::string textureName, Core *core, ISceneManager *smgr, IVideoDriver *driver, std::shared_ptr<IrrlichtDevice> device);
        ~Mesh();
        void update();
        void draw(void) const;

        void remove(void);
        bool isBreakable(void);
        void setPosition(const vector3df &pos);
        void canCollide(bool);

        void setTexture(std::string assets);
        vector3df getPosition(void) const;
        void setScale(const vector3df &scale);
        vector3df getScale(void) const;
        std::shared_ptr<IMesh> getMesh() const;
        void SetIsAI(bool isAI) {};
        std::shared_ptr<IMeshSceneNode> getNode() const;
        bool isRemove = false;

    protected:
        std::shared_ptr<Core> core;
        std::shared_ptr<IMesh> mesh;
        std::shared_ptr<IMeshSceneNode> node;
};

#endif /* !MESH_HPP_ */
