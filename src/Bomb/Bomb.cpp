/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(std::shared_ptr<Irrlicht> irr, vector3df pos)
{
    _irr = irr;
    // device = irr->getDevice();
    // driver = irr->getDriver();
    // smgr = irr->getSmgr();
    mesh = std::make_unique<Mesh>("bomb2.obj", "bombbody_BaseColor.png", irr);
    
    mesh->setPosition(pos);
    vector3di posInt;
    posInt.X = (int)pos.X;
    posInt.Y = (int)pos.Y;
    posInt.Z = (int)pos.Z;
    posFloat.X = (float)posInt.X;
    posFloat.Y = (float)posInt.Y;
    posFloat.Z = (float)posInt.Z;
    then = _irr->getDevice()->getTimer()->getRealTime();
    mesh->setPosition(posFloat);
}

Bomb::~Bomb()
{
}

void Bomb::createExplodeCube()
{
    
}

void Bomb::returnToGreen(std::shared_ptr<GameMap> map, std::string asset)
{
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X + 1) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z + 1) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X - 1) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z - 1) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X + 2) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
&& int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
    map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
    at(int(posFloat.X + 2) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z + 2) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z + 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X - 2) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
&& int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
    map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
    at(int(posFloat.X - 2) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z - 2) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z - 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
}

