/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Assets
*/

#ifndef ASSETS_HPP_
#define ASSETS_HPP_

class GameMap;
class Assets;

#include <vector>
#include <memory>
#include <irrlicht.h>
#include "../Irrlicht/Irrlicht.hpp"
#include "../Entity/IEntity.hpp"
#include "../Map/GameMap.hpp"
#include "../Player/Player.hpp"

class Assets {
    public:
        Assets(std::shared_ptr<Irrlicht> irr);
        ~Assets();

        void init();
        const std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> &getPlayers() const;
        std::shared_ptr<GameMap> getMap() const;
        const std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> &getEntities() const;
        IGUIFont *getFont();

    private:
        std::shared_ptr<Irrlicht> _irr;
        IGUIFont *_font;
        std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> _players;
        std::shared_ptr<GameMap> _map;
        std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> _entities;
        ILightSceneNode *_light;
};

#endif /* !ASSETS_HPP_ */
