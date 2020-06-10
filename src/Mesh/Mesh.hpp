/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Mesh
*/

#ifndef MESH_HPP_
#define MESH_HPP_

#include <irrlicht.h>
#include <memory>
#include "../Entity/IEntity.hpp"
#include "../assets/assets.hpp"
#include "../Core/Core.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Mesh : public IEntity
{
    public:
        Mesh(std::string meshName, std::string textureName, ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device);
        ~Mesh();
        void update(void);
        void draw(void) const;

        void setPosition(const vector3df &pos);
        vector3df getPosition(void) const;
        void setScale(const vector3df &scale);
        vector3df getScale(void) const;

    private:
        IMesh *mesh;
        IMeshSceneNode *node;
};

#endif /* !MESH_HPP_ */
