/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Core
*/

#ifndef CORE_HPP
#define CORE_HPP

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include <irrlicht.h>
#include <string>
#include <memory>

class Player;

#include "../Event/Event.hpp"
#include "../Entity/IEntity.hpp"
#include "../Player/Player.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

enum class State : int
{
    NOTHING,
    GAME,
    MENU,
    GAME_OVER
};

class Core
{
private:
    IVideoDriver *driver;
    ISceneManager *smgr;
    IGUIEnvironment *guienv;
    std::shared_ptr<IrrlichtDevice> device;
    std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities;
    State statement;
    std::shared_ptr<MyEventReceiver> eventReceiver;
    irr::core::array<irr::SJoystickInfo> joystickInfo;
    bool is_ia;
    std::shared_ptr<GameMap> map;
    std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> players;
    ISceneCollisionManager *collMan;
    IGUIFont *font;
    std::wstring gameOverStr;
    u32 gameOverTimerBgn;

public : 
    Core();
    ~Core();
    void run();
    void init();
    void initAssets();
    void deleteAssets();
    const std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> &getEntities() const;
    void set_menu();
    void set_game();
    void update_menu();
    void update_game();
    void update_gameOver();
    void setstatement(State is);
    void set_ia(int player_index, bool ia);
    void isGameOver();
    State getstatement();
    ISceneCollisionManager *getCollMan() const;
    std::shared_ptr<GameMap> getMap() const;
    IVideoDriver *getDriver() const;
    ISceneManager *getSmgr() const;
    std::shared_ptr<IrrlichtDevice> getDevice() const;
    IGUIEnvironment *getGUIenv() const;
    std::shared_ptr<MyEventReceiver> getEventreceiver();
    irr::core::array<irr::SJoystickInfo> getJoystickinfo();
    const std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> &getPlayers() const;
};

#endif

//check