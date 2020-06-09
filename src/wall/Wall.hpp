#ifndef WALL_HPP
#define WALL_HPP

#include <irrlicht.h>
#include <memory>
#include "../Entity/AEntity.hpp"
#include "../Core/Core.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Wall : public AEntity
{
    public:
        Wall(ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device);
        ~Wall();

        void update(void);
        void draw(void) const;

        void setPosition(const vector3df &pos);

    private:
        IMesh *mesh;
        IMeshSceneNode *node;
};

#endif /* WALL_HPP */