#include "Core.hpp"

Core::Core(int fps=60)
{
    _fps = fps;
}

Core::~Core()
{
}

void Core::init()
{
    _irr = std::make_shared<Irrlicht>();
    _irr->init();
    _irr->getDevice()->setWindowCaption(L"Bomberman");
    _irr->getGUIenv();
    _assets = std::make_shared<Assets>(_irr);

    _assets->init();
    _gameManager = Scene(_assets, _irr);
    _gameManager.initMenu();
}

bool Core::isGameOver()
{
    playersLeft = 0;
    indexLastPlayer = -1;

    for (size_t i = 0; i < _assets->getPlayers()->size(); i++) {
        if (_assets->getPlayers()->at(i) != 0) {
            playersLeft++;
            indexLastPlayer = i;
        }
    }
    if (playersLeft <= 1)
        return (true);
    return (false);
}

void Core::update()
{
    for (int i = 0; i < _assets->getEntities()->size(); i++) {
        _assets->getEntities()->at(i)->update(_assets->getMap(), _assets);
    }
    if (isGameOver())
        _gameManager.initGameOverScene(playersLeft, indexLastPlayer);

}

void Core::draw()
{
    if (_gameManager.getGameState() == State::MENU)
        _gameManager.menuScene();
    else if (_gameManager.getGameState() == State::GAME)
        _gameManager.gameScene();
    if (_gameManager.getGameState() == GAME_OVER)
        _gameManager.gameOverScene();
}

void Core::run()
{
    std::clock_t frameBgnTime;
    double deltaTime = 0.0;
    double frameTime = 1.0f / (float)_fps;
    double remainingTime = 0.0;
    size_t updates = 0;

    while (_irr->getDevice()->run())
    {
        frameBgnTime = std::clock();

        update();
        draw();

        deltaTime = (std::clock() - frameBgnTime) / (double)CLOCKS_PER_SEC;

        // if the remaining time is > to the time of 1 frame, keep updating the game
        // this fixes the framerate at $fps frames per sec without using sleep() to prevent lags at low fps
        remainingTime = frameTime - deltaTime;
        updates = 0;
        while (deltaTime < remainingTime) {
            frameBgnTime = std::clock();
            if (updates < 5) {
                updates++;
                update();
            }
            deltaTime = (std::clock() - frameBgnTime) / (double)CLOCKS_PER_SEC;
            remainingTime -= deltaTime;
        }
        
        if (_irr->getEventreceiver()->IsKeyDown(irr::KEY_KEY_E) || _irr->getEventreceiver()->IsKeyDown(irr::KEY_ESCAPE))
            _irr->getDevice()->closeDevice();
    }
}

std::shared_ptr<Irrlicht> Core::getLib(void) const
{
    return (this->_irr);
}