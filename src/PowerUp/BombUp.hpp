#ifndef BOMBUP_HPP
#define BOMBUP_HPP

#include "IPowerUp.hpp"

class BombUp : public IEntity : public IPowerUp
{
private:
    vector3df pos;

public:
    BombUp(/* args */);
    ~BombUp();
};

#endif