#include "TilemapManager.h"
#include "../Core/Context/EngineContext.h"
#include "../Core/AssetManager.h"
#include "Camera.h"

void TilemapManager::loadTopTilesSprites(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths)
{
	for (auto spritePath : spritesPaths)
	{
		topTilemap.push_back(&engineContext.assetManager->loadSprite(spritePath));
	}
}

void TilemapManager::loadBackgroundTilesSprites(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths)
{
	for (auto spritePath : spritesPaths)
	{
		backgroundTilemap.push_back(&engineContext.assetManager->loadSprite(spritePath));
	}
}

std::vector<SpriteToRender>& TilemapManager::getTopTilesSpritesVisibleOnCamera(const Camera& camera)
{
	tilesSpritesVisibleOnCamera.clear();

	int tileStartX = std::floor(camera.x / 16);
	int tileStartY = std::floor(camera.y / 16);

	int tileEndX = std::ceil((camera.x + camera.width) / 16);
	int tileEndY = std::ceil((camera.y + camera.height) / 16);

	tileStartX = max(0, tileStartX);
	tileStartY = max(0, tileStartY);
	tileEndX = min(backgroundTilesStructure[0].size() - 1, tileEndX);
	tileEndY = min(backgroundTilesStructure.size() - 1, tileEndY);

	for (int y = tileStartY; y < tileEndY; y++)
	{
		for (int x = tileStartX; x < tileEndX; x++)
		{
			int tileIndex = topTilesStructure[y][x];
			if (tileIndex < 1) continue;
			tileIndex -= 1;
			if (camera.isOnCamera(x * topTilemap[tileIndex]->width, y * topTilemap[tileIndex]->height, topTilemap[tileIndex]->width, topTilemap[tileIndex]->height))
			{
				SpriteToRender spriteToRenderTop;
				spriteToRenderTop.sprite = topTilemap[tileIndex];
				spriteToRenderTop.worldX = x * spriteToRenderTop.sprite->width;
				spriteToRenderTop.worldY = y * spriteToRenderTop.sprite->height;
				tilesSpritesVisibleOnCamera.push_back(spriteToRenderTop);
			}
		}
	}

	return tilesSpritesVisibleOnCamera;
}

std::vector<SpriteToRender>& TilemapManager::getBackgroundTilesSpritesVisibleOnCamera(const Camera& camera)
{
	tilesSpritesVisibleOnCamera.clear();

	int tileStartX = std::floor(camera.x / 16);
	int tileStartY = std::floor(camera.y / 16);

	int tileEndX = std::ceil((camera.x + camera.width) / 16);
	int tileEndY = std::ceil((camera.y + camera.height) / 16);

	tileStartX = max(0, tileStartX);
	tileStartY = max(0, tileStartY);
	tileEndX = min(backgroundTilesStructure[0].size() - 1, tileEndX);
	tileEndY = min(backgroundTilesStructure.size() - 1, tileEndY);

	for (int y = tileStartY; y < tileEndY; y++)
	{
		for (int x = tileStartX; x < tileEndX; x++)
		{
			int tileIndex = backgroundTilesStructure[y][x];
			if (tileIndex < 1) continue;
			tileIndex -= 1;
			if (camera.isOnCamera(x * backgroundTilemap[tileIndex]->width, y * backgroundTilemap[tileIndex]->height, backgroundTilemap[tileIndex]->width, backgroundTilemap[tileIndex]->height))
			{
				SpriteToRender spriteToRender;
				spriteToRender.sprite = backgroundTilemap[tileIndex];
				spriteToRender.worldX = x * spriteToRender.sprite->width;
				spriteToRender.worldY = y * spriteToRender.sprite->height;
				tilesSpritesVisibleOnCamera.push_back(spriteToRender);
			}
		}
	}

	return tilesSpritesVisibleOnCamera;
}

