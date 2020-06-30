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
#include <irrlicht.h>

#include "../Assets/Assets.hpp"
#include "../Irrlicht/Irrlicht.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class GameMap {
    public:
        GameMap(std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities, int width, int height, std::shared_ptr<Irrlicht> irr);
        ~GameMap();

        void initGround(std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities, std::shared_ptr<Irrlicht> irr);
        void initUnbreakableBlocks(std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities, std::shared_ptr<Irrlicht> irr);
        int removeNeighbour(int &i, int &j, int &missing);
        void removeRandomFromMap();
        void initBreakableBlocks(std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities, std::shared_ptr<Irrlicht> irr);

        std::vector<std::vector<std::shared_ptr<IEntity>>> &getMap(void);
        vector2di getMapSize(void) const;
        const std::vector<std::vector<std::shared_ptr<IEntity>>> &getGround() const;
    protected:
        int _height;
        int _width;
        int _nbCrates;
        std::vector<std::vector<std::shared_ptr<IEntity>>> _ground;
        std::vector<std::vector<std::shared_ptr<IEntity>>> _map;
};

#endif /* !MAP_HPP_ */
