#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "../Entity/IEntity.hpp"
#include "../Core/Core.hpp"

class Core;

class Explosion : public IEntity
{
private:
    vector3df pos;
    scene::IParticleSystemSceneNode *ps;
    scene::IParticleEmitter *em;
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
};

#endif