#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <irrlicht.h>

#include "../Core/Core.hpp"
#include "../../assets/assets.hpp"

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
    Core *_core;
    u32 now;
    u32 then;

public : 
    Explosion(Core *core, const vector3df &pos);
    ~Explosion();

    void remove(void);
    bool isBreakable(void);
    void update(std::shared_ptr<GameMap> map);
    void draw(void) const;
    void canCollide(bool);
    void setPosition(const irr::core::vector3df &pos);
    irr::core::vector3df getPosition(void) const;
    void setScale(const irr::core::vector3df &scale);
    irr::core::vector3df getScale(void) const;
    void setTexture(std::string assets) {};
};

#endif