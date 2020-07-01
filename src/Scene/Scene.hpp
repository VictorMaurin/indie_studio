#ifndef SCENE_HPP
#define SCENE_HPP

class Menu;

#include "../Assets/Assets.hpp"
#include "../Menu/Menu.hpp"

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
    std::shared_ptr<Menu> _menu;
    std::shared_ptr<Assets> _assets;
    std::shared_ptr<Irrlicht> _irr;
public:
    Scene();
    Scene(std::shared_ptr<Assets> assets, std::shared_ptr<Irrlicht> irr);
    ~Scene();
    void menuScene();
    void initMenu();
    void gameScene();
    void startGame();
    void gameOverScene();
    void initGameOverScene(int playersLeft, int indexLastPlayer);

    State getGameState(void) const;
};

#endif