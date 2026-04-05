#include "ConsoleEngine.h"
#include "Window.h"

void ConsoleEngine::run(std::unique_ptr<Scene> startingLevel)
{
    start(std::move(startingLevel));
    update();
    cleanup();
}

void ConsoleEngine::handleInput()
{
    //if (GetKeyState('P') & 0x8000) running = false;
}

void ConsoleEngine::start(std::unique_ptr<Scene> startingLevel)
{
    lastFrame = std::chrono::steady_clock::now();
    assetManager = std::make_unique<AssetManager>();
    inputManager = std::make_unique<InputManager>();
    engineContext = EngineContext{ 0, fixedDeltaTime, inputManager.get(), assetManager.get()};
	renderer = std::make_unique<ConsoleRenderer>(206, 60);
    currentScene = std::move(startingLevel);
	viewportInfo = ViewportInfo{ renderer->getLogicalWidth(), renderer->getLogicalHeight() };
    currentScene->start(viewportInfo, engineContext);
}

void ConsoleEngine::update()
{
    while (isRunning())
    {
        HandleTime();

        Camera& camera = currentScene->getCamera();

        if (renderer->hasWindowResized())
        {
            viewportInfo = ViewportInfo{ renderer->getLogicalWidth(), renderer->getLogicalHeight() };
            currentScene->handleResize(viewportInfo);
        }
        
		engineContext.deltaTime = deltaTime;

        handleInput();
        renderer->clear();
		int attempts = 0;
        while (accumulator >= fixedDeltaTime && attempts < maxFixedUpdatesPerFrame)
        {
            currentScene->fixedUpdate(engineContext);
            accumulator -= fixedDeltaTime;
            attempts++;
		}

        currentScene->update(engineContext);
        QueueSceneSpritesToDraw();
        renderer->present(camera);
    }
}

void ConsoleEngine::QueueSceneSpritesToDraw()
{
    for (size_t i = 0; i < currentScene->getBackgroundTilesToRender().size(); i++)
    {
        renderer->queueDraw(
            currentScene->getBackgroundTilesToRender()[i].sprite,
            currentScene->getBackgroundTilesToRender()[i].worldX,
            currentScene->getBackgroundTilesToRender()[i].worldY,
            currentScene->getBackgroundTilesToRender()[i].flip
        );
    }
    for (size_t i = 0; i < currentScene->getTopTilesToRender().size(); i++)
    {
        renderer->queueDraw(
            currentScene->getTopTilesToRender()[i].sprite,
            currentScene->getTopTilesToRender()[i].worldX,
            currentScene->getTopTilesToRender()[i].worldY,
            currentScene->getTopTilesToRender()[i].flip
        );
    }
    for (size_t i = 0; i < currentScene->getEntitiesToRender().size(); i++)
    {
        renderer->queueDraw(
            currentScene->getEntitiesToRender()[i].sprite,
            currentScene->getEntitiesToRender()[i].worldX,
            currentScene->getEntitiesToRender()[i].worldY,
            currentScene->getEntitiesToRender()[i].flip
        );
    }
}

void ConsoleEngine::HandleTime()
{
    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration<float>(now - lastFrame).count();
    lastFrame = now;
	accumulator += deltaTime;
}

void ConsoleEngine::cleanup()
{
    currentScene->destroy(engineContext);
}
