/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IEntity
*/

#ifndef IENTITY_HPP
#define IENTITY_HPP

class GameMap;

#include <vector>
#include <irrlicht.h>
#include <string>

#include "../Map/GameMap.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class IEntity
{
public:
    virtual ~IEntity() = default;

    virtual void update(std::shared_ptr<GameMap> map)=0;
    virtual void draw(void) const = 0;

    virtual void remove(void)=0;
    virtual bool isBreakable(void)=0;
    virtual void canCollide(bool)=0;
    virtual void SetIsAI(bool isAI)=0;

    virtual void setPosition(const irr::core::vector3df &pos)=0;
    virtual irr::core::vector3df getPosition(void) const = 0;
    virtual void setScale(const irr::core::vector3df &scale)=0;
    virtual irr::core::vector3df getScale(void) const = 0;
    virtual void setTexture(std::string assets) = 0;
};

#endif /* IENTITY_HPP */