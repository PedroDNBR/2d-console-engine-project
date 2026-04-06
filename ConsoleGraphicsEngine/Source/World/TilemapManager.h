#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Sprite/Sprite.h"
#include "../Sprite/SpriteToRender.h"

struct EngineContext;
class Camera;

class TilemapManager
{
public:
	std::vector<Sprite*> backgroundTilemap;
	std::vector<Sprite*> topTilemap;
	std::vector<std::vector<int>> backgroundTilesStructure;
	std::vector<std::vector<int>> topTilesStructure;

	void loadTopTilesSprites(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths);
	void loadBackgroundTilesSprites(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths);

	std::vector<SpriteToRender>& getTopTilesSpritesVisibleOnCamera(const Camera& camera);
	std::vector<SpriteToRender>& getBackgroundTilesSpritesVisibleOnCamera(const Camera& camera);

	int tileSize = 16;

private:
	std::vector<SpriteToRender> tilesSpritesVisibleOnCamera;
	std::vector<SpriteToRender>& getTilesSpritesVisibleOnCameraFromVector(const std::vector<std::vector<int>>& tileStructure, const std::vector<Sprite*>& tilemap, const Camera& camera);
};