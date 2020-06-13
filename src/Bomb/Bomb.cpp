#include "Bomb.hpp"

Bomb::Bomb(Core *core, vector3df pos)
{
    core = core;
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

void Bomb::explode(std::shared_ptr<GameMap> map, std::string asset)
{
    bool check = false;
    if ((int(posFloat.X) + int((map->getMapSize().X / 2)) < map->getGround().size())
    && int(posFloat.Z) + int((map->getMapSize().Y / 2)) < map->getGround().size()) {
        map->getGround().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->setTexture(asset);
        std::cout << "size players : " << _core->getPlayers()->size() << std::endl;
        for (int i = 0; i < _core->getPlayers()->size(); i++) {
            if (posFloat.X == _core->getPlayers()->at(i)->getPosition().X
            && posFloat.Z == _core->getPlayers()->at(i)->getPosition().Z) {
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
            check = true;
            map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 1) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < _core->getPlayers()->size(); i++) {
            if (posFloat.X + 1 == _core->getPlayers()->at(i)->getPosition().X
                && posFloat.Z == _core->getPlayers()->at(i)->getPosition().Z) {
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
            check = true;
            map->getMap().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z + 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (posFloat.X == _core->getPlayers()->at(i)->getPosition().X && posFloat.Z + 1 == _core->getPlayers()->at(i)->getPosition().Z)
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
            check = true;
            map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 1) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < _core->getPlayers()->size(); i++) {
            if (posFloat.X - 1 == _core->getPlayers()->at(i)->getPosition().X
                && posFloat.Z == _core->getPlayers()->at(i)->getPosition().Z) {
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
            check = true;
            map->getMap().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->remove();
            map->getMap().at(int(posFloat.Z - 1) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (posFloat.X == _core->getPlayers()->at(i)->getPosition().X && posFloat.Z - 1 == _core->getPlayers()->at(i)->getPosition().Z)
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
        && check == false) {
            map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 2) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X + 2) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (posFloat.X + 2 == _core->getPlayers()->at(i)->getPosition().X && posFloat.Z == _core->getPlayers()->at(i)->getPosition().Z)
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
        && check == false) {
            map->getMap().at(int(posFloat.Z + 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z + 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (posFloat.X == _core->getPlayers()->at(i)->getPosition().X && posFloat.Z + 2 == _core->getPlayers()->at(i)->getPosition().Z)
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
        && check == false) {
            map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 2) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X - 2) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (posFloat.X - 2 == _core->getPlayers()->at(i)->getPosition().X && posFloat.Z == _core->getPlayers()->at(i)->getPosition().Z)
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
        && check == false) {
            map->getMap().at(int(posFloat.Z - 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2)))->remove();
        map->getMap().at(int(posFloat.Z - 2) + int((map->getMapSize().Y / 2))).
        at(int(posFloat.X) + int((map->getMapSize().X / 2))).reset();
        }
        for (int i = 0; i < _core->getPlayers()->size(); i++)
        {
            if (posFloat.X == _core->getPlayers()->at(i)->getPosition().X && posFloat.Z - 2 == _core->getPlayers()->at(i)->getPosition().Z)
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
    else if ((now - then) / 1000 >= 3) {
        explode(map, "grasseRed.jpg");
    }
    if ((now - then) / 1000 >= 5) {
        explode(map, "grass.jpg");
    }
}

void Bomb::draw(void) const
{
}

void Bomb::canCollide(__attribute__((unused)) bool b)
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

}

bool Bomb::isBreakable()
{
    return (true);
}