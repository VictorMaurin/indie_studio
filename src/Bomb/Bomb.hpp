#ifndef BOMB_HPP
#define BOMB_HPP

#include "../Core/Core.hpp"
#include "../Player/Player.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Explosion/Explosion.hpp"
#include "irrlicht.h"
using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

#include "../Entity/IEntity.hpp"

class Bomb : public IEntity
{
private:
    IVideoDriver *driver;
    IrrlichtDevice *device;
    ISceneManager *smgr;
    IMesh *mesh;
    IMeshSceneNode *node;
    u32 now;
    IParticleEmitter *em;
    IParticleAffector *paf;
    Core *core;
public : 
    Bomb(Core *core, vector3df pos);
    ~Bomb();
    void createExplodeCube();
    void update(void);
    void draw(void) const;
    void explode();
    void setPos(const irr::core::vector3df pos);
    vector3df getPos(void) const;
};

#endif