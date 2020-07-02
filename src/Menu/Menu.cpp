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
	_irr = irr;
}

Menu::~Menu()
{
}

void Menu::create(std::shared_ptr<Assets> assets, std::shared_ptr<Irrlicht> irr)
{
	if (!assets || !assets.get())
		throw MyException("unexpected argument", "Menu.cpp", 30, "Menu::create()");
	this->createWindow();
	this->createButtons();
	this->createImage();
	this->createText();
	receiver = std::make_shared<MyEvent>(assets, window, button, image, text, irr, this);
	if (!receiver || !receiver.get())
		throw MyException("couldn't create menu event receiver", "Menu.cpp", 37, "Menu::create()");
	_irr->getDevice()->setEventReceiver(receiver.get());
}

void Menu::createWindow()
{
	window = _irr->getGUIenv()->addWindow(
		rect<s32>(0, 0, 640, 480),
		false, L"\t\t\t\t\t\t\t\t\t\tMenu window");
	window->getCloseButton()->setVisible(false);
}

void Menu::createButtons()
{
	button["quit"] = _irr->getGUIenv()->addButton(rect<s32>(490,300,600,300 + 32), 0, QUIT_BUTTON, L"QUIT", L"Game Exit");
	button["help"] = _irr->getGUIenv()->addButton(rect<s32>(370,300,480,300 + 32), 0, HELP_BUTTON, L"HELP", L"Help");
	button["ia"] = _irr->getGUIenv()->addButton(rect<s32>(120,300,240,300 + 32), 0, IA_BUTTON, L"IA", L"Opponent is an IA");
	button["player"] = _irr->getGUIenv()->addButton(rect<s32>(250,300,360,300 + 32), 0, PLAYER_BUTTON, L"PLAYER", L"Opponent is a player");
}

void Menu::createImage()
{
	image = _irr->getGUIenv()->addImage(_irr->getDriver()->getTexture(findAsset("bomberman.png").c_str()),
			position2d<int>(10,10));
}

void Menu::createText()
{
	text = _irr->getGUIenv()->addStaticText(L"CHOOSE YOUR OPPONENT",
		rect<s32>(250,360,400,382), true, false, window);
}

Scene *Menu::getGameManager(void) const
{
	return (_gameManager);
}