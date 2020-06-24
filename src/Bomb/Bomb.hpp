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

class Bomb : public Mesh {
    private:
        std::shared_ptr<IVideoDriver> driver;
        std::shared_ptr<IrrlichtDevice> device;
        std::shared_ptr<ISceneManager> smgr;
        // IMeshSceneNode *node;
        u32 now;
        u32 then;
        IParticleEmitter *em;
        IParticleAffector *paf;
        std::shared_ptr<Core> _core;
        // std::unique_ptr<Mesh> mesh;
        bool passed = false;
        vector3df posFloat;

    public : 
        Bomb(std::shared_ptr<Core> core, vector3df pos);
        ~Bomb();
        void SetIsAI(bool isAI){};
        void returnToGreen(std::string asset);
        void createExplodeCube();
        void update();
        void draw(void) const;
        void explode(std::string asset);
        // void remove(void);
        bool isBreakable(void);
        void canCollide(bool);

        // void setPosition(const irr::core::vector3df &pos);
        // irr::core::vector3df getPosition(void) const;
        // void setScale(const irr::core::vector3df &scale);
        // irr::core::vector3df getScale(void) const;
        void setTexture(std::string assets) {};
};

#endif