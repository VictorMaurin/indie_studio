/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Breakable
*/

#ifndef BREAKABLE_HPP_
#define BREAKABLE_HPP_

#include <memory>
#include <irrlicht.h>

#include "../Mesh/Mesh.hpp"
#include "../Core/Core.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Breakable : public Mesh {
    public:
        Breakable(Core *core, ISceneManager *smgr, IVideoDriver *driver, std::shared_ptr<IrrlichtDevice> device);
        ~Breakable();

        void spawnPowerUp();
        bool isBreakable(void);
};

#endif /* !BREAKABLE_HPP_ */
