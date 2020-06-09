#include <irrlicht.h>
#include "driverChoice.h"
#include "../Entity/AEntity.hpp"
#include "../Event/Event.hpp"*
#include <memory>

class Player : public AEntity
{
public:
	Player();
	~Player();
	void initPlayer(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver);
	void movementPlayer(MyEventReceiver receiver, const irr::f32 MOVEMENT_SPEED, const irr::f32 frameDeltaTime);

	irr::core::vector3df getPos();
	void setPos(const irr::core::vector3df pos);
	irr::scene::IAnimatedMeshSceneNode* PlayerOBJ;
private:

};