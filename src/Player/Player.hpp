#include <irrlicht.h>
#include "driverChoice.h"
#include "../Entity/IEntity.hpp"
#include "../Event/Event.hpp"
#include "../assets/assets.hpp"
#include "../bomb/Bomb.hpp"

class Player : public IEntity
{
public:
	//Player() {};
	Player(std::string meshName, std::string textureName, Core *core,
		irr::EKEY_CODE advance, irr::EKEY_CODE behind, irr::EKEY_CODE left, irr::EKEY_CODE right);
	~Player();
	void initPlayer(std::string meshName, std::string textureName, irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver);
	void movementPlayer(irr::core::array<irr::SJoystickInfo>& joystickInfo, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void initJoystic(irr::core::array<irr::SJoystickInfo> &joystickInfo, irr::IrrlichtDevice* device);
	void movementPlayerJoystick(irr::core::array<irr::SJoystickInfo> &joystickInfo, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void movementPlayerMouse(MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void plantbomb();

	void update(void);
	void draw(void) const;
	void setPosition(const irr::core::vector3df& pos);
	irr::core::vector3df getPosition(void) const;
	void setScale(const irr::core::vector3df& scale);
	irr::core::vector3df getScale(void) const;
private:
	MyEventReceiver* _receiver;
	Core* _core;
	irr::scene::IAnimatedMeshSceneNode* PlayerOBJ;
	int joysticActivated;
	irr::IrrlichtDevice* _device;
	irr::video::IVideoDriver* _driver;
	irr::f32 MOVEMENT_SPEED;
	irr::u32 then;
	irr::core::array<irr::SJoystickInfo> _joystickInfo;
	irr::EKEY_CODE _advance;
	irr::EKEY_CODE _behind;
	irr::EKEY_CODE _left;
	irr::EKEY_CODE _right;
	std::vector<std::shared_ptr<IEntity>> _entities;

};