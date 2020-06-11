#ifndef BOMBE_HPP
#define BOMBE_HPP

#include "../Core/Core.hpp"
#include "../Player/Player.hpp"
#include "../Mesh/Mesh.hpp"
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
    vector3df pos;
    u32 now;
    IParticleEmitter *em;
    IParticleAffector *paf;
public : 
    Bomb(Core core, Player player);
    ~Bomb();
    void createExplodeCube();
    void update(void);
    void draw(void) const;
    void explode();
    void setPos(const irr::core::vector3df pos);
    void getPos(void) const;
};

#endif