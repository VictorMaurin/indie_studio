#include <irrlicht/irrlicht.h>
#include <vector>
#include <ctime>
#include <cmath>
#include "Entity/IEntity.hpp"

int main()
{
    std::clock_t frameBgnTime;
    std::clock_t frameEndTime;
    double deltaTime = 0.0;
    size_t fps = 60;
    double frameTime = 1 / fps;
    double remainingTime = 0.0;
    size_t updates = 0;

    //create device
    irr::IrrlichtDevice *device = irr::createDevice( irr::video::EDT_OPENGL, 
    irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, false, 0);
    if (!device)
        return 1;
    device->setWindowCaption(L"Hello world! - Irrlicht Engine Demo");
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    irr::scene::ISceneManager *smgr = device->getSceneManager();
    irr::gui::IGUIEnvironment *guienv = device->getGUIEnvironment();

    //init all (factory ?) and add drawables to the $entities vector

    while (device->run()) {
        frameBgnTime = std::clock();

        // do events

        //update
        for (int i = 0; i < entities.size(); i++) {
            entities[i].update();
        }

        // draw
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();

        frameEndTime = std::clock();

        deltaTime = frameEndTime - frameBgnTime;

        //if the remaining time is > to the time of 1 frame, keep updating the game
        // this fixes the framerate at $fps frames per sec without using sleep() to prevent lags at low fps
        remainingTime = abs((deltaTime / (double)CLOCKS_PER_SEC) - (frameTime / (double)CLOCKS_PER_SEC));
        updates = 0;
        while (frameTime > remainingTime) {
            frameBgnTime = std::clock();
            if (updates < 5) {
                updates++;
                for (int i = 0; i < entities.size(); i++)
                    entities[i].update();
            }
            deltaTime = std::clock() - frameBgnTime;
            remainingTime -= deltaTime * (double)CLOCKS_PER_SEC;
        }
    }

    return (0);
}