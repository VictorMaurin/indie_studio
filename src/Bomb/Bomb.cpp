#include "Bomb.hpp"

Bomb::Bomb(Core *core, vector3df pos)
{
    _core = core;
    device = core->getDevice();
    driver = core->getDriver();
    smgr = core->getSmgr();
    mesh = std::make_unique<Mesh>(
        "bomb2.obj", "bombbody_BaseColor.png",
        core, smgr, driver, device);
    
    mesh->setPosition(pos);
    vector3di posInt;
    posInt.X = (int)pos.X;
    posInt.Y = (int)pos.Y;
    posInt.Z = (int)pos.Z;
    // posInt.X -= 2;
    posFloat.X = (float)posInt.X;
    posFloat.Y = (float)posInt.Y;
    posFloat.Z = (float)posInt.Z;
    // mesh->setScale(scale);
    then = device->getTimer()->getRealTime();
    mesh->setPosition(posFloat);
}

Bomb::~Bomb()
{
}

void Bomb::createExplodeCube()
{
    // _core->getEntities()->push_back(std::make_shared<Explosion>(this->_core, mesh->getPosition()));
}

void Bomb::returnToGreen(std::shared_ptr<GameMap> map, std::string asset)
{
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X + 1) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z + 1) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X - 1) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z - 1) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X + 2) + int((map->getMapSize().X / 2)) < map->getGround().size())
&& int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
    map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
    at(int(posFloat.X + 2) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z + 2) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z + 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X - 2) + int((map->getMapSize().X / 2)) < map->getGround().size())
&& int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
    map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
    at(int(posFloat.X - 2) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z - 2) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z - 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
    }
}

void Bomb::explode(std::shared_ptr<GameMap> map, std::string asset)
{
    bool checkXPlus = false;
    bool checkXMin = false;
    bool checkZPlus = false;
    bool checkZMin = false;
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        for (int i = 0; i < _core->getPlayers()->size(); i++) {
            if (_core->getPlayers()->at(i) != NULL && (int)posFloat.X == (int)_core->getPlayers()->at(i)->getPosition().X
            && (int)posFloat.Z == (int)_core->getPlayers()->at(i)->getPosition().Z) {
                _core->getPlayers()->at(i)->remove();
                _core->getPlayers()->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X + 1) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X + 1) + int((map->getMapSize().X / 2)) < map->getGround().size())
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
        for (int i = 0; i < _core->getPlayers()->size(); i++) {
            if (_core->getPlayers()->at(i) != NULL && (int)posFloat.X + 1 == (int)_core->getPlayers()->at(i)->getPosition().X
                && (int)posFloat.Z == (int)_core->getPlayers()->at(i)->getPosition().Z) {
                    _core->getPlayers()->at(i)->remove();
                    _core->getPlayers()->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z + 1) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
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
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (_core->getPlayers()->at(i) != NULL && (int)posFloat.X == (int)_core->getPlayers()->at(i)->getPosition().X && (int)posFloat.Z + 1 == (int)_core->getPlayers()->at(i)->getPosition().Z)
            {
                _core->getPlayers()->at(i)->remove();
                _core->getPlayers()->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X - 1) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X - 1) + int((map->getMapSize().X / 2)) < map->getGround().size())
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
        for (int i = 0; i < _core->getPlayers()->size(); i++) {
            if (_core->getPlayers()->at(i) != NULL && (int)posFloat.X - 1 == (int)_core->getPlayers()->at(i)->getPosition().X
                && (int)posFloat.Z == (int)_core->getPlayers()->at(i)->getPosition().Z) {
                    _core->getPlayers()->at(i)->remove();
                    _core->getPlayers()->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z - 1) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
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
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (_core->getPlayers()->at(i) != NULL && (int)posFloat.X == (int)_core->getPlayers()->at(i)->getPosition().X && (int)posFloat.Z - 1 == (int)_core->getPlayers()->at(i)->getPosition().Z)
            {
                _core->getPlayers()->at(i)->remove();
                _core->getPlayers()->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X + 2) + int((map->getMapSize().X / 2)) < map->getGround().size())
&& int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
    map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
    at(int(posFloat.X + 2) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X + 2) + int((map->getMapSize().X / 2)) < map->getGround().size())
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
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (checkXPlus == false && _core->getPlayers()->at(i) != NULL && (int)posFloat.X + 2 == (int)_core->getPlayers()->at(i)->getPosition().X && (int)posFloat.Z == (int)_core->getPlayers()->at(i)->getPosition().Z)
            {
                _core->getPlayers()->at(i)->remove();
                _core->getPlayers()->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z + 2) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z + 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
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
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (checkZPlus == false && _core->getPlayers()->at(i) != NULL && (int)posFloat.X == (int)_core->getPlayers()->at(i)->getPosition().X && (int)posFloat.Z + 2 == (int)_core->getPlayers()->at(i)->getPosition().Z)
            {
                _core->getPlayers()->at(i)->remove();
                _core->getPlayers()->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X - 2) + int((map->getMapSize().X / 2)) < map->getGround().size())
&& int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
    map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
    at(int(posFloat.X - 2) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X - 2) + int((map->getMapSize().X / 2)) < map->getGround().size())
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
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (checkXMin == false && _core->getPlayers()->at(i) != NULL && (int)posFloat.X - 2 == (int)_core->getPlayers()->at(i)->getPosition().X && (int)posFloat.Z == (int)_core->getPlayers()->at(i)->getPosition().Z)
            {
                _core->getPlayers()->at(i)->remove();
                _core->getPlayers()->at(i).reset();
            }
        }
    }
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z - 2) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z - 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
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
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (checkZMin == false && _core->getPlayers()->at(i) != NULL && (int)posFloat.X == (int)_core->getPlayers()->at(i)->getPosition().X && (int)posFloat.Z - 2 == (int)_core->getPlayers()->at(i)->getPosition().Z)
            {
                _core->getPlayers()->at(i)->remove();
                _core->getPlayers()->at(i).reset();
            }
        }
    }
    createExplodeCube();
}

void Bomb::update(std::shared_ptr<GameMap> map)
{
    now = device->getTimer()->getRealTime();
    // node->setScale(vector3df(0.01f, 0.01f, 0.01f));
    if ((now - then) / 1000 >= 3 && passed == false) {
        passed = true;
        mesh->remove();
    }
    else if ((now - then) / 1000 >= 3 && (now - then) / 1000 < 5) {
        explode(map, "grasseRed.jpg");
    }
    if ((now - then) / 1000 >= 5) {
        returnToGreen(map, "grass.jpg");
    }
}

void Bomb::draw(void) const
{
}

void Bomb::canCollide(bool b)
{

}

void Bomb::setPosition(const irr::core::vector3df &pos)
{
    node->setPosition(pos);
}

irr::core::vector3df Bomb::getPosition() const
{
    return (node->getPosition());
}

void Bomb::setScale(const irr::core::vector3df &scale)
{
    node->setScale(scale);
}

irr::core::vector3df Bomb::getScale() const
{
    return (node->getScale());
}

void Bomb::remove()
{
    mesh->remove();
}

bool Bomb::isBreakable()
{
    return (true);
}