#ifndef IENTITY_HPP
#define IENTITY_HPP

#include <vector>
#include <irrlicht/irrlicht.h>


class IEntity
{
public:
    virtual ~IEntity() = default;

    virtual void update(void)=0;
    virtual void draw(void) const = 0;

    virtual void setPos(const irr::core::vector3df pos)=0;
    virtual void getPos(void) const = 0;
};

std::vector<IEntity> entities;

#endif /* IENTITY_HPP */