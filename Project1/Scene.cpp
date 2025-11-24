#include "Scene.h"
#include "SpriteImporter.h"
#include "ConsoleEngine.h"
#include <iostream>

void Scene::start(ConsoleEngine* engine)
{
	Player* mauro = new Player(54, 30);
	mauro->sprite = importSprite("./Sprites/mauro.tspr"); //apenas para teste
	entities.push_back(mauro); //apenas para teste
	loadTilemap();
	engine->camera.target = mauro;

	for (auto e : entities)
	{
		e->scene = this;
		e->start();
	}
}

void Scene::update(ConsoleEngine* engine, float deltaTime)
{
	for (auto e : entities)
	{
		e->update(deltaTime);
		
	}
	setTilemapsOnPosition(engine);
	for (auto e : entities)
	{
		if (e->sprite != nullptr)
			engine->drawSprite(e->sprite, e->worldX, e->worldY);
	}
	CameraFollowTarget(engine, deltaTime);
}

void Scene::destroy()
{
	for (auto t : tilemap) delete t;

	for (auto e : entities) delete e;

	tilemap.clear();
	entities.clear();
}

void Scene::CameraFollowTarget(ConsoleEngine* engine, float deltaTime)
{
	float leftLimit = engine->camera.x + positiveXcameraOffset;
	float rightLimit = engine->camera.x + (engine->getLogicalWidth() / 2) - negativeXcameraOffset;

	if (engine->camera.target->worldX > leftLimit)
		engine->camera.x = engine->camera.target->worldX - std::floor(engine->getLogicalWidth() / 4.f) - 9;

	if (engine->camera.target->worldX < rightLimit)
		engine->camera.x = engine->camera.target->worldX - std::floor(engine->getLogicalWidth() / 4.f) + 8;

	float topLimit = engine->camera.y + positiveYcameraOffset;
	float bottomLimit = engine->camera.y + engine->getLogicalHeight() - negativeYcameraOffset;

	if (engine->camera.target->worldY < topLimit)
		engine->camera.y -= (topLimit - engine->camera.target->worldY) * deltaTime * 10;

	if (engine->camera.target->worldY > bottomLimit)
		engine->camera.y += (engine->camera.target->worldY - bottomLimit) * deltaTime * 10;
}


bool Scene::isTileSolid(float worldX, float worldY, int width, int height)
{
	return
		isTileSolidAtPoint(worldX, worldY) ||
		isTileSolidAtPoint(worldX + width - 1, worldY) ||
		isTileSolidAtPoint(worldX, worldY + height) ||
		isTileSolidAtPoint(worldX + width - 1, worldY + height);

}

bool Scene::isTileSolidAtPoint(float worldX, float worldY)
{
	int tileX = worldX / tilemap[0]->width;
	int tileY = worldY / tilemap[0]->height;

	if (tileY < 0 || tileY >= tilesStructure.size()) return false;
	if (tileX < 0 || tileX >= tilesStructure[tileY].size()) return false;

	int tileIndex = tilesStructure[tileY][tileX];

	return tilemapPhysics[tileIndex] == 1;
}

void Scene::loadTilemap()
{
	tilemap.push_back(importSprite("./Sprites/sky.tspr"));
	tilemapPhysics.push_back(0);
	tilemap.push_back(importSprite("./Sprites/ground.tspr"));
	tilemapPhysics.push_back(1);
}

void Scene::setTilemapsOnPosition(ConsoleEngine* engine)
{
	for (size_t y = 0; y < tilesStructure.size(); y++)
	{
		for (size_t x = 0; x < tilesStructure[y].size(); x++)
		{
			size_t spriteIndex = tilesStructure[y][x];
			engine->drawSprite(tilemap[spriteIndex], tilemap[spriteIndex]->width * x, tilemap[spriteIndex]->height * y);
		}
	}
}
