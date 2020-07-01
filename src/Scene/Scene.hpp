#ifndef SCENE_HPP
#define SCENE_HPP

#include "../Assets/Assets.hpp"

enum State
{
    UNKNOWN,
    GAME,
    MENU,
    GAME_OVER
};

class Scene
{
private:
    State _gameState;
    std::wstring _gameOverStr;
    unsigned int gameOverTimerBgn;

    std::shared_ptr<Assets> _assets;
    std::shared_ptr<Irrlicht> _irr;
public:
    Scene();
    Scene(std::shared_ptr<Assets> assets, std::shared_ptr<Irrlicht> irr);
    ~Scene();
    void menuScene();
    void gameScene();
    void gameOverScene();
    void initGameOverScene(int playersLeft, int indexLastPlayer);

    State getGameState(void) const;
};

#endif