#pragma once
#include <memory>
#include <functional>
#include "ViewportInfo.h"
#include "../World/Scene.h"

using SceneFactory = std::function<std::unique_ptr<Scene>()>;

class SceneManager
{

public:
    void loadScene(SceneFactory newSceneFactory);
    void reloadScene();
    bool processSceneRequest(ViewportInfo& viewport, EngineContext& engineContext);
    Scene* getCurrentScene();

private:
    std::unique_ptr<Scene> currentScene;
	SceneFactory currentSceneFactory;

    SceneFactory pendingSceneFactory;

};

