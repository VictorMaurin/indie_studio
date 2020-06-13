#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "../Entity/IEntity.hpp"
#include "../Core/Core.hpp"
#include "../../assets/assets.hpp"

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
    Core *_core;
    u32 now;
    u32 then;

public : 
    Explosion(Core *core, const vector3df &pos);
    ~Explosion();
    void remove(void);
    bool isBreakable(void);
    void update(void);
    void draw(void) const;
    void setPosition(const irr::core::vector3df &pos);
    irr::core::vector3df getPosition(void) const;
    void setScale(const irr::core::vector3df &scale);
    irr::core::vector3df getScale(void) const;
};

#endif