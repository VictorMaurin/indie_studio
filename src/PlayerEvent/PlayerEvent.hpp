/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerEvent
*/

#ifndef PLAYEREVENT_HPP
#define PLAYEREVENT_HPP

class Player;

#include "Player/Player.hpp"

class PlayerEvent
{
public:
	PlayerEvent(std::shared_ptr<Irrlicht> irr, irr::EKEY_CODE advance, irr::EKEY_CODE behind, irr::EKEY_CODE left, irr::EKEY_CODE right, irr::EKEY_CODE plantBomb, Player* _player);
	~PlayerEvent();

	void movementPlayer(std::shared_ptr<GameMap> map, const irr::f32 frameDeltaTime);
	void movementPlayerJoystick(std::shared_ptr<GameMap> map, const irr::f32 frameDeltaTime);
	void movementPlayerKeyBoard(std::shared_ptr<GameMap> map, const irr::f32 frameDeltaTime);
	void plantBomb(std::shared_ptr<GameMap> map, std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities);

	bool isJoystickActivated(void) const;
private:
	irr::EKEY_CODE _advance;
	irr::EKEY_CODE _behind;
	irr::EKEY_CODE _left;
	irr::EKEY_CODE _right;
	irr::EKEY_CODE _plantBomb;

	int joysticActivated;
	Player* player;
	std::shared_ptr<Irrlicht> _irr;
};

#endif /* !PLAYEREVENT_HPP */