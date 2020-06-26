#include "Core.hpp"

Core::Core()
{
}

Core::~Core()
{
}

void Core::init()
{
// #ifdef __APPLE__
//     video::E_DRIVER_TYPE driverType = EDT_OPENGL;
// #else
//     video::E_DRIVER_TYPE driverType = driverChoiceConsole();
// #endif
//     if (driverType == video::EDT_COUNT)
//         throw("Problem in driver");
    // this->eventReceiver = std::make_shared<MyEventReceiver>();
    statement = State::MENU;
    _irr = std::make_shared<Irrlicht>();
    _irr->init();
    _irr->getDevice()->setWindowCaption(L"Bomberman");
    _irr->getGUIenv();
    _assets = std::make_shared<Assets>(_irr);
    //create device
    // device = std::shared_ptr<IrrlichtDevice>(createDevice(driverType, dimension2d<u32>(640, 480), 16, false, false, false, eventReceiver.get()));
    // if (!device)
    //     throw("Problem in device");
    // device->setResizable(true);
    // device->setWindowCaption(L"Hello world! - Irrlicht Engine Demo");
    // driver = device->getVideoDriver();
    // smgr = device->getSceneManager();
    // guienv = device->getGUIEnvironment();
    // font = this->guienv->getBuiltInFont();
    set_menu();
    
    //light source
    // ILightSceneNode* light = smgr->addLightSceneNode( 0, vector3df(0.0f,50.0f,2.0f), SColorf(1.0f,1.0f,1.0f,1.0f), 35.0f );
    //camera
    _irr->getSmgr()->addCameraSceneNode(0, vector3df(0,11,-2), vector3df(0,0,0));

    // this->collMan = _irr->getSmgr()->getSceneCollisionManager();

    // entities = std::make_shared<std::vector<std::shared_ptr<IEntity>>>();
    // players = std::make_shared<std::vector<std::shared_ptr<IEntity>>>();
    this->initAssets();
    _assets->init();
}

void Core::initAssets()
{
    // this->map = std::make_shared<GameMap>(entities, 19, 13, _irr);

    // -------------- TMP COMMENT --------------
    // std::shared_ptr<Menu> menu = std::make_shared<Menu>(this);
    this->gameOverStr.clear();

    // entities->push_back(std::make_shared<Player>("Bomberman.MD3", "BlackBombermanTextures.png", _irr, irr::KEY_KEY_Z, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_KEY_D, irr::KEY_SPACE));
    // players->push_back(entities->back());
    // entities->back()->setPosition(vector3df(-8.0f, 0.0f, -5.0f));
    
    // entities->push_back(std::make_shared<Player>("Bomberman.MD3", "WhiteBombermanTextures.png", _irr, irr::KEY_KEY_Y, irr::KEY_KEY_H, irr::KEY_KEY_G, irr::KEY_KEY_J, irr::KEY_KEY_L));
    // players->push_back(entities->back());
    // entities->back()->setPosition(vector3df(-8.0f, 0.0f, 5.0f));
    
    // entities->push_back(std::make_shared<Player>("Bomberman.MD3", "RedBombermanTextures.png", _irr, irr::KEY_KEY_Y, irr::KEY_KEY_H, irr::KEY_KEY_G, irr::KEY_KEY_J, irr::KEY_KEY_L));
    // players->push_back(entities->back());
    // entities->back()->setPosition(vector3df(8.0f, 0.0f, 5.0f));
    // entities->back()->SetIsAI(true);
    
    // entities->push_back(std::make_shared<Player>("Bomberman.MD3", "PinkBombermanTextures.png", _irr, irr::KEY_KEY_Y, irr::KEY_KEY_H, irr::KEY_KEY_G, irr::KEY_KEY_J, irr::KEY_KEY_L));
    // players->push_back(entities->back());
    // entities->back()->setPosition(vector3df(8.0f, 0.0f, -5.0f));
    // entities->back()->SetIsAI(true);
}

void Core::deleteAssets()
{
    _assets->getPlayers()->clear();
    _assets->getPlayers()->shrink_to_fit();
    for (size_t i = 0; i < _assets->getEntities()->size(); i++) {
        if (_assets->getEntities()->at(i)) {
            _assets->getEntities()->at(i)->remove();
            _assets->getEntities()->at(i).reset();
        }
    }
    _assets->getEntities()->clear();
    _assets->getEntities()->shrink_to_fit();
    _assets->getMap().reset();
}

