#ifndef IENTITY_HPP
#define IENTITY_HPP

#include <vector>
#include "irrlicht.h"


class IEntity
{
public:
    virtual ~IEntity() = default;

    virtual void update(void)=0;
    virtual void draw(void) const = 0;

    virtual void setPosition(const irr::core::vector3df &pos)=0;
    virtual irr::core::vector3df getPosition(void) const = 0;
};

#endif /* IENTITY_HPP */
