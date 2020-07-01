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

#include "../Irrlicht/Irrlicht.hpp"
#include "../Assets/Assets.hpp"
#include "../Scene/Scene.hpp"
// #include "../Menu/Menu.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

// enum class State : int
// {
//     NOTHING,
//     GAME,
//     MENU,
//     GAME_OVER
// };

class Core
{
private:
    // State statement;
    bool is_ia;
    // std::wstring gameOverStr;
    // u32 gameOverTimerBgn;
    Scene _gameManager;
    int playersLeft=0;
    int indexLastPlayer=-1;

    std::shared_ptr<Assets> _assets;
    std::shared_ptr<Irrlicht> _irr;

public : 
    Core();
    ~Core();
    void run();
    void init();
    void initAssets();
    // void deleteAssets();
    // void set_menu();
    // void set_game();
    void update_menu();
    void update_game();
    // void update_gameOver();
    bool isGameOver();
    // void setstatement(State is);
    void set_ia(int player_index, bool ia);
    // State getstatement();
    std::shared_ptr<Irrlicht> getLib(void) const;
};

#endif