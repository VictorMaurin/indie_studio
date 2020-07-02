/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Menu
*/

#include "Menu.hpp"
#include "../../assets/assets.hpp"

Menu::Menu(std::shared_ptr<Irrlicht> irr, Scene *gameManager)
{
	if (!irr || !irr.get() || !gameManager)
		throw MyException("unexpected argument", "Menu.cpp", 15, "Menu::ctor()");
	_gameManager = gameManager;
    driver = irr->getDriver();
    device = irr->getDevice();
    smgr = irr->getSmgr();
    guienv = irr->getGUIenv();
}

Menu::~Menu()
{
}

void Menu::create(std::shared_ptr<Assets> assets, std::shared_ptr<Irrlicht> irr)
{
	if (!assets || !assets.get())
		throw MyException("unexpected argument", "Menu.cpp", 30, "Menu::create()");
	this->create_window();
	this->create_buttons();
	this->create_image();
	this->create_text();
	receiver = std::make_shared<MyEvent>(assets, window, button, image, text, irr, this);
	if (!receiver || !receiver.get())
		throw MyException("couldn't create menu event receiver", "Menu.cpp", 37, "Menu::create()");
	device->setEventReceiver(receiver.get());
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

Scene *Menu::getGameManager(void) const
{
	return (_gameManager);
}