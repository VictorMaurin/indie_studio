#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include "../Mesh/Mesh.hpp"
#include "../Event/Event.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

enum
{
	QUIT_BUTTON = 101,
	GAME_BUTTON
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

class MyEvent : public IEventReceiver
{
public:
	MyEvent(Core *core, IGUIWindow *window) {
        this->window = window;
     };

	virtual bool OnEvent(const SEvent& event, Core *core, IGUIWindow* window)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			guienv = core->getGUIenv();
            driver = core->getDriver();
            device = core->getDevice();
            smgr = core->getSmgr();

			switch(event.GUIEvent.EventType) {
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case QUIT_BUTTON:
					device->closeDevice();
					return true;

				case GAME_BUTTON:
					{
					window->remove();
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
        IVideoDriver *driver;
        IrrlichtDevice *device;
        ISceneManager *smgr;
        IGUIEnvironment *guienv;
        IGUIListBox *listbox;
        IGUISkin* skin;
        IGUIWindow* window;
        s32	counter;
};

#endif