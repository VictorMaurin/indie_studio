#ifndef SPEEDUP_HPP
#define SPEEDUP_HPP

#include "IPowerUp.hpp"

class SpeedUp : public IEntity : public IPowerUp
{
private:
    vector3df pos;

public:
    SpeedUp(/* args */);
    ~SpeedUp();
};

#endif