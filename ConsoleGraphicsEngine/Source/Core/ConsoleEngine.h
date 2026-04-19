#pragma once
#include <vector>
#include <chrono>
#include "SceneManager.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "./Context/EngineContext.h"
#include "../Sprite/Sprite.h"
#include "../World/Scene.h"
#include "../Core/ConsoleRenderer.h"
#ifdef _DEBUG
#include "../Core/DebugDraw.h"
#endif

class ConsoleEngine {

public:
    void run(SceneFactory startingSceneFactory);

private:
    std::unique_ptr<ConsoleRenderer> renderer;
    std::unique_ptr<SceneManager> sceneManager;
    std::unique_ptr<InputManager> inputManager;
	std::unique_ptr<AssetManager> assetManager;
#ifdef _DEBUG
    std::unique_ptr<DebugDraw> debugDraw;
#endif

    bool isRunning() const { return running; }
    void handleInput();
    void start();
    void update();
    void QueueSceneSpritesToDraw();
    void HandleTime();
    void cleanup();

	EngineContext engineContext;
	ViewportInfo viewportInfo;
    bool running = true;
    float deltaTime = 0.0f;
	float accumulator = 0.0f;
	const float fixedDeltaTime = 1.0f / 60.0f; // 60 FPS
    std::chrono::steady_clock::time_point lastFrame;
	const int maxFixedUpdatesPerFrame = 4; // To prevent spiral of death

};