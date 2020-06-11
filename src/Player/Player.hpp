#include <irrlicht.h>
#include "driverChoice.h"
#include "../Entity/IEntity.hpp"
#include "../Event/Event.hpp"
#include "../assets/assets.hpp"
#include "../Bomb/Bomb.hpp"

class Player : public IEntity
{
public:
	Player(std::string meshName, std::string textureName, irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, irr::IrrlichtDevice* device, irr::core::array<irr::SJoystickInfo> joystickInfo, MyEventReceiver* receiver, irr::EKEY_CODE advance, irr::EKEY_CODE behind, irr::EKEY_CODE left, irr::EKEY_CODE right);
	~Player();
	void initPlayer(std::string meshName, std::string textureName, irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver);
	void movementPlayer(irr::core::array<irr::SJoystickInfo>& joystickInfo, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void initJoystic(irr::core::array<irr::SJoystickInfo> &joystickInfo, irr::IrrlichtDevice* device);
	void movementPlayerJoystick(irr::core::array<irr::SJoystickInfo> &joystickInfo, MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void movementPlayerMouse(MyEventReceiver* receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);

	void update(void);
	void draw(void) const;
	void setPosition(const irr::core::vector3df& pos);
	irr::core::vector3df getPosition(void) const;
	void setScale(const irr::core::vector3df& scale);
	irr::core::vector3df getScale(void) const;
private:
	MyEventReceiver* _receiver;
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

};