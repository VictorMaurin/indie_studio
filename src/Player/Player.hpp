#include <irrlicht.h>
#include "driverChoice.h"
#include "../Entity/AEntity.hpp"
//#include <iostream>

class Player : public AEntity
{
public:
	Player();
	~Player();
	void initPlayer(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver);
	irr::scene::IAnimatedMeshSceneNode* PlayerOBJ;
private:

};