void Core::isGameOver()
{
    int playersLeft = 0;
    int indexPlayer = -1;

    for (size_t i = 0; i < _assets->getPlayers()->size(); i++) {
        if (_assets->getPlayers()->at(i) != 0) {
            playersLeft++;
            indexPlayer = i;
        }
    }
    if (playersLeft == 1) {
        this->statement = State::GAME_OVER;
        if (this->gameOverStr.empty()) {
            if (indexPlayer == 0)
                gameOverStr += L"Black";
            if (indexPlayer == 1)
                gameOverStr += L"White";
            if (indexPlayer == 2)
                gameOverStr += L"Red";
            if (indexPlayer == 3)
                gameOverStr += L"Pink";
            gameOverStr += L" player WINS !";
            gameOverTimerBgn = _irr->getDevice()->getTimer()->getRealTime();
        } else if ((_irr->getDevice()->getTimer()->getRealTime() - gameOverTimerBgn) / 1000 >= 3) {
            _assets->getPlayers()->erase(_assets->getPlayers()->begin() + indexPlayer);
            this->deleteAssets();
            set_menu();
            // -------- TMP --------
            statement = State::GAME;

            this->initAssets();
            _assets->init();
        }
    } else if (playersLeft == 0) {
        this->statement = State::GAME_OVER;
        if (this->gameOverStr.empty()) {
            gameOverStr += L" Nobody win !";
            gameOverTimerBgn = _irr->getDevice()->getTimer()->getRealTime();
        } else if ((_irr->getDevice()->getTimer()->getRealTime() - gameOverTimerBgn) / 1000 >= 3) {
            this->deleteAssets();
            set_menu();
            // -------- TMP --------
            statement = State::GAME;

            this->initAssets();
            _assets->init();
        }
    }
}

// const std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> &Core::getPlayers() const
// {
//     return (players);
// }

// const std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> &Core::getEntities() const
// {
//     return (entities);
// }

// IVideoDriver *Core::getDriver() const
// {
//     return (driver);
// }

// ISceneManager *Core::getSmgr() const
// {
//     return (smgr);
// }

// std::shared_ptr<IrrlichtDevice> Core::getDevice() const
// {
//     return (device);
// }

// IGUIEnvironment *Core::getGUIenv() const
// {
//     return (guienv);
// }

void Core::set_ia(int player_index, bool ia)
{
    _assets->getPlayers()->at(player_index)->SetIsAI(ia);
}

void Core::set_menu()
{
    if (this->statement != State::MENU) {
        this->statement = State::MENU;
    }
}

void Core::set_game()
{
    if (this->statement != State::GAME) {
        this->statement = State::GAME;
    }
}

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
        isGameOver();

        // draw
        // ---------- TMP COMMENT -----------
        // if (this->statement == State::MENU)
        //     this->update_menu();
        // else if (this->statement == State::GAME)
        this->update_game();
        if (this->statement == State::GAME_OVER)
            this->update_gameOver();
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
                isGameOver();
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

void Core::setstatement(State is)
{
    this->statement = is;
}

State Core::getstatement()
{
    return (this->statement);
}

void Core::update_gameOver()
{
    dimension2du size = _irr->getDriver()->getScreenSize();
    _irr->getDriver()->beginScene(true, true, SColor(255, 100, 101, 140));
    _irr->getSmgr()->drawAll();
    if (_assets->getFont())
        _assets->getFont()->draw(this->gameOverStr.c_str(), recti(size.Width / 2 - 50, size.Height / 2, 300, 50), SColor(255,230,230,230));
    _irr->getGUIenv()->drawAll();
    _irr->getDriver()->endScene();
}

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

// std::shared_ptr<MyEventReceiver> Core::getEventreceiver()
// {
//     return (this->eventReceiver);
// }

// irr::core::array<irr::SJoystickInfo> Core::getJoystickinfo()
// {
//     return (this->joystickInfo);
// }

// ISceneCollisionManager *Core::getCollMan() const
// {
//     return (this->collMan);
// }

// std::shared_ptr<GameMap> Core::getMap() const
// {
//     return (this->map);
// }

std::shared_ptr<Irrlicht> Core::getLib(void) const
{
    return (this->_irr);
}