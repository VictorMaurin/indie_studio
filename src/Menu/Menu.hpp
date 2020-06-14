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
    PLAYER_BUTTON
};

class MyEvent : public IEventReceiver
{
public:
	MyEvent(Core *core, IGUIWindow* window, IGUIButton* quit, IGUIButton* ia, IGUIButton* player, IGUIImage* image) {
        _core = core;
        statement = core->getstatement();
        device = core->getDevice();
        driver = core->getDriver();
        smgr = core->getSmgr();
        guienv = core->getGUIenv();
        _ia = ia;
        _player = player;
        _quit = quit;
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
                        if (_quit)
                            _quit->remove();
                        if (_ia)
                            _ia->remove();
                        if (_player)
                            _player->remove();
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
                        _image->remove();
                        _core->setstatement(State::GAME);
                        _core->set_ia(1, false);
					}
					return true;
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
        IrrlichtDevice *device;
        ISceneManager *smgr;
        IGUIEnvironment *guienv;
        IGUIButton* _ia;
        IGUIButton* _player;
        IGUIButton* _quit;
        IGUIImage* _image;
        IGUIWindow* win;
        State statement;
};

class Menu
{
    private:
        IVideoDriver *driver;
        IrrlichtDevice *device;
        ISceneManager *smgr;
        IGUIEnvironment *guienv;
        IGUIListBox *listbox;
        IGUISkin* skin;
        IGUIWindow* window;
        s32	counter;
    public :
        Menu(Core *core);
        ~Menu();
};

#endif