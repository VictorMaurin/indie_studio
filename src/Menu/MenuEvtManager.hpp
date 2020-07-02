/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MenuEvtManager
*/

#ifndef MENUEVTMANAGER_HPP_
#define MENUEVTMANAGER_HPP_

#include <memory>
#include "Menu.hpp"
#include "../Event/Event.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class MyEvent : public IEventReceiver
{
public:
	MyEvent(std::shared_ptr<Assets> assets, IGUIWindow* window, std::map<std::string, IGUIButton*> button, IGUIImage* image, IGUIStaticText* text, std::shared_ptr<Irrlicht> irr, Menu *gameMenu);
	bool OnEvent(const SEvent& event);

    private:
        std::shared_ptr<Assets> _assets;
        std::shared_ptr<Irrlicht> _irr;
        IVideoDriver *driver;
        ISceneManager *smgr;
        IGUIEnvironment *guienv;
        std::shared_ptr<IrrlichtDevice> device;
        std::map<std::string, IGUIButton*> _button;
        IGUIButton* _ia;
        IGUIButton* _player;
        IGUIButton* _help;
        IGUIButton* _quit;
        IGUIButton* _return;
        IGUIImage* _image;
        IGUIImage* image_help;
        IGUIWindow* win;
        IGUIStaticText* _text;
        Menu *_gameMenu;
};

#endif /* !MENUEVTMANAGER_HPP_ */
