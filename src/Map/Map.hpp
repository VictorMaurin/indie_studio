/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <memory>
#include "../Mesh/Mesh.hpp"
#include "../Breakable/Breakable.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Map {
    public:
        Map(std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities, int width, int height,
            ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device);
        ~Map();

        void removeRandomFromMap();
        int removeNeighbour(int &i, int &j, int &missing);
        std::vector<std::vector<std::shared_ptr<IEntity>>> getMap(void) const;
    protected:
        int height;
        int width;
        int nbCrates;
        std::vector<std::vector<std::shared_ptr<IEntity>>> ground;
        std::vector<std::vector<std::shared_ptr<IEntity>>> map;
};

#endif /* !MAP_HPP_ */
