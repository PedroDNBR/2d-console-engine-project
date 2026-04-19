#include "Window.h"
#include "ConsoleEngine.h"

void ConsoleEngine::run(SceneFactory startingSceneFactory)
{
    sceneManager = std::make_unique<SceneManager>();
    sceneManager->loadScene(startingSceneFactory);
    start();
    update();
    cleanup();
}

void ConsoleEngine::handleInput()
{
    //if (GetKeyState('P') & 0x8000) running = false;
}

void ConsoleEngine::start()
{
    if (sceneManager->getCurrentScene() == nullptr)
        throw new std::runtime_error("No starting scene set in SceneManager");

    lastFrame = std::chrono::steady_clock::now();
    assetManager = std::make_unique<AssetManager>();
    inputManager = std::make_unique<InputManager>();
#ifdef _DEBUG
	 debugDraw = std::make_unique<DebugDraw>();
#endif
    engineContext = EngineContext
    { 
        0, fixedDeltaTime, 
        sceneManager.get(),
        inputManager.get(),
        assetManager.get()
#ifdef _DEBUG
        ,debugDraw.get()
#endif
    };
	renderer = std::make_unique<ConsoleRenderer>(206, 60);
    // currentScene = std::move(startingLevel);
	viewportInfo = ViewportInfo{ renderer->getLogicalWidth(), renderer->getLogicalHeight() };

    sceneManager->getCurrentScene()->start(viewportInfo, engineContext);
}

void ConsoleEngine::update()
{
    while (isRunning())
    {
        HandleTime();

        Camera& camera = sceneManager->getCurrentScene()->getCamera();

        if (renderer->hasWindowResized())
        {
            viewportInfo = ViewportInfo{ renderer->getLogicalWidth(), renderer->getLogicalHeight() };
            sceneManager->getCurrentScene()->handleResize(viewportInfo);
        }
        
		engineContext.deltaTime = deltaTime;

        handleInput();
        renderer->clear();
		int attempts = 0;
        while (accumulator >= fixedDeltaTime && attempts < maxFixedUpdatesPerFrame)
        {
            sceneManager->getCurrentScene()->fixedUpdate(engineContext);
            accumulator -= fixedDeltaTime;
            attempts++;
        }

        sceneManager->getCurrentScene()->update(engineContext);
        QueueSceneSpritesToDraw();
        renderer->present(camera.x, camera.y);

        if (sceneManager->processSceneRequest(viewportInfo, engineContext))
        {
            accumulator = 0;
            lastFrame = std::chrono::steady_clock::now();
        }
    }
}

void ConsoleEngine::QueueSceneSpritesToDraw()
{
    auto backgroundTiles = sceneManager->getCurrentScene()->getBackgroundTilesToRender();
    for (size_t i = 0; i < backgroundTiles.size(); i++)
    {
        renderer->queueSpriteDraw(
            backgroundTiles[i].sprite,
            backgroundTiles[i].worldX,
            backgroundTiles[i].worldY,
            backgroundTiles[i].flip
        );
    }
    auto topTiles = sceneManager->getCurrentScene()->getTopTilesToRender();
    for (size_t i = 0; i < topTiles.size(); i++)
    {
        renderer->queueSpriteDraw(
            topTiles[i].sprite,
            topTiles[i].worldX,
            topTiles[i].worldY,
            topTiles[i].flip
        );
    }
    auto entitiesSprites = sceneManager->getCurrentScene()->getEntitiesToRender();
    for (size_t i = 0; i < entitiesSprites.size(); i++)
    {
        renderer->queueSpriteDraw(
            entitiesSprites[i].sprite,
            entitiesSprites[i].worldX,
            entitiesSprites[i].worldY,
            entitiesSprites[i].flip
        );
    }

#ifdef _DEBUG
    if (engineContext.debugDraw != nullptr)
    {
        for (const auto& debugPixel : engineContext.debugDraw->debugPixels)
            renderer->queuePixelDraw(debugPixel.x, debugPixel.y, debugPixel.ch, debugPixel.color);

        engineContext.debugDraw->debugPixels.clear();
    }
#endif
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
    sceneManager->getCurrentScene()->destroy(engineContext);
}
