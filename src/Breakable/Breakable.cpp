/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Breakable
*/

#include "Breakable.hpp"

Breakable::Breakable(std::shared_ptr<Irrlicht> irr) : Mesh("crate3.obj", "crate3.png", irr)
{
}

Breakable::~Breakable()
{
    this->spawnPowerUp();
}

void Breakable::spawnPowerUp()
{
    
}

bool Breakable::isBreakable(void)
{
    return (true);
}