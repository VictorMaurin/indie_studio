#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

enum class State : int
{
    NOTHING,
    GAME,
    MENU,
    GAME_OVER
};

class SceneManager
{
private:
    State statement;
public:
    SceneManager(/* args */);
    ~SceneManager();
    void updateScene(State statement);
    const State &getScene() const;
};

#endif