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
    IGUIButton* quit = guienv->addButton(rect<s32>(490,300,600,300 + 32), 0, QUIT_BUTTON,
			L"QUIT", L"Game Exit");
	IGUIButton* help = guienv->addButton(rect<s32>(370,300,480,300 + 32), 0, HELP_BUTTON,
			L"HELP", L"Help");
	IGUIButton* ia = guienv->addButton(rect<s32>(120,300,240,300 + 32), 0, IA_BUTTON,
			L"IA", L"Opponent is a player");
	IGUIButton* player = guienv->addButton(rect<s32>(250,300,360,300 + 32), 0, PLAYER_BUTTON,
			L"PLAYER", L"Opponent is a IA");
	IGUIStaticText* text = guienv->addStaticText(L"CHOOSE YOUR OPPONENT",
		rect<s32>(250,360,400,382), true, false, window);
    window->getCloseButton()->setVisible(false);
    MyEvent *receiver = new MyEvent(core, window, quit, ia, player, help, image, text);
	device->setEventReceiver(receiver);
}

Menu::~Menu()
{
}