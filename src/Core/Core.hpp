#ifndef CORE_HPP
#define CORE_HPP

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include <irrlicht.h>
#include <string>

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
    IrrlichtDevice *device;
    std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities;
    State statement;
    MyEventReceiver *eventReceiver;
    irr::core::array<irr::SJoystickInfo> joystickInfo;
    bool is_ia;
    std::shared_ptr<GameMap> map;
    std::shared_ptr<std::vector<std::shared_ptr<Player>>> players;
    ISceneCollisionManager *collMan;
    IGUIFont *font;
    std::wstring gameOverStr;
    u32 gameOverTimerBgn;

public : 
    Core(/* args */);
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
    IVideoDriver *getDriver() const;
    ISceneManager *getSmgr() const;
    IrrlichtDevice *getDevice() const;
    IGUIEnvironment *getGUIenv() const;
    MyEventReceiver* getEventreceiver();
    irr::core::array<irr::SJoystickInfo> getJoystickinfo();
    const std::shared_ptr<std::vector<std::shared_ptr<Player>>> &getPlayers() const;
};

#endif