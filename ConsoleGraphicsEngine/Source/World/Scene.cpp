#include "Scene.h"
#include <iostream>

void Scene::start(ViewportInfo& info, EngineContext& engineContext)
{
	entityManager = std::make_unique<EntityManager>();
	tilemapManager = std::make_unique<TilemapManager>();
	collisionManager = std::make_unique<CollisionManager>(*tilemapManager, *entityManager);
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

std::vector<SpriteToRender> Scene::getEntitiesToRender()
{
	return entityManager->getEntitiesSpritesVisibleOnCamera(camera);
}

std::vector<SpriteToRender> Scene::getTopTilesToRender()
{
	return tilemapManager->getTopTilesSpritesVisibleOnCamera(camera);
}

std::vector<SpriteToRender> Scene::getBackgroundTilesToRender()
{
	return tilemapManager->getBackgroundTilesSpritesVisibleOnCamera(camera);
}
