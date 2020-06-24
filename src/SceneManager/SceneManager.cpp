#include "SceneManager.hpp"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::updateScene(State statement)
{
    statement = statement;
}

const State &SceneManager::getScene() const
{
    return (statement);
}