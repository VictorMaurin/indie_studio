#ifndef PLAYER_HPP
#define PLAYER_HPP

class Core;
class IEntity;
class GameMap;
class Mesh;

#include "driverChoice.h"
#include <irrlicht.h>
#include <fstream>

#include "../Event/Event.hpp"
#include "../assets/assets.hpp"
#include "../Map/GameMap.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Player : public IEntity
{
public:
	Player(std::string meshName, std::string textureName, std::shared_ptr<Core> core, irr::EKEY_CODE advance, irr::EKEY_CODE behind, irr::EKEY_CODE left, irr::EKEY_CODE right, irr::EKEY_CODE plantBomb);
	~Player();
	void initPlayer(std::string meshName, std::string textureName, std::shared_ptr<ISceneManager> sceneManager, std::shared_ptr<IVideoDriver> driver);
	void movementPlayer(std::shared_ptr<GameMap> map, irr::core::array<irr::SJoystickInfo>& joystickInfo, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void initJoystic(irr::core::array<irr::SJoystickInfo> &joystickInfo, std::shared_ptr<IrrlichtDevice> device);
	void movementPlayerJoystick(std::shared_ptr<GameMap> map, irr::core::array<irr::SJoystickInfo> &joystickInfo, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void movementPlayerKeyBoard(std::shared_ptr<GameMap> map, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void plantBomb(std::shared_ptr<GameMap> map);

	void update();
	void draw(void) const;
	void remove(void);
	void canCollide(bool);
    bool isBreakable(void);
	void setPosition(const irr::core::vector3df& pos);
	irr::core::vector3df getPosition(void) const;
	void setScale(const irr::core::vector3df& scale);
	irr::core::vector3df getScale(void) const;
	void setTexture(std::string assets) {};
	void SetIsAI(bool isAI);
private:
	MyEventReceiver* _receiver;
	std::shared_ptr<Core> _core;
	scene::IAnimatedMeshSceneNode* PlayerOBJ;
	int joysticActivated;
	std::shared_ptr<IrrlichtDevice> _device;
	f32 MOVEMENT_SPEED;
	u32 then;
	irr::core::array<irr::SJoystickInfo> _joystickInfo;
	EKEY_CODE _advance;
	EKEY_CODE _behind;
	EKEY_CODE _left;
	EKEY_CODE _right;
	EKEY_CODE _plantBomb;
	bool isRemove = false;
	bool isAI = false;
};
#endif