#include "Core.hpp"

Core::Core()
{
}

Core::~Core()
{
}

void Core::init()
{
    // statement = State::MENU;
    _irr = std::make_shared<Irrlicht>();
    _irr->init();
    _irr->getDevice()->setWindowCaption(L"Bomberman");
    _irr->getGUIenv();
    _assets = std::make_shared<Assets>(_irr);
    // set_menu();

    this->initAssets();
    _assets->init();
    _gameManager = Scene(_assets, _irr);
}

void Core::initAssets()
{
    // set_menu();
    // this->map = std::make_shared<GameMap>(entities, 19, 13, std::shared_ptr<Core>(this), smgr, driver, device);
    std::shared_ptr<Menu> menu = std::make_shared<Menu>(std::shared_ptr<Core>(this));
    menu->create();
    // this->gameOverStr.clear();

    // this->gameOverStr.clear();
}

// void Core::deleteAssets()
// {
//     _assets->getPlayers()->clear();
//     _assets->getPlayers()->shrink_to_fit();
//     for (size_t i = 0; i < _assets->getEntities()->size(); i++) {
//         if (_assets->getEntities()->at(i)) {
//             _assets->getEntities()->at(i)->remove();
//             _assets->getEntities()->at(i).reset();
//         }
//     }
//     _assets->getEntities()->clear();
//     _assets->getEntities()->shrink_to_fit();
//     _assets->getMap().reset();
// }

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
    // if (playersLeft == 1) {
    //     this->statement = State::GAME_OVER;
    //     if (this->gameOverStr.empty()) {
    //         if (indexLastPlayer == 0)
    //             gameOverStr += L"Black";
    //         if (indexLastPlayer == 1)
    //             gameOverStr += L"White";
    //         if (indexLastPlayer == 2)
    //             gameOverStr += L"Red";
    //         if (indexLastPlayer == 3)
    //             gameOverStr += L"Pink";
    //         gameOverStr += L" player WINS !";
    //         gameOverTimerBgn = _irr->getDevice()->getTimer()->getRealTime();
    //     } else if ((_irr->getDevice()->getTimer()->getRealTime() - gameOverTimerBgn) / 1000 >= 3) {
    //         _assets->getPlayers()->erase(_assets->getPlayers()->begin() + indexLastPlayer);
    //         this->deleteAssets();
    //         set_menu();
    //         // -------- TMP --------
    //         statement = State::GAME;

    //         this->initAssets();
    //         _assets->init();
    //     }
    // } else if (playersLeft == 0) {
    //     this->statement = State::GAME_OVER;
    //     if (this->gameOverStr.empty()) {
    //         gameOverStr += L" Nobody win !";
    //         gameOverTimerBgn = _irr->getDevice()->getTimer()->getRealTime();
    //     } else if ((_irr->getDevice()->getTimer()->getRealTime() - gameOverTimerBgn) / 1000 >= 3) {
    //         this->deleteAssets();
    //         set_menu();
    //         // -------- TMP --------
    //         statement = State::GAME;

    //         this->initAssets();
    //         _assets->init();
    //     }
    // }
}

void Core::set_ia(int player_index, bool ia)
{
    _assets->getPlayers()->at(player_index)->SetIsAI(ia);
}

// void Core::set_menu()
// {
//     if (this->statement != State::MENU) {
//         this->statement = State::MENU;
//     }
// }

// void Core::set_game()
// {
//     if (this->statement != State::GAME) {
//         this->statement = State::GAME;
//     }
// }

void Core::run()
{
    std::wstring fpsStr;
    std::clock_t totalFpsTime;
    std::clock_t frameBgnTime;
    std::clock_t frameEndTime;
    double deltaTime = 0.0;
    double totalFrameTime = 0.0;
    size_t fps = 60;
    double frameTime = 1.0f / (float)fps;
    double remainingTime = 0.0;
    size_t updates = 0;
    dimension2du windowSize = _irr->getDriver()->getCurrentRenderTargetSize();

    while (_irr->getDevice()->run())
    {
        totalFpsTime = std::clock();
        frameBgnTime = std::clock();

        //update
        for (int i = 0; i < _assets->getEntities()->size(); i++)
        {
            _assets->getEntities()->at(i)->update(_assets->getMap(), _assets);
        }
        if (isGameOver())
            _gameManager.initGameOverScene(playersLeft, indexLastPlayer);

        // draw
        // ---------- TMP COMMENT -----------
        // if (_gameManager.getGameState() == State::MENU)
        //     this->update_menu();
        // else if (_gameManager.getGameState() == State::GAME)
        this->update_game();
        if (_gameManager.getGameState() == GAME_OVER)
            _gameManager.gameOverScene();
        frameEndTime = std::clock();

        deltaTime = (frameEndTime - frameBgnTime) / (double)CLOCKS_PER_SEC;

        //if the remaining time is > to the time of 1 frame, keep updating the game
        // this fixes the framerate at $fps frames per sec without using sleep() to prevent lags at low fps
        remainingTime = frameTime - deltaTime;
        updates = 0;
        while (deltaTime < remainingTime)
        {
            frameBgnTime = std::clock();
            if (updates < 5)
            {
                updates++;
                for (int i = 0; i < _assets->getEntities()->size(); i++)
                    _assets->getEntities()->at(i)->update(_assets->getMap(), _assets);
                if (isGameOver())
                    _gameManager.initGameOverScene(playersLeft, indexLastPlayer);
            }
            deltaTime = (std::clock() - frameBgnTime) / (double)CLOCKS_PER_SEC;
            remainingTime -= deltaTime;
        }
        totalFrameTime = (std::clock() - totalFpsTime) / (double)CLOCKS_PER_SEC;
        if (_irr->getEventreceiver()->IsKeyDown(irr::KEY_KEY_E) || _irr->getEventreceiver()->IsKeyDown(irr::KEY_ESCAPE))
            _irr->getDevice()->closeDevice();
    }
    // _irr->getDevice()->drop(); // CAUSES A SEGFAULT SINCE IN IRRLICHT CLASS
}

// void Core::setstatement(State is)
// {
//     this->statement = is;
// }

// State Core::getstatement()
// {
//     return (this->statement);
// }

// void Core::update_gameOver()
// {
//     dimension2du size = _irr->getDriver()->getScreenSize();
//     _irr->getDriver()->beginScene(true, true, SColor(255, 100, 101, 140));
//     _irr->getSmgr()->drawAll();
//     if (_assets->getFont())
//         _assets->getFont()->draw(this->gameOverStr.c_str(), recti(size.Width / 2 - 50, size.Height / 2, 300, 50), SColor(255,230,230,230));
//     _irr->getGUIenv()->drawAll();
//     _irr->getDriver()->endScene();
// }

void Core::update_menu()
{
    _irr->getDriver()->beginScene(true, true, SColor(255, 100, 101, 140));
    _irr->getSmgr()->drawAll();
    _irr->getGUIenv()->drawAll();
    _irr->getDriver()->endScene();
}

void Core::update_game()
{
    _irr->getDevice()->setEventReceiver(_irr->getEventreceiver().get());
    _irr->getDriver()->beginScene(true, true, SColor(255, 100, 101, 140));
    _irr->getSmgr()->drawAll();
    _irr->getGUIenv()->drawAll();
    _irr->getDriver()->endScene();
}

std::shared_ptr<Irrlicht> Core::getLib(void) const
{
    return (this->_irr);
}