#include "Core.hpp"
#include "../Menu/Menu.hpp"

Core::Core()
{
}

Core::~Core()
{
}

void Core::init()
{
#ifdef __APPLE__
    video::E_DRIVER_TYPE driverType = EDT_OPENGL;
#else
    video::E_DRIVER_TYPE driverType = driverChoiceConsole();
#endif
    if (driverType == video::EDT_COUNT)
        throw("Problem in driver");
    this->eventReceiver = std::make_shared<MyEventReceiver>();
    statement = State::MENU;
    //create device
    device = std::shared_ptr<IrrlichtDevice>(createDevice(driverType, dimension2d<u32>(640, 480), 16, false, false, false, eventReceiver.get()));
    if (!device)
        throw("Problem in device");
    device->setResizable(true);
    device->setWindowCaption(L"Hello world! - Irrlicht Engine Demo");
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    font = this->guienv->getBuiltInFont();
    set_menu();
    
    //light source
    ILightSceneNode* light = smgr->addLightSceneNode( 0, vector3df(0.0f,50.0f,2.0f), SColorf(1.0f,1.0f,1.0f,1.0f), 35.0f );
    //camera
    smgr->addCameraSceneNode(0, vector3df(0,11,-2), vector3df(0,0,0));

    this->collMan = smgr->getSceneCollisionManager();

    entities = std::make_shared<std::vector<std::shared_ptr<IEntity>>>();
    players = std::make_shared<std::vector<std::shared_ptr<IEntity>>>();
    this->initAssets();
}

void Core::initAssets()
{
    this->map = std::make_shared<GameMap>(entities, 19, 13, this, smgr, driver, device);
    std::shared_ptr<Menu> menu = std::make_shared<Menu>(this);
    this->gameOverStr.clear();

    entities->push_back(std::make_shared<Player>("Bomberman.MD3", "BlackBombermanTextures.png", this, irr::KEY_KEY_Z, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_KEY_D, irr::KEY_SPACE));
    players->push_back(entities->back());
    entities->back()->setPosition(vector3df(-8.0f, 0.0f, -5.0f));
    
    entities->push_back(std::make_shared<Player>("Bomberman.MD3", "WhiteBombermanTextures.png", this, irr::KEY_KEY_Y, irr::KEY_KEY_H, irr::KEY_KEY_G, irr::KEY_KEY_J, irr::KEY_KEY_L));
    players->push_back(entities->back());
    entities->back()->setPosition(vector3df(-8.0f, 0.0f, 5.0f));
    
    entities->push_back(std::make_shared<Player>("Bomberman.MD3", "RedBombermanTextures.png", this, irr::KEY_KEY_Y, irr::KEY_KEY_H, irr::KEY_KEY_G, irr::KEY_KEY_J, irr::KEY_KEY_L));
    players->push_back(entities->back());
    entities->back()->setPosition(vector3df(8.0f, 0.0f, 5.0f));
    entities->back()->SetIsAI(true);
    
    entities->push_back(std::make_shared<Player>("Bomberman.MD3", "PinkBombermanTextures.png", this, irr::KEY_KEY_Y, irr::KEY_KEY_H, irr::KEY_KEY_G, irr::KEY_KEY_J, irr::KEY_KEY_L));
    players->push_back(entities->back());
    entities->back()->setPosition(vector3df(8.0f, 0.0f, -5.0f));
    entities->back()->SetIsAI(true);
}

void Core::deleteAssets()
{
    players->clear();
    players->shrink_to_fit();
    for (size_t i = 0; i < entities->size(); i++) {
        if (entities->at(i)) {
            entities->at(i)->remove();
            entities->at(i).reset();
        }
    }
    entities->clear();
    entities->shrink_to_fit();
    this->map.reset();
}

void Core::isGameOver()
{
    int playersLeft = 0;
    int indexPlayer = -1;

    for (size_t i = 0; i < this->players->size(); i++) {
        if (this->players->at(i) != 0) {
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
            gameOverTimerBgn = device->getTimer()->getRealTime();
        } else if ((device->getTimer()->getRealTime() - gameOverTimerBgn) / 1000 >= 3) {
            players->erase(players->begin() + indexPlayer);
            this->deleteAssets();
            set_menu();

            this->initAssets();
        }
    }
    else if (playersLeft == 0) {
        this->statement = State::GAME_OVER;
        if (this->gameOverStr.empty()) {
            gameOverStr += L" Nobody win !";
            gameOverTimerBgn = device->getTimer()->getRealTime();
        } else if ((device->getTimer()->getRealTime() - gameOverTimerBgn) / 1000 >= 3) {
            this->deleteAssets();
            set_menu();

            this->initAssets();
        }
    }
}

const std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> &Core::getPlayers() const
{
    return (players);
}

const std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> &Core::getEntities() const
{
    return (entities);
}

IVideoDriver *Core::getDriver() const
{
    return (driver);
}

ISceneManager *Core::getSmgr() const
{
    return (smgr);
}

std::shared_ptr<IrrlichtDevice> Core::getDevice() const
{
    return (device);
}

IGUIEnvironment *Core::getGUIenv() const
{
    return (guienv);
}

void Core::set_ia(int player_index, bool ia)
{
    this->players->at(player_index)->SetIsAI(ia);
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
    dimension2du windowSize = driver->getCurrentRenderTargetSize();

    while (device->run())
    {
        totalFpsTime = std::clock();
        frameBgnTime = std::clock();

        //update
        for (int i = 0; i < entities->size(); i++)
        {
            entities->at(i)->update(this->map);
        }
        isGameOver();

        // draw
        if (this->statement == State::MENU)
            this->update_menu();
        else if (this->statement == State::GAME)
            this->update_game();
        else if (this->statement == State::GAME_OVER)
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
                for (int i = 0; i < entities->size(); i++)
                    entities->at(i)->update(this->map);
                isGameOver();
            }
            deltaTime = (std::clock() - frameBgnTime) / (double)CLOCKS_PER_SEC;
            remainingTime -= deltaTime;
        }
        totalFrameTime = (std::clock() - totalFpsTime) / (double)CLOCKS_PER_SEC;
        if (this->eventReceiver->IsKeyDown(irr::KEY_KEY_E) || this->eventReceiver->IsKeyDown(irr::KEY_ESCAPE))
            device->closeDevice();
    }
    device->drop();
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
    dimension2du size = driver->getScreenSize();
    driver->beginScene(true, true, SColor(255, 100, 101, 140));
    smgr->drawAll();
    if (this->font)
        this->font->draw(this->gameOverStr.c_str(), recti(size.Width / 2 - 50, size.Height / 2, 300, 50), SColor(255,230,230,230));
    guienv->drawAll();
    driver->endScene();
}

void Core::update_menu()
{
    driver->beginScene(true, true, SColor(255, 100, 101, 140));
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();
}

void Core::update_game()
{
    device->setEventReceiver(this->eventReceiver.get());
    driver->beginScene(true, true, SColor(255, 100, 101, 140));
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();
    // if return to menu --> set_menu()
}

std::shared_ptr<MyEventReceiver> Core::getEventreceiver()
{
    return (this->eventReceiver);
}

irr::core::array<irr::SJoystickInfo> Core::getJoystickinfo()
{
    return (this->joystickInfo);
}

ISceneCollisionManager *Core::getCollMan() const
{
    return (this->collMan);
}

std::shared_ptr<GameMap> Core::getMap() const
{
    return (this->map);
}