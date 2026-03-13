#include "Scene.h"
#include "SpriteImporter.h"
#include "ConsoleEngine.h"
#include <iostream>

void Scene::start(ConsoleRenderer* renderer)
{
	std::unique_ptr<Player> mauro = std::make_unique<Player>(54, 30);

	spritesUsedInScene.push_back(std::move(importSpriteFromBinary("./Sprites/mauro")));
	spritesUsedInScene.push_back(std::move(importSpriteFromBinary("./Sprites/maurowalk1")));
	spritesUsedInScene.push_back(std::move(importSpriteFromBinary("./Sprites/maurowalk2")));
	spritesUsedInScene.push_back(std::move(importSpriteFromBinary("./Sprites/maurowalk3")));
	mauro->currentFrame = spritesUsedInScene[0].get();  //apenas para teste
	mauro->frames.push_back(spritesUsedInScene[0].get());  //apenas para teste
	mauro->frames.push_back(spritesUsedInScene[1].get());  //apenas para teste
	mauro->frames.push_back(spritesUsedInScene[2].get());  //apenas para teste
	mauro->frames.push_back(spritesUsedInScene[3].get());  //apenas para teste

	entities.push_back(std::move(mauro)); //apenas para teste
	loadTilemap();
	renderer->camera.target = entities[0].get();

	for (const auto& e : entities)
	{
		e->scene = this;
		e->start();
	}
}

void Scene::update(ConsoleRenderer* renderer, float deltaTime)
{
	setTilemapsOnPosition(renderer);
	for (const auto& e : entities)
	{
		e->update(deltaTime);
		if (e->currentFrame != nullptr)
			renderer->queueDraw(e->currentFrame, e->worldX, e->worldY, e->flipSprite);
	}
	CameraFollowTarget(renderer, deltaTime);
}

void Scene::destroy()
{
	spritesUsedInScene.clear();
	tilemap.clear();
	entities.clear();
}

void Scene::CameraFollowTarget(ConsoleRenderer* renderer, float deltaTime)
{
	float leftLimit = renderer->camera.x + positiveXcameraOffset;
	float rightLimit = renderer->camera.x + (renderer->getLogicalWidth() / 2) - negativeXcameraOffset;

	if (renderer->camera.target->worldX > leftLimit && renderer->camera.x < ((tilesStructure[0].size() - 1) * tilemap[0]->width) - std::floor(renderer->getLogicalWidth() / 4.f) - negativeXcameraOffset)
		renderer->camera.x = renderer->camera.target->worldX - std::floor(renderer->getLogicalWidth() / 4.f) - 9;

	if (renderer->camera.target->worldX < rightLimit && renderer->camera.x - 1 > 0)
		renderer->camera.x = renderer->camera.target->worldX - std::floor(renderer->getLogicalWidth() / 4.f) + 8;

	float topLimit = renderer->camera.y + positiveYcameraOffset;
	float bottomLimit = renderer->camera.y + renderer->getLogicalHeight() - negativeYcameraOffset;

	if (renderer->camera.target->worldY < topLimit)
		renderer->camera.y -= (topLimit - renderer->camera.target->worldY) * deltaTime * 10;

	if (renderer->camera.target->worldY > bottomLimit)
		renderer->camera.y += (renderer->camera.target->worldY - bottomLimit) * deltaTime * 10;
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
	tilemap.push_back(importSpriteFromBinary("./Sprites/sky"));
	tilemapPhysics.push_back(0);
	tilemap.push_back(importSpriteFromBinary("./Sprites/ground"));
	tilemapPhysics.push_back(1);
}

void Scene::setTilemapsOnPosition(ConsoleRenderer* renderer)
{
	for (size_t y = 0; y < tilesStructure.size(); y++)
	{
		for (size_t x = 0; x < tilesStructure[y].size(); x++)
		{
			size_t spriteIndex = tilesStructure[y][x];
			renderer->queueDraw(tilemap[spriteIndex].get(), tilemap[spriteIndex]->width * x, tilemap[spriteIndex]->height * y);
		}
	}
}
