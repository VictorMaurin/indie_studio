/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Breakable
*/

#include "Breakable.hpp"

Breakable::Breakable(Core *core, ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device) : Mesh("crate3.obj", "crate3.png", core, smgr, driver, device)
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