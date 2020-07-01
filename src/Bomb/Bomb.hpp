/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#ifndef BOMB_HPP
#define BOMB_HPP

#include <irrlicht.h>

#include "../Irrlicht/Irrlicht.hpp"
#include "../Assets/Assets.hpp"
#include "../Mesh/Mesh.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Bomb : public Mesh
{
private:
    u32 now;
    u32 then;
    std::shared_ptr<Irrlicht> _irr;
    bool passed = false;
    vector3df posFloat;

public : 
    Bomb(std::shared_ptr<Irrlicht> irr, vector3df pos);
    ~Bomb();
    void SetIsAI(bool isAI){};
    void returnToGreen(std::shared_ptr<GameMap> map, std::string asset);
    void update(std::shared_ptr<GameMap> map, std::shared_ptr<Assets> assets);
    void killPlayers(int x, int z, std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> players);
    int breakMap(int x, int z, std::shared_ptr<GameMap> map);
    void explosionAnimation(int x, int z, std::shared_ptr<GameMap> map, std::string assetName);
    void explode(std::shared_ptr<GameMap> map, std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> players, std::string asset);
    bool isBreakable(void);
    void canCollide(bool);

    void setTexture(std::string assets) {};
};

#endif