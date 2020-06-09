#ifndef WALL_HPP
#define WALL_HPP

#include <irrlicht.h>
#include <memory>
#include "../Entity/IEntity.hpp"
#include "../Core/Core.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Wall : public IEntity
{
    public:
        Wall(ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device);
        ~Wall();

        void update(void);
        void draw(void) const;

        void setPosition(const vector3df &pos);
        vector3df getPosition(void) const;
        void setScale(const vector3df &scale);
        vector3df getScale(void) const;

    private:
        IMesh *mesh;
        IMeshSceneNode *node;
};

#endif /* WALL_HPP */