/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#include "GameMap.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Breakable/Breakable.hpp"

GameMap::GameMap(std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities, int width, int height,
        std::shared_ptr<Core> core, std::shared_ptr<ISceneManager> smgr, std::shared_ptr<IVideoDriver> driver, std::shared_ptr<IrrlichtDevice> device)
{
    this->height = height;
    this->width = width;
    // init ground
    float xPos =  -(int)(width / 2);
    float zPos = -(int)(height / 2);
    this->ground = std::vector<std::vector<std::shared_ptr<IEntity>>>(height, std::vector<std::shared_ptr<IEntity>>(width));
    for (size_t i = 0; i < height; i++) {
        xPos = -(int)(width / 2);
        for (size_t j = 0; j < width; j++) {
            this->ground[i][j] = std::make_shared<Mesh>("tile.obj", "grass.jpg", core, smgr, driver, device);
            this->ground[i][j]->setPosition(vector3df(xPos, 0.0f, zPos));
            entities->push_back(this->ground[i][j]);

            xPos += 1;
        }
        zPos += 1;
    }
    // init unbreakable blocks
    xPos =  -(int)(width / 2);
    zPos = -(int)(height / 2);
    this->map = std::vector<std::vector<std::shared_ptr<IEntity>>>(height, std::vector<std::shared_ptr<IEntity>>(width));
    for (size_t i = 0; i < height; i++) {
        xPos = -(int)(width / 2);
        for (size_t j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1 || //borders
            (i % 2 == 0 && j % 2 == 0)) {//inside map
                this->map[i][j] = std::make_shared<Mesh>("block.obj", "block.png", core, smgr, driver, device);
                this->map[i][j]->setPosition(vector3df(xPos, 0.0f, zPos));
                this->map[i][j]->canCollide(true);
                entities->push_back(this->map[i][j]);
            }
            xPos += 1;
        }
        zPos += 1;
    }
    //init breakables
    xPos =  -(int)(width / 2);
    zPos = -(int)(height / 2);
    for (size_t i = 0; i < height; i++) {
        xPos = -(int)(width / 2);
        for (size_t j = 0; j < width; j++) {
            if (this->map[i][j] == 0) {
                if ((i > 2 && i < height - 3) || (j > 2 && j < width - 3)) {
                    nbCrates++;
                    this->map[i][j] = std::make_shared<Breakable>(core, smgr, driver, device);
                    this->map[i][j]->setScale(vector3df(0.85f, 0.85f, 0.85f));
                    this->map[i][j]->setPosition(vector3df(xPos, -0.15f, zPos));
                    this->map[i][j]->canCollide(true);
                    entities->push_back(this->map[i][j]);
                }
            }
            xPos += 1;
        }
        zPos += 1;
    }
    //remove some crates
    this->removeRandomFromMap();
}

GameMap::~GameMap()
{
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

    if (missing == 0 || (
       (((i - 1) % 2 == 0 && j % 2 == 0) || ((i - 1 == 0 || i - 1 == height - 1) && (j == 0 || j != width - 1)) || this->map[i - 1][j] == 0) &&
       (((i + 1) % 2 == 0 && j % 2 == 0) || ((i + 1 == 0 || i + 1 == height - 1) && (j == 0 || j != width - 1)) || this->map[i + 1][j] == 0) &&
       ((i % 2 == 0 && (j - 1) % 2 == 0) || ((i == 0 || i == height - 1) && (j - 1 == 0 || j - 1 != width - 1)) || this->map[i][j - 1] == 0) &&
       ((i % 2 == 0 && (j + 1) % 2 == 0) || ((i == 0 || i == height - 1) && (j + 1 == 0 || j + 1 != width - 1)) || this->map[i][j + 1] == 0))) {
        return (0);
    }
    dir = pickDirection();
    while (this->map[i + dir.X][j + dir.Y] == 0 ||
          ((i + dir.X) % 2 == 0 && (j + dir.Y) % 2 == 0) ||
          (i + dir.X <= 0 || i + dir.X >= height - 1) || (j + dir.Y <= 0 || j + dir.Y >= width - 1)) {
        dir = pickDirection();
    }
    i += dir.X;
    j += dir.Y;
    // vector3df meshPos = this->map[i][j]->getPosition();
    // meshPos.Y -= 2;
    // this->map[i][j]->setPosition(meshPos);
    this->map[i][j]->remove();
    this->map[i][j].reset();
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
        i = rand() % height;
        j = rand() % width;
        if (this->map[i][j] != 0 && ((i > 2 && i < height - 3) || (j > 2 && j < width - 3)) &&    //avoid spawn points
            (i % 2 != 0 && j % 2 != 0) &&                               //avoid inner unbreakable blocks
            i != 0 && i != height - 1 && j != 0 && j != width - 1) {    //avoid walls
            // vector3df meshPos = this->map[i][j]->getPosition();
            // meshPos.Y -= 2;
            // this->map[i][j]->setPosition(meshPos);
            this->map[i][j]->remove();
            this->map[i][j].reset();
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

std::vector<std::vector<std::shared_ptr<IEntity>>> &GameMap::getMap(void)
{
    return (this->map);
}

vector2di GameMap::getMapSize(void) const
{
    return (vector2di(this->width, this->height));
}

const std::vector<std::vector<std::shared_ptr<IEntity>>> &GameMap::getGround() const
{
    return (this->ground);
}