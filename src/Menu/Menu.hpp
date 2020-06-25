/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Menu
*/

#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include "../Core/Core.hpp"
#include "../Event/Event.hpp"

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

class MyEvent : public IEventReceiver
{
public:
	MyEvent(std::shared_ptr<Core> core, IGUIWindow* window, IGUIButton* quit, IGUIButton* ia, IGUIButton* player, IGUIButton* help, IGUIImage* image, IGUIStaticText* text) {
        _core = core;
        statement = core->getstatement();
        device = core->getDevice();
        driver = core->getDriver();
        smgr = core->getSmgr();
        guienv = core->getGUIenv();
        _ia = ia;
        _player = player;
        _text = text;
        _quit = quit;
        _image = image;
        _help = help;
        win = window;
    };

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();

			switch(event.GUIEvent.EventType) {
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case QUIT_BUTTON:
					device->closeDevice();
					return true;

				case IA_BUTTON:
					{
					    if (win)
                            win->remove();
                        if (_quit)
                            _quit->remove();
                        if (_ia)
                            _ia->remove();
                        if (_player)
                            _player->remove();
                        if (_help)
                            _help->remove();
                        _image->remove();
                        _core->setstatement(State::GAME);
                        _core->set_ia(1, true);
					}
					return true;
                case PLAYER_BUTTON:
					{
					    if (win)
                            win->remove();
                        if (_quit)
                            _quit->remove();
                        if (_ia)
                            _ia->remove();
                        if (_player)
                            _player->remove();
                        if (_help)
                            _help->remove();
                        _image->remove();
                        _core->setstatement(State::GAME);
                        _core->set_ia(1, false);
					}
					return true;
                case HELP_BUTTON:
                    {
                        _quit->setVisible(false);
                        _ia->setVisible(false);
                        _player->setVisible(false);
                        _image->setVisible(false);
                        _help->setVisible(false);
                        _text->setVisible(false);
                        image_help = guienv->addImage(driver->getTexture(findAsset("help.png").c_str()),
			position2d<int>(10,10));
                        _return = guienv->addButton(rect<s32>(490,440,600,440 + 32), 0, RETURN_BUTTON,
			L"RETURN", L"Return");
                    }
                    return (true);
                case RETURN_BUTTON:
                    {
                        _image->setVisible(true);
                        _quit->setVisible(true);
                        _ia->setVisible(true);
                        _player->setVisible(true);
                        _help->setVisible(true);
                        _text->setVisible(true);
                        _return->remove();
                        image_help->remove();
                    }
                    return (true);
				default:
					return false;
				}
				break;
			}
		}

		return false;
	}

    private:
        Core *_core;
        IVideoDriver *driver;
        std::shared_ptr<IrrlichtDevice> device;
        ISceneManager *smgr;
        IGUIEnvironment *guienv;
        IGUIButton* _ia;
        IGUIButton* _player;
        IGUIButton* _help;
        IGUIButton* _quit;
        IGUIButton* _return;
        IGUIImage* _image;
        IGUIImage* image_help;
        IGUIWindow* win;
        IGUIStaticText* _text;
        State statement;
};

class Menu
{
    private:
        IVideoDriver *driver;
        std::shared_ptr<IrrlichtDevice> device;
        ISceneManager *smgr;
        IGUIEnvironment *guienv;
        // IGUIListBox *listbox;
        // IGUISkin* skin;
        IGUIWindow* window;
        s32	counter;
    public :
        Menu(std::shared_ptr<Core> core);
        ~Menu();
};

#endif