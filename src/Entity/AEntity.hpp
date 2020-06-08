#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "IEntity.hpp"

class AEntity : public IEntity
{
private:
    /* data */
public:
    AEntity();
    ~AEntity();
    virtual void update(void);
    virtual void draw(void);

    virtual void setPos(const irr::core::vector3df pos);
    virtual void getPos(void);
};

#endif