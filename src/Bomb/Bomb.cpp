/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(std::shared_ptr<Irrlicht> irr, vector3df pos) : Mesh("bomb2.obj", "bombbody_BaseColor.png", irr)
{
    if (!irr || !irr.get())
        throw MyException("unexpected argument", "Bomb.cpp", 13, "Bomb::ctor()");
    _irr = irr;
    this->setPosition(pos);
    posFloat.X = (int)pos.X;
    posFloat.Y = (int)pos.Y;
    posFloat.Z = (int)pos.Z;
    then = _irr->getDevice()->getTimer()->getRealTime();
    this->setPosition(posFloat);
}

Bomb::~Bomb()
{
}

void Bomb::returnToGreen(std::shared_ptr<GameMap> map, std::string asset)
{
    // X axis
    for (int x = -2; x <= 2; x++) {
        if ((int)posFloat.X + x >= -(int)(map->getMapSize().X / 2) && (int)posFloat.X + x <= (int)(map->getMapSize().X / 2)) {
            // change ground color
            map->getGround().at((int)posFloat.Z + int(map->getMapSize().Y / 2)).at((int)posFloat.X + x + int(map->getMapSize().X / 2))->setTexture(asset);
        }
    }
    // Z axis
    for (int z = -2; z <= 2; z++) {
        if ((int)posFloat.Z + z >= -(int)(map->getMapSize().Y / 2) && (int)posFloat.Z + z <= (int)(map->getMapSize().Y / 2)) {
            // change ground color
            map->getGround().at((int)posFloat.Z + z + int(map->getMapSize().Y / 2)).at((int)posFloat.X + int(map->getMapSize().X / 2))->setTexture(asset);
        }
    }
}

void Bomb::killPlayers(int x, int z, std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> players)
{
    for (int i = 0; i < players->size(); i++) {
        if (players->at(i) != NULL && x == (int)players->at(i)->getPosition().X && z == (int)players->at(i)->getPosition().Z) {
            players->at(i)->remove();
            players->at(i).reset();
        }
    }
}

int Bomb::breakMap(int x, int z, std::shared_ptr<GameMap> map)
{
    if (map->getMap().at( z + int(map->getMapSize().Y / 2) ).at( x + int(map->getMapSize().X / 2) ) != NULL &&
        map->getMap().at( z + int(map->getMapSize().Y / 2) ).at( x + int(map->getMapSize().X / 2) )->isBreakable() ) {
        map->getMap().at( z + int(map->getMapSize().Y / 2) ).at( x + int(map->getMapSize().X / 2) )->remove();
        map->getMap().at( z + int(map->getMapSize().Y / 2) ).at( x + int(map->getMapSize().X / 2) ).reset();
        return (1);
    } else if (map->getMap().at( z + int(map->getMapSize().Y / 2) ).at( x + int(map->getMapSize().X / 2) ) != NULL &&
               map->getMap().at( z + int(map->getMapSize().Y / 2) ).at( x + int(map->getMapSize().X / 2) )->isBreakable() == false )
        return (1);
    return (0);
}

void Bomb::explosionAnimation(int x, int z, std::shared_ptr<GameMap> map, std::string assetName)
{
    map->getGround().at( z + int(map->getMapSize().Y / 2) ).at( x + int(map->getMapSize().X / 2) )->setTexture(assetName);
}

void Bomb::explode(std::shared_ptr<GameMap> map, std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> players, std::string asset)
{
    // It is mandatory to have each axis two times ( one for the negative part and one for the positive part )
    // to make things easier if we want to avoid exploding the second block if the first one isnt breakable

    // explode on X axis left side
    for (int x = -1; x >= -2; x--)
    {
        if ((int)posFloat.X + x >= -(int)(map->getMapSize().X / 2) && (int)posFloat.X + x <= (int)(map->getMapSize().X / 2)) {
            // kill player (if any)
            killPlayers((int)posFloat.X + x, (int)posFloat.Z, players);
            // destroy breakable, if there is one
            if (breakMap((int)posFloat.X + x, (int)posFloat.Z, map) == 1)
                break;
            // change ground color
            explosionAnimation((int)posFloat.X + x, (int)posFloat.Z, map, asset);
        }
    }
    // explode on X axis right side
    for (int x = 0; x <= 2; x++)
    {
        if ((int)posFloat.X + x >= -(int)(map->getMapSize().X / 2) && (int)posFloat.X + x <= (int)(map->getMapSize().X / 2)) {
            // kill player (if any)
            killPlayers((int)posFloat.X + x, (int)posFloat.Z, players);
            // destroy breakable, if there is one
            if (breakMap((int)posFloat.X + x, (int)posFloat.Z, map))
                break;
            // change ground color
            explosionAnimation((int)posFloat.X + x, (int)posFloat.Z, map, asset);
        }
    }
    // explode on Z axis up
    for (int z = 1; z <= 2; z++)
    {
        if ((int)posFloat.Z + z >= -(int)(map->getMapSize().Y / 2) && (int)posFloat.Z + z <= (int)(map->getMapSize().Y / 2)) {
            // kill player (if any)
            killPlayers((int)posFloat.X, (int)posFloat.Z + z, players);
            // destroy breakable, if there is one
            if (breakMap((int)posFloat.X, (int)posFloat.Z + z, map))
                break;
            // change ground color
            explosionAnimation((int)posFloat.X, (int)posFloat.Z + z, map, asset);
        }
    }
    // explode on Z axis down
    for (int z = -1; z >= -2; z--)
    {
        if ((int)posFloat.Z + z >= -(int)(map->getMapSize().Y / 2) && (int)posFloat.Z + z <= (int)(map->getMapSize().Y / 2)) {
            // kill player (if any)
            killPlayers((int)posFloat.X, (int)posFloat.Z + z, players);
            // destroy breakable, if there is one
            if (breakMap((int)posFloat.X, (int)posFloat.Z + z, map))
                break;
            // change ground color
            explosionAnimation((int)posFloat.X, (int)posFloat.Z + z, map, asset);
        }
    }
}

void Bomb::update(std::shared_ptr<Assets> assets)
{
    if (!assets || !assets.get())
        throw MyException("unexpected argument", "Bomb.cpp", 135, "Bomb::update()");
    now = _irr->getDevice()->getTimer()->getRealTime();
    if ((now - then) / 1000 >= 3 && passed == false) {
        passed = true;
        // mesh->remove();
        this->remove();
    } else if ((now - then) / 1000 >= 3 && (now - then) / 1000.0f < 3.4f) {
        explode(assets->getMap(), assets->getPlayers(), "grasseRed.jpg");
    } if ((now - then) / 1000.0f >= 3.4f) {
        returnToGreen(assets->getMap(), "grass.jpg");
    }
}

bool Bomb::isBreakable()
{
    return (true);
}