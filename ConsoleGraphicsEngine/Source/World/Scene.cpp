#include "Scene.h"
#include <iostream>

void Scene::start(ViewportInfo& info, EngineContext& engineContext)
{
	entityManager = std::make_unique<EntityManager>();
	tilemapManager = std::make_unique<TilemapManager>();
	collisionManager = std::make_unique<CollisionManager>(*tilemapManager);
	worldContext = std::make_unique<WorldContext>(*tilemapManager, * entityManager, *collisionManager);
	camera = Camera{ 0, 0, info.width, info.height };
	onStart(info, engineContext, *worldContext);
	entityManager->start(engineContext, *worldContext);
}

void Scene::update(EngineContext& engineContext)
{
	onUpdate(engineContext, *worldContext);
	entityManager->update(engineContext, *worldContext);
}

void Scene::fixedUpdate(EngineContext& engineContext)
{
	onFixedUpdate(engineContext, *worldContext);
	entityManager->fixedUpdate(engineContext, *worldContext);
}

void Scene::destroy(EngineContext& engineContext)
{
	onDestroy(engineContext, *worldContext);
}

void Scene::onStart(ViewportInfo& viewportInfo, EngineContext& engineContext, WorldContext& worldContext) {}
void Scene::onUpdate(EngineContext& engineContext, WorldContext& worldContext) {}
void Scene::onDestroy(EngineContext& engineContext, WorldContext& worldContext) {}

void Scene::handleResize(ViewportInfo& info)
{
	camera.width = info.width;
	camera.height = info.height;
	onHandleResize(info);
}

std::vector<SpriteToRender> Scene::getSpritesToRender()
{
	spritesToRender.clear();

	const auto& tilemapSprites = tilemapManager->getTilesSpritesVisibleOnCamera(camera);
	const auto& entitiesSprites = entityManager->getEntitiesSpritesVisibleOnCamera(camera);

	spritesToRender.insert(spritesToRender.end(), tilemapSprites.begin(), tilemapSprites.end());
	spritesToRender.insert(spritesToRender.end(), entitiesSprites.begin(), entitiesSprites.end());

	return spritesToRender;
}
