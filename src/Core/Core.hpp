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

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Core
{
private:
    bool is_ia;
    Scene _gameManager;
    int playersLeft=0;
    int indexLastPlayer=-1;
    int _fps;
    std::shared_ptr<Assets> _assets;
    std::shared_ptr<Irrlicht> _irr;

public : 
    Core(int fps=60);
    ~Core();
    void run();
    void init();
    bool isGameOver();
    void update();
    void draw();
    std::shared_ptr<Irrlicht> getLib(void) const;
};

#endif