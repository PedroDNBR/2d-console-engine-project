#pragma once
#include <vector>
#include <chrono>
#include "InputManager.h"
#include "./Context/EngineContext.h"
#include "../Sprite/Sprite.h"
#include "../World/Scene.h"
#include "../World/Camera.h"
#include "../Core/ConsoleRenderer.h"
#include "AssetManager.h"

class ConsoleEngine {

public:
    void run(std::unique_ptr<Scene> startingLevel);

private:
    std::unique_ptr<Scene> currentScene;
    std::unique_ptr<ConsoleRenderer> renderer;
    std::unique_ptr<InputManager> inputManager;
	std::unique_ptr<AssetManager> assetManager;
    bool isRunning() const { return running; }
    void handleInput();
    void start(std::unique_ptr<Scene> startingLevel);
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