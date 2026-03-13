#include "ConsoleEngine.h"
#include "Window.h"

void ConsoleEngine::handleInput()
{
    if (GetKeyState('P') & 0x8000) running = false;
}

void ConsoleEngine::start()
{
    std::vector<std::vector<int>> tile = {
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
     { 1,1,1,1,1,1,1,1,1,1,1,0,1,1,1 },
     { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
    };

	renderer = std::make_unique<ConsoleRenderer>(206, 60);
    currentScene = std::make_unique<Scene>(tile);

    currentScene->start(renderer.get());
    lastFrame = std::chrono::steady_clock::now();
}

void ConsoleEngine::update()
{
    while (isRunning())
    {
        auto now = std::chrono::steady_clock::now();
        deltaTime = std::chrono::duration<float>(now - lastFrame).count();
        lastFrame = now;

        handleInput();
        renderer->clear();
        currentScene->update(renderer.get(), deltaTime);
        renderer->present();
    }
}

void ConsoleEngine::cleanup()
{
    currentScene->destroy();
}
