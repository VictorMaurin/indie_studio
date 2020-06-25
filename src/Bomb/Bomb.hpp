#ifndef BOMB_HPP
#define BOMB_HPP

class Mesh;

#include <irrlicht.h>

#include "../Core/Core.hpp"
#include "../Mesh/Mesh.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Bomb : public IEntity
{
private:
    IVideoDriver *driver;
    std::shared_ptr<IrrlichtDevice> device;
    ISceneManager *smgr;
    IMeshSceneNode *node;
    u32 now;
    u32 then;
    IParticleEmitter *em;
    IParticleAffector *paf;
    Core *_core;
    std::unique_ptr<Mesh> mesh;
    bool passed = false;
    vector3df posFloat;

public : 
    Bomb(Core *core, vector3df pos);
    ~Bomb();
    void SetIsAI(bool isAI){};
    void returnToGreen(std::shared_ptr<GameMap> map, std::string asset);
    void createExplodeCube();
    void update(std::shared_ptr<GameMap> map);
    void draw(void) const;
    void explode(std::shared_ptr<GameMap> map, std::string asset);
    void remove(void);
    bool isBreakable(void);
    void canCollide(bool);

    void setPosition(const irr::core::vector3df &pos);
    irr::core::vector3df getPosition(void) const;
    void setScale(const irr::core::vector3df &scale);
    irr::core::vector3df getScale(void) const;
    void setTexture(std::string assets) {};
};

#endif