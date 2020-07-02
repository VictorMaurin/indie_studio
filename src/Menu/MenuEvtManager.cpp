/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MenuEvtManager
*/

#include "MenuEvtManager.hpp"

MyEvent::MyEvent(std::shared_ptr<Assets> assets, IGUIWindow* window, std::map<std::string, IGUIButton*> button, IGUIImage* image, IGUIStaticText* text, std::shared_ptr<Irrlicht> irr, Menu *gameMenu)
{
    _gameMenu = gameMenu;
    _assets = assets;
    _irr = irr;
    _button = button;
    _text = text;
    _image = image;
    win = window;
}

bool MyEvent::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();
		switch(event.GUIEvent.EventType) {
		case EGET_BUTTON_CLICKED:
			switch(id)
			{
			case QUIT_BUTTON:
				_irr->getDevice()->closeDevice();
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
                    _gameMenu->getGameManager()->startGame();
                    _assets->setAi(1, true);
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
                    _gameMenu->getGameManager()->startGame();
                    _assets->setAi(1, false);
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
                    image_help = _irr->getGUIenv()->addImage(_irr->getDriver()->getTexture(findAsset("help.png").c_str()),
		position2d<int>(10,10));
                    _return = _irr->getGUIenv()->addButton(rect<s32>(490,440,600,440 + 32), 0, RETURN_BUTTON,
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