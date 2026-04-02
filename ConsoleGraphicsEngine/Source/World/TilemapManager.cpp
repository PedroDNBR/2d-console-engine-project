#include "TilemapManager.h"
#include "../Core/Context/EngineContext.h"
#include "../Core/AssetManager.h"
#include "Camera.h"

void TilemapManager::loadTilesSprites(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths)
{
	for (auto spritePath : spritesPaths)
	{
		tilemap.push_back(&engineContext.assetManager->loadSprite(spritePath));
	}
}

std::vector<SpriteToRender>& TilemapManager::getTilesSpritesVisibleOnCamera(const Camera& camera)
{
	tilesSpritesVisibleOnCamera.clear();
	for (size_t y = 0; y < tilesStructure.size(); y++)
	{
		for (size_t x = 0; x < tilesStructure[y].size(); x++)
		{
			int tileIndex = tilesStructure[y][x];
			if (camera.isOnCamera(x * tilemap[tileIndex]->width, y * tilemap[tileIndex]->height, tilemap[tileIndex]->width, tilemap[tileIndex]->height))
			{
				SpriteToRender spriteToRender;
				spriteToRender.sprite = tilemap[tileIndex];
				spriteToRender.worldX = x * spriteToRender.sprite->width;
				spriteToRender.worldY = y * spriteToRender.sprite->height;
				tilesSpritesVisibleOnCamera.push_back(spriteToRender);
			}
		}
	}

	return tilesSpritesVisibleOnCamera;
}
