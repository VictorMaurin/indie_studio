#ifndef FIREUP_HPP
#define FIREUP_HPP

#include "IPowerUp.hpp"
#include "../Map/GameMap.hpp"

class FireUp : public IEntity, public IPowerUp
{
private:
    vector3df pos;

public:
    FireUp(/* args */);
    ~FireUp();
    void update();
    void draw(void) const;

    void setPosition(const vector3df &pos);
    vector3df getPosition(void) const;
    void setScale(const vector3df &scale);
    vector3df getScale(void) const;
    IMesh *getMesh() const;
    IMeshSceneNode *getNode() const;
};

#endif