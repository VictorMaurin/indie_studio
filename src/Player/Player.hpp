#ifndef PLAYER_HPP
#define PLAYER_HPP

class Core;
class IEntity;

#include "driverChoice.h"
#include <irrlicht.h>
#include <fstream>

#include "../Bomb/Bomb.hpp"
#include "../Event/Event.hpp"
#include "../assets/assets.hpp"

using namespace irr;
using namespace scene;
using namespace gui;
using namespace video;
using namespace core;

class Player : public IEntity
{
public:
	Player(std::string meshName, std::string textureName, Core* core, irr::EKEY_CODE advance, irr::EKEY_CODE behind, irr::EKEY_CODE left, irr::EKEY_CODE right, irr::EKEY_CODE plantBomb);
	~Player();
	void initPlayer(std::string meshName, std::string textureName, irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver);
	void movementPlayer(std::shared_ptr<GameMap> map, irr::core::array<irr::SJoystickInfo>& joystickInfo, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void initJoystic(irr::core::array<irr::SJoystickInfo> &joystickInfo, irr::IrrlichtDevice* device);
	void movementPlayerJoystick(std::shared_ptr<GameMap> map, irr::core::array<irr::SJoystickInfo> &joystickInfo, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void movementPlayerKeyBoard(std::shared_ptr<GameMap> map, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void plantBomb();

	void update(std::shared_ptr<GameMap> map);
	void draw(void) const;
	void remove(void);
	void canCollide(bool);
    bool isBreakable(void);
	void setPosition(const irr::core::vector3df& pos);
	irr::core::vector3df getPosition(void) const;
	void setScale(const irr::core::vector3df& scale);
	irr::core::vector3df getScale(void) const;
	void setTexture(std::string assets) {};
private:
	MyEventReceiver* _receiver;
	Core* _core;
	irr::scene::IAnimatedMeshSceneNode* PlayerOBJ;
	int joysticActivated;
	irr::IrrlichtDevice* _device;
	irr::f32 MOVEMENT_SPEED;
	irr::u32 then;
	irr::core::array<irr::SJoystickInfo> _joystickInfo;
	irr::EKEY_CODE _advance;
	irr::EKEY_CODE _behind;
	irr::EKEY_CODE _left;
	irr::EKEY_CODE _right;
	irr::EKEY_CODE _plantBomb;
	bool isRemove = false;
};
#endif