#include "Explosion.hpp"

Explosion::Explosion(Core *core, const vector3df &pos)
{
    _core = core;
    smgr = _core->getSmgr();
    device = _core->getDevice();
    driver = _core->getDriver();
    ps = smgr->addParticleSystemSceneNode(false);

    em = ps->createBoxEmitter(
        core::aabbox3d<f32>(0, 0, 0, 0, 0, 0), // emitter size
        core::vector3df(0.0f, 0.01f, 0.0f),    // initial direction
        5, 5,                                  // emit rate
        video::SColor(0, 255, 255, 255),       // darkest color
        video::SColor(0, 255, 255, 255),       // brightest color
        300, 200, 0,                          // min and max age, angle
        core::dimension2df(5.f, 5.f),          // min size
        core::dimension2df(5.f, 5.f));         // max size

    ps->setEmitter(em); // this grabs the emitter
    em->drop();         // so we can drop it here without deleting it

    scene::IParticleAffector *paf = ps->createFadeOutParticleAffector();

    ps->addAffector(paf); // same goes for the affector
    paf->drop();

    // ps->setPosition(core::vector3df(0, 0, 40));
    ps->setScale(vector3df(0.002, 0.002, 0.002));
    ps->setMaterialFlag(video::EMF_LIGHTING, false);
    ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    std::string asset = findAsset("fire.bmp");
    ps->setMaterialTexture(0, driver->getTexture(asset.c_str()));
    if (!ps)
        throw "cannot open particle";
    ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    ps->setPosition(pos);
}

Explosion::~Explosion()
{

}

void Explosion::remove()
{

}

bool Explosion::isBreakable()
{

}

void Explosion::update()
{
    std::cout << "update" << std::endl;
}

void Explosion::draw() const
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

irr::core::vector3df Explosion::getScale() const
{
    return (ps->getScale());
}