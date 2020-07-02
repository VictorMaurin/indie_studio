/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Breakable
*/

#include "Breakable.hpp"

Breakable::Breakable(std::shared_ptr<Irrlicht> irr) : Mesh("crate3.obj", "crate3.png", irr)
{
    if (!irr || !irr.get())
        throw MyException("unexpected argument", "Breakable.cpp", 13, "Breakable::update()");
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