void Bomb::explode(std::shared_ptr<GameMap> map, std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> players, std::string asset)
{
    bool checkXPlus = false;
    bool checkXMin = false;
    bool checkZPlus = false;
    bool checkZMin = false;
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        for (int i = 0; i < players->size(); i++) {
            if (players->at(i) != NULL && (int)posFloat.X == (int)players->at(i)->getPosition().X
            && (int)posFloat.Z == (int)players->at(i)->getPosition().Z) {
                players->at(i)->remove();
                players->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X + 1) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X + 1) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getMap().size()
    && map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2)))->isBreakable() == true
        ) {
            checkXPlus = true;
            map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2))).reset();
        }
        else if (map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2)))->isBreakable() == false) {
            checkXPlus = true;
        }
        for (int i = 0; i < players->size(); i++) {
            if (players->at(i) != NULL && (int)posFloat.X + 1 == (int)players->at(i)->getPosition().X
                && (int)posFloat.Z == (int)players->at(i)->getPosition().Z) {
                    players->at(i)->remove();
                    players->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z + 1) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z + 1) + int((map->getMapSize().Y / 2)) < map->getMap().size()
    && map->getMap().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->isBreakable() == true) {
            checkZPlus = true;
            map->getMap().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))).reset();
        }
        else if (map->getMap().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).at(int(posFloat.X) + int((map->getMapSize().X / 2)))->isBreakable() == false)
        {
            checkZPlus = true;
        }
        for (int i = 0; i < players->size(); i++)
        {
            if (players->at(i) != NULL && (int)posFloat.X == (int)players->at(i)->getPosition().X && (int)posFloat.Z + 1 == (int)players->at(i)->getPosition().Z)
            {
                players->at(i)->remove();
                players->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X - 1) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X - 1) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getMap().size()
    && map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2)))->isBreakable() == true) {
            checkXMin = true;
            map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2))).reset();
        }
        else if (map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).at(int(posFloat.X - 1) + int((map->getMapSize().X / 2)))->isBreakable() == false)
        {
            checkXMin = true;
        }
        for (int i = 0; i < players->size(); i++) {
            if (players->at(i) != NULL && (int)posFloat.X - 1 == (int)players->at(i)->getPosition().X
                && (int)posFloat.Z == (int)players->at(i)->getPosition().Z) {
                    players->at(i)->remove();
                    players->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z - 1) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z - 1) + int((map->getMapSize().Y / 2)) < map->getMap().size()
    && map->getMap().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->isBreakable() == true) {
            checkZMin = true;
            map->getMap().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->remove();
            map->getMap().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))).reset();
        }
        else if (map->getMap().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).at(int(posFloat.X) + int((map->getMapSize().X / 2)))->isBreakable() == false)
        {
            checkZMin = true;
        }
        for (int i = 0; i < players->size(); i++)
        {
            if (players->at(i) != NULL && (int)posFloat.X == (int)players->at(i)->getPosition().X && (int)posFloat.Z - 1 == (int)players->at(i)->getPosition().Z)
            {
                players->at(i)->remove();
                players->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X + 2) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
&& int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
    map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
    at(int(posFloat.X + 2) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X + 2) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getMap().size()
    && map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 2) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 2) + int((map->getMapSize().X / 2)))->isBreakable() == true
        && checkXPlus == false) {
            map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 2) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 2) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < players->size(); i++)
        {
            if (checkXPlus == false && players->at(i) != NULL && (int)posFloat.X + 2 == (int)players->at(i)->getPosition().X && (int)posFloat.Z == (int)players->at(i)->getPosition().Z)
            {
                players->at(i)->remove();
                players->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z + 2) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z + 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z + 2) + int((map->getMapSize().Y / 2)) < map->getMap().size()
    && map->getMap().at(int(posFloat.Z + 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z + 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->isBreakable() == true
        && checkZPlus == false) {
            map->getMap().at(int(posFloat.Z + 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z + 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < players->size(); i++)
        {
            if (checkZPlus == false && players->at(i) != NULL && (int)posFloat.X == (int)players->at(i)->getPosition().X && (int)posFloat.Z + 2 == (int)players->at(i)->getPosition().Z)
            {
                players->at(i)->remove();
                players->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X - 2) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
&& int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
    map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
    at(int(posFloat.X - 2) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X - 2) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getMap().size()
    && map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 2) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 2) + int((map->getMapSize().X / 2)))->isBreakable() == true
        && checkXMin == false) {
            map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 2) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 2) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < players->size(); i++)
        {
            if (checkXMin == false && players->at(i) != NULL && (int)posFloat.X - 2 == (int)players->at(i)->getPosition().X && (int)posFloat.Z == (int)players->at(i)->getPosition().Z)
            {
                players->at(i)->remove();
                players->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z - 2) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z - 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().at(0).size())
    && int(posFloat.Z - 2) + int((map->getMapSize().Y / 2)) < map->getMap().size()
    && map->getMap().at(int(posFloat.Z - 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))) != NULL && map->getMap().at(int(posFloat.Z - 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->isBreakable() == true
        && checkZMin == false) {
            map->getMap().at(int(posFloat.Z - 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z - 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < players->size(); i++)
        {
            if (checkZMin == false && players->at(i) != NULL && (int)posFloat.X == (int)players->at(i)->getPosition().X && (int)posFloat.Z - 2 == (int)players->at(i)->getPosition().Z)
            {
                players->at(i)->remove();
                players->at(i).reset();
            }
        }
    }
    createExplodeCube();
}

void Bomb::update(std::shared_ptr<GameMap> map, std::shared_ptr<Assets> assets)
{
    now = _irr->getDevice()->getTimer()->getRealTime();
    if ((now - then) / 1000 >= 3 && passed == false) {
        passed = true;
        mesh->remove();
    }
    else if ((now - then) / 1000 >= 3 && (now - then) / 1000 < 5) {
        explode(assets->getMap(), assets->getPlayers(), "grasseRed.jpg");
    }
    if ((now - then) / 1000 >= 5) {
        returnToGreen(map, "grass.jpg");
    }
}

void Bomb::canCollide(bool b)
{

}

void Bomb::setPosition(const irr::core::vector3df &pos)
{
    mesh->getNode()->setPosition(pos);
}

irr::core::vector3df Bomb::getPosition() const
{
    return (mesh->getNode()->getPosition());
}

void Bomb::setScale(const irr::core::vector3df &scale)
{
    mesh->getNode()->setScale(scale);
}

irr::core::vector3df Bomb::getScale() const
{
    return (mesh->getNode()->getScale());
}

void Bomb::remove()
{
    mesh->remove();
}

bool Bomb::isBreakable()
{
    return (true);
}