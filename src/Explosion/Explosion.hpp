#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <irrlicht.h>

#include "../Core/Core.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Explosion : public IEntity
{
private:
    vector3df pos;
    IParticleSystemSceneNode *ps;
    IParticleEmitter *em;
    IVideoDriver *driver;
    IrrlichtDevice *device;
    ISceneManager *smgr;

public : 
    Explosion(Core *core, vector3df pos);
    ~Explosion();
    void setPosition(const vector3df &pos);
    vector3df getPosition(void) const;
    void setScale(const vector3df &scale);
    vector3df getScale(void);
    void canCollide(bool);
};

#endif