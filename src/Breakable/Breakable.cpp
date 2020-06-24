/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Breakable
*/

#include "Breakable.hpp"

Breakable::Breakable(std::shared_ptr<Core> core, std::shared_ptr<ISceneManager> smgr, std::shared_ptr<IVideoDriver> driver, std::shared_ptr<IrrlichtDevice> device)
 : Mesh("crate3.obj", "crate3.png", core, smgr, driver, device)
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