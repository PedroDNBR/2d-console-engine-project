#include <windows.h>
#include <vector>
#include <chrono>
#include "../Sprite/Sprite.h"
#include "../World/Scene.h"
#include "../World/Camera.h"
#include "../Core/ConsoleRenderer.h"

class ConsoleEngine {
private:
    
    bool running = true;
    std::chrono::steady_clock::time_point lastFrame;
    float deltaTime = 0.0f;
    std::unique_ptr<ConsoleRenderer> renderer;

public:
    std::unique_ptr<Scene> currentScene;
    bool isRunning() const { return running; }
    void handleInput();
    void start();
    void update();
    void cleanup();
};