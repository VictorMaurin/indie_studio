/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Menu
*/

#include "Menu.hpp"
#include "../../assets/assets.hpp"

Menu::Menu(Core *core)
{
    driver = core->getDriver();
    device = core->getDevice();
    smgr = core->getSmgr();
    guienv = core->getGUIenv();
    
    IGUIButton* quit = guienv->addButton(rect<s32>(490,300,600,300 + 32), 0, QUIT_BUTTON,
			L"QUIT", L"Game Exit");
	IGUIButton* help = guienv->addButton(rect<s32>(370,300,480,300 + 32), 0, HELP_BUTTON,
			L"HELP", L"Help");
	IGUIButton* ia = guienv->addButton(rect<s32>(120,300,240,300 + 32), 0, IA_BUTTON,
			L"IA", L"Opponent is a player");
	IGUIButton* player = guienv->addButton(rect<s32>(250,300,360,300 + 32), 0, PLAYER_BUTTON,
			L"PLAYER", L"Opponent is a IA");
    MyEvent *receiver = new MyEvent(core, window, button, image, text);
	device->setEventReceiver(receiver);
}

Menu::~Menu()
{
}

void Menu::create()
{
	this->create_window();
	this->create_buttons();
	this->create_image();
	this->create_text();
}

void Menu::create_window()
{
	window = guienv->addWindow(
		rect<s32>(0, 0, 640, 480),
		false, L"\t\t\t\t\t\t\t\t\t\tMenu window");
	window->getCloseButton()->setVisible(false);
}

void Menu::create_buttons()
{
	button["quit"] = guienv->addButton(rect<s32>(490,300,600,300 + 32), 0, QUIT_BUTTON,
L"QUIT", L"Game Exit");
	button["help"] = guienv->addButton(rect<s32>(370,300,480,300 + 32), 0, HELP_BUTTON,
L"HELP", L"Help");
	button["ia"] = guienv->addButton(rect<s32>(120,300,240,300 + 32), 0, IA_BUTTON,
L"IA", L"Opponent is an IA");
	button["player"] = guienv->addButton(rect<s32>(250,300,360,300 + 32), 0, PLAYER_BUTTON,
L"PLAYER", L"Opponent is a player");
}

void Menu::create_image()
{
	image = guienv->addImage(driver->getTexture(findAsset("bomberman.png").c_str()),
			position2d<int>(10,10));
}

void Menu::create_text()
{
	text = guienv->addStaticText(L"CHOOSE YOUR OPPONENT",
		rect<s32>(250,360,400,382), true, false, window);
}