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
    auto backgroundTiles = currentScene->getBackgroundTilesToRender();
    for (size_t i = 0; i < backgroundTiles.size(); i++)
    {
        renderer->queueDraw(
            backgroundTiles[i].sprite,
            backgroundTiles[i].worldX,
            backgroundTiles[i].worldY,
            backgroundTiles[i].flip
        );
    }
    auto topTiles = currentScene->getTopTilesToRender();
    for (size_t i = 0; i < topTiles.size(); i++)
    {
        renderer->queueDraw(
            topTiles[i].sprite,
            topTiles[i].worldX,
            topTiles[i].worldY,
            topTiles[i].flip
        );
    }
    auto entitiesSprites = currentScene->getEntitiesToRender();
    for (size_t i = 0; i < entitiesSprites.size(); i++)
    {
        renderer->queueDraw(
            entitiesSprites[i].sprite,
            entitiesSprites[i].worldX,
            entitiesSprites[i].worldY,
            entitiesSprites[i].flip
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
