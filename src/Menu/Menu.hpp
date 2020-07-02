/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Menu
*/

#ifndef MENU_HPP
#define MENU_HPP

class MyEvent;
class Scene;

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include "MenuEvtManager.hpp"
#include "Scene/Scene.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

enum
{
	QUIT_BUTTON = 101,
	IA_BUTTON,
    PLAYER_BUTTON,
    HELP_BUTTON,
    RETURN_BUTTON
};

class Menu
{
    private:
        std::shared_ptr<MyEvent> receiver;
        std::shared_ptr<Irrlicht> _irr;
        std::map<std::string, IGUIButton*> button;
        IGUIImage* image;
        IGUIWindow* window;
        IGUIStaticText* text;
        s32	counter;
        Scene *_gameManager;
    public :
        Menu(std::shared_ptr<Irrlicht> irr, Scene *gameManager);
        ~Menu();
        void create(std::shared_ptr<Assets> assets, std::shared_ptr<Irrlicht> irr);
        void createWindow();
        void createButtons();
        void createImage();
        void createText();
        Scene *getGameManager(void) const;
};

#endif