#include "Menu.hpp"
#include "../../assets/assets.hpp"

Menu::Menu(Core *core)
{
    driver = core->getDriver();
    device = core->getDevice();
    smgr = core->getSmgr();
    guienv = core->getGUIenv();

	window = guienv->addWindow(
		rect<s32>(0, 0, 640, 480),
		false, L"												Menu window");
    IGUIImage* image = guienv->addImage(driver->getTexture(findAsset("bomberman.png").c_str()),
			position2d<int>(10,10));
    IGUIButton* quit = guienv->addButton(rect<s32>(370,300,480,300 + 32), 0, QUIT_BUTTON,
			L"Quit", L"Exits Program");
	IGUIButton* ia = guienv->addButton(rect<s32>(120,300,240,300 + 32), 0, IA_BUTTON,
			L"IA", L"Launches a new Window");
	IGUIButton* player = guienv->addButton(rect<s32>(250,300,360,300 + 32), 0, PLAYER_BUTTON,
			L"PLAYER", L"Launches a new Window");
	guienv->addStaticText(L"CHOOSE YOUR OPPONENT",
		rect<s32>(250,360,400,382), true, false, window);
    window->getCloseButton()->setVisible(false);
    MyEvent *receiver = new MyEvent(core, window, quit, ia, player, image);
	device->setEventReceiver(receiver);
}

Menu::~Menu()
{
}