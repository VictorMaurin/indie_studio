#include <irrlicht.h>
#include "driverChoice.h"
#include "../Entity/IEntity.hpp"
#include "../Event/Event.hpp"*
#include <memory>

class Player : public IEntity
{
public:
	Player();
	~Player();
	void initPlayer(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver);
	void movementPlayer(MyEventReceiver receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);
	void initJoystic(irr::core::array<irr::SJoystickInfo> &joystickInfo, irr::IrrlichtDevice* device);
	void movementPlayerJoystick(irr::core::array<irr::SJoystickInfo> &joystickInfo, MyEventReceiver receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);

	void update(void);
	void draw(void) const;

	void setPosition(const irr::core::vector3df& pos);
	irr::core::vector3df getPosition(void) const;
	void setScale(const irr::core::vector3df& scale);
	irr::core::vector3df getScale(void) const;
	irr::scene::IAnimatedMeshSceneNode* PlayerOBJ;
private:

};