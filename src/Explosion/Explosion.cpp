#include "Explosion.hpp"

Explosion::Explosion(Core *core, vector3df pos)
{
    smgr = core->getSmgr();
    device = core->getDevice();
    driver = core->getDriver();
    ps = smgr->addParticleSystemSceneNode(false);

    em = ps->createBoxEmitter(
        core::aabbox3d<f32>(0, 0, 0, 0, 1, 1), // emitter size
        core::vector3df(0.0f, 0.01f, 0.0f),    // initial direction
        5, 5,                                  // emit rate
        video::SColor(0, 255, 255, 255),       // darkest color
        video::SColor(0, 255, 255, 255),       // brightest color
        800, 1000, 0,                          // min and max age, angle
        core::dimension2df(5.f, 5.f),          // min size
        core::dimension2df(5.f, 5.f));         // max size

    ps->setEmitter(em); // this grabs the emitter
    em->drop();         // so we can drop it here without deleting it

    scene::IParticleAffector *paf = ps->createFadeOutParticleAffector();

    ps->addAffector(paf); // same goes for the affector
    paf->drop();

    // ps->setPosition(core::vector3df(0, 0, 40));
    ps->setScale(vector3df(0.01, 0.01, 0.01));
    ps->setMaterialFlag(video::EMF_LIGHTING, false);
    ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    ps->setMaterialTexture(0, driver->getTexture("assets/fire.bmp"));
    ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    vector3df temp = pos;
    temp.X += 3;
    ps->setPosition(temp);
}

Explosion::~Explosion()
{

}

void Explosion::setPosition(const irr::core::vector3df &pos)
{
    ps->setPosition(pos);
}

irr::core::vector3df Explosion::getPosition() const
{
    return (ps->getPosition());
}

void Explosion::setScale(const irr::core::vector3df &scale)
{
    ps->setScale(scale);
}

vector3df Explosion::getScale()
{
    return (ps->getScale());
}

void Explosion::canCollide(__attribute__((unused)) bool b)
{

}