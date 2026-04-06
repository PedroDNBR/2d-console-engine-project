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
	return getTilesSpritesVisibleOnCameraFromVector(topTilesStructure, topTilemap, camera);

}

std::vector<SpriteToRender>& TilemapManager::getBackgroundTilesSpritesVisibleOnCamera(const Camera& camera)
{
	return getTilesSpritesVisibleOnCameraFromVector(backgroundTilesStructure, backgroundTilemap, camera);
}

std::vector<SpriteToRender>& TilemapManager::getTilesSpritesVisibleOnCameraFromVector(const std::vector<std::vector<int>>& tileStructure, const std::vector<Sprite*>& tilemap, const Camera& camera)
{
	tilesSpritesVisibleOnCamera.clear();

	int tileStartX = std::floor(camera.x / tileSize);
	int tileStartY = std::floor(camera.y / tileSize);

	int tileEndX = std::ceil((camera.x + camera.width) / tileSize);
	int tileEndY = std::ceil((camera.y + camera.height) / tileSize);

	tileStartX = max(0, tileStartX);
	tileStartY = max(0, tileStartY);
	tileEndX = min(tileStructure[0].size() - 1, tileEndX);
	tileEndY = min(tileStructure.size() - 1, tileEndY);

	for (int y = tileStartY; y <= tileEndY; y++)
	{
		for (int x = tileStartX; x <= tileEndX; x++)
		{
			bool flip = false;
			int tileIndex = tileStructure[y][x];
			if (tileIndex == 0) continue;
			if (tileIndex < 0)
			{
				tileIndex *= -1;
				flip = true;
			}
			tileIndex -= 1;
			if (camera.isOnCamera(x * tilemap[tileIndex]->width, y * tilemap[tileIndex]->height, tilemap[tileIndex]->width, tilemap[tileIndex]->height))
			{
				SpriteToRender spriteToRenderTop;
				spriteToRenderTop.sprite = tilemap[tileIndex];
				spriteToRenderTop.worldX = x * spriteToRenderTop.sprite->width;
				spriteToRenderTop.worldY = y * spriteToRenderTop.sprite->height;
				spriteToRenderTop.flip = flip;
				tilesSpritesVisibleOnCamera.push_back(spriteToRenderTop);
			}
		}
	}

	return tilesSpritesVisibleOnCamera;
}

