#ifndef WALLPASS_HPP
#define WALLPASS_HPP

#include "IPowerUp.hpp"

class WallPass : public IEntity : public IPowerUp
{
private:
    vector3df pos;
public:
    WallPass(/* args */);
    ~WallPass();
};

#endif