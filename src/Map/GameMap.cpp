/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#include "GameMap.hpp"
#include "../Breakable/Breakable.hpp"
#include "../Mesh/Mesh.hpp"

GameMap::GameMap(std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities, int width, int height, std::shared_ptr<Irrlicht> irr)
{
    if (!entities || !irr || !irr.get() || width <= 2 || height <= 2)
        throw MyException("unexpected argument", "GameMap.cpp", 15, "GameMap::ctor()");
    this->_height = height;
    this->_width = width;

    initGround(entities, irr);
    initUnbreakableBlocks(entities, irr);
    initBreakableBlocks(entities, irr);
}

GameMap::~GameMap()
{
}

void GameMap::initGround(std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities, std::shared_ptr<Irrlicht> irr)
{
    float xPos =  -(int)(_width / 2);
    float zPos = -(int)(_height / 2);

    this->_ground = std::vector<std::vector<std::shared_ptr<IEntity>>>(_height, std::vector<std::shared_ptr<IEntity>>(_width));
    for (size_t i = 0; i < _height; i++) {
        xPos = -(int)(_width / 2);
        for (size_t j = 0; j < _width; j++) {
            try {
                this->_ground[i][j] = std::make_shared<Mesh>("tile.obj", "grass.jpg", irr);
                this->_ground[i][j]->setPosition(vector3df(xPos, 0.0f, zPos));
                entities->push_back(this->_ground[i][j]);
                if (!_ground[i][j] || !_ground[i][j].get() || !entities->at(entities->size() - 1))
                    throw MyException("couldn't create ground", "GameMap.cpp", 40, "GameMap::initGround()");
            } catch(const std::exception& e) {
                std::cerr << e.what() << '\n';
            }
            xPos += 1;
        }
        zPos += 1;
    }
}

void GameMap::initUnbreakableBlocks(std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities, std::shared_ptr<Irrlicht> irr)
{
    float xPos =  -(int)(_width / 2);
    float zPos = -(int)(_height / 2);

    this->_map = std::vector<std::vector<std::shared_ptr<IEntity>>>(_height, std::vector<std::shared_ptr<IEntity>>(_width));
    for (size_t i = 0; i < _height; i++) {
        xPos = -(int)(_width / 2);
        for (size_t j = 0; j < _width; j++) {
            if (i == 0 || i == _height - 1 || j == 0 || j == _width - 1 || //borders
            (i % 2 == 0 && j % 2 == 0)) {//inside _map
                this->_map[i][j] = std::make_shared<Mesh>("block.obj", "block.png", irr);
                entities->push_back(this->_map[i][j]);
                if (!_map[i][j] || !_map[i][j].get() || !entities->at(entities->size() - 1))
                    throw MyException("couldn't create map", "GameMap.cpp", 62, "GameMap::initUnbreakableBlocks()");
                this->_map[i][j]->setPosition(vector3df(xPos, 0.0f, zPos));
                this->_map[i][j]->canCollide(true);
            }
            xPos += 1;
        }
        zPos += 1;
    }
}

vector2di pickDirection()
{
    vector2di dir = vector2di(0, 0);

    while (abs(dir.X) == abs(dir.Y)) {
        dir.X = rand() % 3 + (-1);
        dir.Y = rand() % 3 + (-1);
    }
    return (dir);
}

int GameMap::removeNeighbour(int &i, int &j, int &missing)
{
    vector2di dir;

    // if all blocks around have already been removed / arnt removable (walls) -> return
    if (missing == 0 || (
       (((i - 1) % 2 == 0 && j % 2 == 0) || ((i - 1 == 0 || i - 1 == _height - 1) && (j == 0 || j != _width - 1)) || this->_map[i - 1][j] == 0) &&
       (((i + 1) % 2 == 0 && j % 2 == 0) || ((i + 1 == 0 || i + 1 == _height - 1) && (j == 0 || j != _width - 1)) || this->_map[i + 1][j] == 0) &&
       ((i % 2 == 0 && (j - 1) % 2 == 0) || ((i == 0 || i == _height - 1) && (j - 1 == 0 || j - 1 != _width - 1)) || this->_map[i][j - 1] == 0) &&
       ((i % 2 == 0 && (j + 1) % 2 == 0) || ((i == 0 || i == _height - 1) && (j + 1 == 0 || j + 1 != _width - 1)) || this->_map[i][j + 1] == 0))) {
        return (0);
    }
    dir = pickDirection();
    // pick a new random nearby cell while the previously chosen cell doesnt contain a breakable block
    while (this->_map[i + dir.X][j + dir.Y] == 0 ||
          ((i + dir.X) % 2 == 0 && (j + dir.Y) % 2 == 0) ||
          (i + dir.X <= 0 || i + dir.X >= _height - 1) || (j + dir.Y <= 0 || j + dir.Y >= _width - 1)) {
        dir = pickDirection();
    }
    // remove chosen breakable block
    i += dir.X;
    j += dir.Y;
    this->_map[i][j]->remove();
    this->_map[i][j].reset();
    missing--;
    return (1);
}

void GameMap::removeRandomFromMap(void)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
    int remove = 36;
    int doRemoveNeighbour = 0;

    while (remove > 0) {
        i = rand() % _height;
        j = rand() % _width;
        // if the _map at position (j, i) contains a breakable block -> remove it
        if (this->_map[i][j] != 0 && ((i > 2 && i < _height - 3) || (j > 2 && j < _width - 3)) &&   // avoid spawn points
            (i % 2 != 0 && j % 2 != 0) &&                                                           // avoid inner unbreakable blocks
            i != 0 && i != _height - 1 && j != 0 && j != _width - 1) {                              // avoid walls
            this->_map[i][j]->remove();
            this->_map[i][j].reset();
            remove--;
            x = i;
            y = j;
            while ((doRemoveNeighbour = rand() % 2)) {
                if (!this->removeNeighbour(x, y, remove))
                    break;
            }
        }
    }
}

void GameMap::initBreakableBlocks(std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities, std::shared_ptr<Irrlicht> irr)
{
    float xPos =  -(int)(_width / 2);
    float zPos = -(int)(_height / 2);

    // iterate through the map
    for (size_t i = 0; i < _height; i++) {
        xPos = -(int)(_width / 2);
        for (size_t j = 0; j < _width; j++) {
            // place a breakable block if tge current cell is empty and not a spawn point
            if (this->_map[i][j] == 0) {
                if ((i > 2 && i < _height - 3) || (j > 2 && j < _width - 3)) {
                    this->_map[i][j] = std::make_shared<Breakable>(irr);
                    entities->push_back(this->_map[i][j]);
                    if (!_map[i][j] || !_map[i][j].get() || !entities->at(entities->size() - 1))
                        throw MyException("couldn't create map", "GameMap.cpp", 157, "GameMap::initBreakableBlocks()");
                    this->_map[i][j]->setScale(vector3df(0.85f, 0.85f, 0.85f));
                    this->_map[i][j]->setPosition(vector3df(xPos, -0.15f, zPos));
                    this->_map[i][j]->canCollide(true);
                }
            }
            xPos += 1;
        }
        zPos += 1;
    }
    this->removeRandomFromMap();
}

std::vector<std::vector<std::shared_ptr<IEntity>>> &GameMap::getMap(void)
{
    return (this->_map);
}

vector2di GameMap::getMapSize(void) const
{
    return (vector2di(this->_width, this->_height));
}

const std::vector<std::vector<std::shared_ptr<IEntity>>> &GameMap::getGround() const
{
    return (this->_ground);
}