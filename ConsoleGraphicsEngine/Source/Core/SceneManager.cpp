#include "SceneManager.h"

void SceneManager::loadScene(SceneFactory newSceneFactory)
{
	if (currentScene != nullptr)
	{
		pendingSceneFactory = newSceneFactory;
		return;
	}

	currentSceneFactory = newSceneFactory;
	currentScene = currentSceneFactory();
}

void SceneManager::reloadScene()
{
	pendingSceneFactory = currentSceneFactory;
}

bool SceneManager::processSceneRequest(ViewportInfo& viewport, EngineContext& engineContext)
{
	if (pendingSceneFactory == nullptr) return false;

	currentScene->destroy(engineContext);
	currentScene.reset();
	currentSceneFactory = pendingSceneFactory;
	currentScene = currentSceneFactory();
	currentScene->start(viewport, engineContext);

	pendingSceneFactory = nullptr;
	return true;
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene.get();
}
