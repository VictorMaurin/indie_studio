#include "Core.hpp"

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
    //create device
    device = createDevice(EDT_OPENGL,
    dimension2d<u32>(640, 480), 16, false, false, false, 0);
    if (!device)
        throw("Problem in device");
    device->setWindowCaption(L"Hello world! - Irrlicht Engine Demo");
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    ILightSceneNode* light = smgr->addLightSceneNode( 0, vector3df(0.0f,30.0f,-40.0f), SColorf(1.0f,1.0f,1.0f,1.0f), 500.0f );
    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    entities.push_back(std::make_shared<Wall>(smgr, driver, device)); //tmp
}

void Core::run()
{
    std::clock_t frameBgnTime;
    std::clock_t frameEndTime;
    double deltaTime = 0.0;
    size_t fps = 60;
    double frameTime = 1 / fps;
    double remainingTime = 0.0;
    size_t updates = 0;

    while (device->run())
    {
        frameBgnTime = std::clock();

        // do events

        //update
        for (int i = 0; i < entities.size(); i++)
        {
            entities[i]->update();
        }

        // draw
        driver->beginScene(true, true, SColor(255, 100, 101, 140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();

        frameEndTime = std::clock();

        deltaTime = frameEndTime - frameBgnTime;

        //if the remaining time is > to the time of 1 frame, keep updating the game
        // this fixes the framerate at $fps frames per sec without using sleep() to prevent lags at low fps
        remainingTime = abs((deltaTime / (double)CLOCKS_PER_SEC) - (frameTime / (double)CLOCKS_PER_SEC));
        updates = 0;
        while (frameTime > remainingTime)
        {
            frameBgnTime = std::clock();
            if (updates < 5)
            {
                updates++;
                for (int i = 0; i < entities.size(); i++)
                    entities[i]->update();
            }
            deltaTime = std::clock() - frameBgnTime;
            remainingTime -= deltaTime * (double)CLOCKS_PER_SEC;
        }
    }
}

const std::vector<std::shared_ptr<IEntity>> &Core::getEntities() const
{
    return (entities);
}

const IVideoDriver *Core::getDriver() const
{
    return (driver);
}

const ISceneManager *Core::getSmgr() const
{
    return (smgr);
}

const IrrlichtDevice *Core::getDevice() const
{
    return (device);
}
