#ifndef SPEEDUP_HPP
#define SPEEDUP_HPP

#include "IPowerUp.hpp"
#include "../Map/Map.hpp"

class SpeedUp : public IEntity, public IPowerUp
{
private:
    vector3df pos;

public:
    SpeedUp(/* args */);
    ~SpeedUp();
    void update(std::shared_ptr<GameMap> map);
    void draw(void) const;

    void setPosition(const vector3df &pos);
    vector3df getPosition(void) const;
    void setScale(const vector3df &scale);
    vector3df getScale(void) const;
    IMesh *getMesh() const;
    IMeshSceneNode *getNode() const;
};

#endif