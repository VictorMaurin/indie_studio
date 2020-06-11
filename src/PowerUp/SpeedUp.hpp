#ifndef SPEEDUP_HPP
#define SPEEDUP_HPP

#include "IPowerUp.hpp"

class SpeedUp : public IEntity, public IPowerUp
{
private:
    vector3df pos;

public:
    SpeedUp(/* args */);
    ~SpeedUp();
    void update(void);
    void draw(void) const;

    void setPosition(const vector3df &pos);
    vector3df getPosition(void) const;
    void setScale(const vector3df &scale);
    vector3df getScale(void) const;
    IMesh *getMesh() const;
    IMeshSceneNode *getNode() const;
};

#endif