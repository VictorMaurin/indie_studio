#ifndef FIREUP_HPP
#define FIREUP_HPP

#include "IPowerUp.hpp"

class FireUp : public IEntity : public IPowerUp
{
private:
    vector3df pos;

public:
    FireUp(/* args */);
    ~FireUp();
};

#endif