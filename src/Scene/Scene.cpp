#include "Scene.hpp"

Scene::Scene()
{
}

Scene::Scene(std::shared_ptr<Assets> assets, std::shared_ptr<Irrlicht> irr)
{
    _gameState = MENU;
    _assets = assets;
    _irr = irr;
}

Scene::~Scene()
{
}

void Scene::initMenu()
{
    _gameState = MENU;
    _menu = std::make_shared<Menu>(_irr, this);
    _menu->create(_assets, _irr);
}

void Scene::menuScene()
{
    _irr->getDriver()->beginScene(true, true, SColor(255, 100, 101, 140));
    _irr->getSmgr()->drawAll();
    _irr->getGUIenv()->drawAll();
    _irr->getDriver()->endScene();
}

void Scene::startGame()
{
    _gameState = GAME;
    _menu.reset();
    _irr->getDevice()->setEventReceiver(_irr->getEventreceiver().get());
}

void Scene::gameScene()
{
    _irr->getDriver()->beginScene(true, true, SColor(255, 100, 101, 140));
    _irr->getSmgr()->drawAll();
    _irr->getGUIenv()->drawAll();
    _irr->getDriver()->endScene();
}

void Scene::initGameOverScene(int playersLeft, int indexLastPlayer)
{
    if (playersLeft == 1) {
        _gameState = State::GAME_OVER;
        if (_gameOverStr.empty()) {
            if (indexLastPlayer == 0)
                _gameOverStr += L"Black";
            if (indexLastPlayer == 1)
                _gameOverStr += L"White";
            if (indexLastPlayer == 2)
                _gameOverStr += L"Red";
            if (indexLastPlayer == 3)
                _gameOverStr += L"Pink";
            _gameOverStr += L" player WINS !";
            gameOverTimerBgn = _irr->getDevice()->getTimer()->getRealTime();
        } else if ((_irr->getDevice()->getTimer()->getRealTime() - gameOverTimerBgn) / 1000 >= 3) {
            _assets->getPlayers()->erase(_assets->getPlayers()->begin() + indexLastPlayer);
            _assets->deleteAll();
            initMenu();
            _assets->init();
        }
    } else if (playersLeft == 0) {
        this->_gameState = State::GAME_OVER;
        if (_gameOverStr.empty()) {
            _gameOverStr += L" It's a draw !";
            gameOverTimerBgn = _irr->getDevice()->getTimer()->getRealTime();
        } else if ((_irr->getDevice()->getTimer()->getRealTime() - gameOverTimerBgn) / 1000 >= 3) {
            _assets->deleteAll();
            initMenu();
            _assets->init();
        }
    }
}

void Scene::gameOverScene()
{
    dimension2du size = _irr->getDriver()->getScreenSize();

    _irr->getDriver()->beginScene(true, true, SColor(255, 100, 101, 140));
    _irr->getSmgr()->drawAll();
    if (_assets->getFont())
        _assets->getFont()->draw(_gameOverStr.c_str(), recti(size.Width / 2 - 50, size.Height / 2, 300, 50), SColor(255,230,230,230));
    _irr->getGUIenv()->drawAll();
    _irr->getDriver()->endScene();
}

State Scene::getGameState(void) const
{
    return (_gameState);
}