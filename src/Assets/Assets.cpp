/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Assets
*/

#include "Assets.hpp"

Assets::Assets(std::shared_ptr<Irrlicht> irr)
{
    if (!irr || !irr.get())
        throw MyException("unexpected argument", "Assets.cpp", 13, "Assets::ctor()");
    _irr = irr;
    _font = _irr->getGUIenv()->getBuiltInFont();
    _light = _irr->getSmgr()->addLightSceneNode( 0, vector3df(0.0f,50.0f,2.0f), SColorf(1.0f,1.0f,1.0f,1.0f), 35.0f );

    _entities = std::make_shared<std::vector<std::shared_ptr<IEntity>>>();
    _players = std::make_shared<std::vector<std::shared_ptr<IEntity>>>();
}

Assets::~Assets()
{
}

void Assets::init()
{
    // create the map
    _map = std::make_shared<GameMap>(_entities, 19, 13, _irr);
    if (!_map || !_map.get())
        throw MyException("couldn't create map", "Assets.cpp", 28, "Assets::init()");

    // create 4 players and put them in each corners
    _entities->push_back(std::make_shared<Player>("Bomberman.MD3", "BlackBombermanTextures.png", _irr, irr::KEY_KEY_Z, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_KEY_D, irr::KEY_SPACE));
    _players->push_back(_entities->back());
    if (!_players->at(_players->size() - 1) || !_entities->at(_entities->size() - 1))
        throw MyException("couldn't create player", "Assets.cpp", 33, "Assets::init()");
    _entities->back()->setPosition(vector3df(-8.0f, 0.0f, -5.0f));

    _entities->push_back(std::make_shared<Player>("Bomberman.MD3", "WhiteBombermanTextures.png", _irr, irr::KEY_KEY_Y, irr::KEY_KEY_H, irr::KEY_KEY_G, irr::KEY_KEY_J, irr::KEY_KEY_L));
    _players->push_back(_entities->back());
    if (!_players->at(_players->size() - 1) || !_entities->at(_entities->size() - 1))
        throw MyException("couldn't create player", "Assets.cpp", 39, "Assets::init()");
    _entities->back()->setPosition(vector3df(-8.0f, 0.0f, 5.0f));
    
    _entities->push_back(std::make_shared<Player>("Bomberman.MD3", "RedBombermanTextures.png", _irr, irr::KEY_KEY_Y, irr::KEY_KEY_H, irr::KEY_KEY_G, irr::KEY_KEY_J, irr::KEY_KEY_L));
    _players->push_back(_entities->back());
    if (!_players->at(_players->size() - 1) || !_entities->at(_entities->size() - 1))
        throw MyException("couldn't create player", "Assets.cpp", 45, "Assets::init()");
    _entities->back()->setPosition(vector3df(8.0f, 0.0f, 5.0f));
    _entities->back()->SetIsAI(true);
    
    _entities->push_back(std::make_shared<Player>("Bomberman.MD3", "PinkBombermanTextures.png", _irr, irr::KEY_KEY_Y, irr::KEY_KEY_H, irr::KEY_KEY_G, irr::KEY_KEY_J, irr::KEY_KEY_L));
    _players->push_back(_entities->back());
    if (!_players->at(_players->size() - 1) || !_entities->at(_entities->size() - 1))
        throw MyException("couldn't create player", "Assets.cpp", 52, "Assets::init()");
    _entities->back()->setPosition(vector3df(8.0f, 0.0f, -5.0f));
    _entities->back()->SetIsAI(true);
}

void Assets::deleteAll(void)
{
    _players->clear();
    _players->shrink_to_fit();
    for (size_t i = 0; i < _entities->size(); i++) {
        if (_entities->at(i)) {
            _entities->at(i)->remove();
            _entities->at(i).reset();
        }
    }
    _entities->clear();
    _entities->shrink_to_fit();
    _map.reset();
}

void Assets::setAi(int playerIndex, bool isAi)
{
    _players->at(playerIndex)->SetIsAI(isAi);
}

const std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> &Assets::getPlayers() const
{
    return (this->_players);
}

std::shared_ptr<GameMap> Assets::getMap() const
{
    return (this->_map);
}

const std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> &Assets::getEntities() const
{
    return (this->_entities);
}

IGUIFont *Assets::getFont()
{
    return (this->_font);
}