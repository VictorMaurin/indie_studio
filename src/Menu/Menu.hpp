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
#include <map>
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
<<<<<<< HEAD
	MyEvent(Core *core, IGUIWindow* window, IGUIButton* quit, IGUIButton* ia, IGUIButton* player, IGUIButton* help, IGUIImage* image, IGUIStaticText* text) {
=======
	MyEvent(std::shared_ptr<Core> core, IGUIWindow* window, std::map<std::string, IGUIButton*> button, IGUIImage* image, IGUIStaticText* text) {
>>>>>>> ADD- map for management of buttons and different method to create
        _core = core;
        statement = core->getstatement();
        device = core->getDevice();
        driver = core->getDriver();
        smgr = core->getSmgr();
        guienv = core->getGUIenv();
        _button = button;
        _text = text;
        _image = image;
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
                        if (_button["quit"])
                            _button["quit"]->remove();
                        if (_button["ia"])
                            _button["ia"]->remove();
                        if (_button["player"])
                            _button["player"]->remove();
                        if (_button["help"])
                            _button["help"]->remove();
                        _image->remove();
                        _core->setstatement(State::GAME);
                        _core->set_ia(1, true);
					}
					return true;
                
                case PLAYER_BUTTON:
					{
					    if (win)
                            win->remove();
                        if (_button["quit"])
                            _button["quit"]->remove();
                        if (_button["ia"])
                            _button["ia"]->remove();
                        if (_button["player"])
                            _button["player"]->remove();
                        if (_button["help"])
                            _button["help"]->remove();
                        _image->remove();
                        _core->setstatement(State::GAME);
                        _core->set_ia(1, false);
					}
					return true;
                case HELP_BUTTON:
                    {
                        _button["quit"]->setVisible(false);
                        _button["ia"]->setVisible(false);
                        _button["player"]->setVisible(false);
                        _image->setVisible(false);
                        _button["help"]->setVisible(false);
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
                        _button["quit"]->setVisible(true);
                        _button["ia"]->setVisible(true);
                        _button["player"]->setVisible(true);
                        _button["help"]->setVisible(true);
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
<<<<<<< HEAD
        ISceneManager *smgr;
        IGUIEnvironment *guienv;
=======
        std::shared_ptr<ISceneManager> smgr;
        std::shared_ptr<IGUIEnvironment> guienv;
        std::map<std::string, IGUIButton*> _button;
>>>>>>> ADD- map for management of buttons and different method to create
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
<<<<<<< HEAD
        ISceneManager *smgr;
        IGUIEnvironment *guienv;
=======
        std::shared_ptr<ISceneManager> smgr;
        std::shared_ptr<IGUIEnvironment> guienv;
        std::map<std::string, IGUIButton*> button;
        IGUIImage* image;
>>>>>>> ADD- map for management of buttons and different method to create
        IGUIWindow* window;
        IGUIStaticText* text;
        s32	counter;
    public :
        Menu(Core *core);
        ~Menu();
        void create();
        void create_window();
        void create_buttons();
        void create_image();
        void create_text();
};

#endif