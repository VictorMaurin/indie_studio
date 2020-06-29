/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

class PlayerEvent;

#include "driverChoice.h"
#include <irrlicht.h>
#include <fstream>

#include "../Irrlicht/Irrlicht.hpp"
#include "../Assets/Assets.hpp"
#include "../Event/Event.hpp"
#include "../../assets/assets.hpp"
#include "../PlayerEvent/PlayerEvent.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Player : public IEntity
{
public:
	Player(std::string meshName, std::string textureName, std::shared_ptr<Irrlicht> irr, irr::EKEY_CODE advance, irr::EKEY_CODE behind, irr::EKEY_CODE left, irr::EKEY_CODE right, irr::EKEY_CODE plantBomb);
	~Player();
	void initPlayer(std::string meshName, std::string textureName, irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver);

	void moveUpKeyboard(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime);
	void moveDownKeyboard(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime);
	void moveRightKeyboard(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime);
	void moveLeftKeyboard(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime);

	void moveUpControler(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime, irr::f32 moveVertical);
	void moveDownControler(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime, irr::f32 moveVertical);
	void moveRightControler(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime, irr::f32 moveHorizontal);
	void moveLeftControler(line3df ray, vector3df intersection, triangle3df hitTriangle, vector3df nodePosition, const irr::f32 frameDeltaTime, irr::f32 moveHorizontal);

	void plantBomb(std::shared_ptr<GameMap> map, std::shared_ptr<std::vector<std::shared_ptr<IEntity>>> entities);


	void update(std::shared_ptr<GameMap> map, std::shared_ptr<Assets> assets);
	void remove(void);
	void canCollide(bool);
    bool isBreakable(void);
	void setPosition(const irr::core::vector3df& pos);
	irr::core::vector3df getPosition(void) const;
	void setScale(const irr::core::vector3df& scale);
	irr::core::vector3df getScale(void) const;
	void setTexture(std::string assets) {};
	void SetIsAI(bool isAI);
	irr::scene::IAnimatedMeshSceneNode* getPlayerOBJ();
private:
	// std::shared_ptr<MyEventReceiver> _receiver;
	std::shared_ptr<Irrlicht> _irr;
	irr::scene::IAnimatedMeshSceneNode* PlayerOBJ;
	int joysticActivated;
	std::unique_ptr<PlayerEvent> event;
	// std::shared_ptr<irr::IrrlichtDevice> _device;
	irr::f32 MOVEMENT_SPEED;
	irr::u32 then;
	// irr::core::array<irr::SJoystickInfo> _joystickInfo;
	irr::EKEY_CODE _advance;
	irr::EKEY_CODE _behind;
	irr::EKEY_CODE _left;
	irr::EKEY_CODE _right;
	irr::EKEY_CODE _plantBomb;
	bool isRemove = false;
	bool isAI = false;
};
#endif