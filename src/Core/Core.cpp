#include "Core.hpp"
#include "../Menu/Menu.hpp"

Core::Core()
{

}

Core::~Core()
{
    //delete driver;
    //delete smgr;
    //delete guienv;
    //delete device;
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
    this->eventReceiver = new MyEventReceiver();
    statement = State::MENU;
    //create device
    device = createDevice(driverType,
    dimension2d<u32>(640, 480), 16, false, false, false, eventReceiver);
    if (!device)
        throw("Problem in device");
    device->setResizable(true);
    device->setWindowCaption(L"Hello world! - Irrlicht Engine Demo");
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    set_menu();
    
    //tmp light source
    ILightSceneNode* light = smgr->addLightSceneNode( 0, vector3df(0.0f,50.0f,2.0f), SColorf(1.0f,1.0f,1.0f,1.0f), 35.0f );
    //tmp camera
    smgr->addCameraSceneNode(0, vector3df(0,11,-2), vector3df(0,0,0));

    this->collMan = smgr->getSceneCollisionManager();

    entities = std::make_shared<std::vector<std::shared_ptr<IEntity>>>();
    players = std::make_shared<std::vector<std::shared_ptr<IEntity>>>();
    this->map = std::make_shared<GameMap>(entities, 19, 13, this, smgr, driver, device);
    entities->push_back(std::make_shared<Player>("Bomberman.MD3", "BlackBombermanTextures.png", this, smgr, driver, device, joystickInfo, eventReceiver, irr::KEY_KEY_Z, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_KEY_D));
    Menu *menu = new Menu(this);
    players->push_back(entities->back());
    entities->push_back(std::make_shared<Player>("Bomberman.MD3", "BlackBombermanTextures.png", this, smgr, driver, device, joystickInfo, eventReceiver, irr::KEY_KEY_T, irr::KEY_KEY_Y, irr::KEY_KEY_U, irr::KEY_KEY_I));
    players->push_back(entities->back());
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

IrrlichtDevice *Core::getDevice() const
{
    return (device);
}

IGUIEnvironment *Core::getGUIenv() const
{
    return (guienv);
}

void Core::set_ia(bool ia)
{
    this->is_ia = ia;
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

        // draw
        if (this->statement == State::MENU)
            this->update_menu();
        else if (this->statement == State::GAME)
            this->update_game();
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
            }
            deltaTime = (std::clock() - frameBgnTime) / (double)CLOCKS_PER_SEC;
            remainingTime -= deltaTime;
        }
        // std::cout << totalFrameTime << " " << remainingTime << std::endl;
        totalFrameTime = (std::clock() - totalFpsTime) / (double)CLOCKS_PER_SEC;
        // std::cout << remainingTime << " " << 1.0f / totalFrameTime << std::endl;
        fpsStr = std::to_wstring((int)(1.0f / totalFrameTime));
        guienv->addStaticText(fpsStr.c_str(), irr::core::rect<irr::s32>(10, 10, 30, 20), true);
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

void Core::update_menu()
{
    driver->beginScene(true, true, SColor(255, 100, 101, 140));
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();
}

void Core::update_game()
{
    device->setEventReceiver(this->eventReceiver);
    driver->beginScene(true, true, SColor(255, 100, 101, 140));
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();
    // if return to menu --> set_menu()
}

MyEventReceiver* Core::getEventreceiver()
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