#include "Scene.h"
#include "../Sprite/SpriteImporter.h"
#include "../Core/ConsoleEngine.h"
#include <iostream>

void Scene::start(ConsoleRenderer* renderer)
{
	std::unique_ptr<Player> mauro = std::make_unique<Player>(54, 30);

	spritesUsedInScene.push_back(std::move(importSpriteFromBinary("./Assets/Sprites/mauro")));
	spritesUsedInScene.push_back(std::move(importSpriteFromBinary("./Assets/Sprites/maurowalk1")));
	spritesUsedInScene.push_back(std::move(importSpriteFromBinary("./Assets/Sprites/maurowalk2")));
	spritesUsedInScene.push_back(std::move(importSpriteFromBinary("./Assets/Sprites/maurowalk3")));
	spritesUsedInScene.push_back(std::move(importSpriteFromBinary("./Assets/Sprites/maurojump")));
	mauro->currentFrame = spritesUsedInScene[0].get();  //apenas para teste
	mauro->frames.push_back(spritesUsedInScene[0].get());  //apenas para teste
	mauro->frames.push_back(spritesUsedInScene[1].get());  //apenas para teste
	mauro->frames.push_back(spritesUsedInScene[2].get());  //apenas para teste
	mauro->frames.push_back(spritesUsedInScene[3].get());  //apenas para teste
	mauro->frames.push_back(spritesUsedInScene[4].get());  //apenas para teste

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
	float playerScreenX = (renderer->camera.target->worldX + (renderer->camera.target->currentFrame->width / 2)) - renderer->camera.x;
	float playerScreenY = (renderer->camera.target->worldY + (renderer->camera.target->currentFrame->height / 2)) - renderer->camera.y;

	float leftMagin = renderer->getLogicalWidth() * .4f;
	float rightMagin = renderer->getLogicalWidth() * .6f;

	if(playerScreenX < leftMagin)
	{
		renderer->camera.x += (playerScreenX - leftMagin) * deltaTime * 10;
	}
	else if(playerScreenX > rightMagin)
	{
		renderer->camera.x += (playerScreenX - rightMagin) * deltaTime * 10;
	}

	float topMagin = renderer->getLogicalHeight() * .3f;
	float bottomMagin = renderer->getLogicalHeight() * .7f;

	if (playerScreenY < topMagin)
		renderer->camera.y += (playerScreenY - topMagin) * deltaTime * 10;

	if (playerScreenY > bottomMagin)
		renderer->camera.y += (playerScreenY - bottomMagin) * deltaTime * 10;
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
	tilemap.push_back(importSpriteFromBinary("./Assets/Sprites/sky"));
	tilemapPhysics.push_back(0);
	tilemap.push_back(importSpriteFromBinary("./Assets/Sprites/ground"));
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
