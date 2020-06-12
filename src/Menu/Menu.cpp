#include "Menu.hpp"

Menu::Menu(Core *core)
{
    driver = core->getDriver();
    device = core->getDevice();
    smgr = core->getSmgr();
    guienv = core->getGUIenv();

    guienv->addButton(rect<s32>(10,240,110,240 + 32), 0, QUIT_BUTTON,
			L"Quit", L"Exits Program");
	guienv->addButton(rect<s32>(10,280,110,280 + 32), 0, GAME_BUTTON,
			L"GAME", L"Launches a new Window");
	counter = 30;
	window = guienv->addWindow(
		rect<s32>(100 + counter, 100 + counter, 300 + counter, 200 + counter),
		false, L"Menu window");
	guienv->addStaticText(L"Please close me",
		rect<s32>(35,35,140,50), true, false, window);
    MyEvent receiver(core, window);
	device->setEventReceiver(&receiver);
}
