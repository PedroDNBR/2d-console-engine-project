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
	std::vector<Sprite*> tilemap;
	std::vector<std::vector<int>> tilesStructure;

	void loadTilesSprites(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths);

	std::vector<SpriteToRender>& getTilesSpritesVisibleOnCamera(const Camera& camera);

private:
	std::vector<SpriteToRender> tilesSpritesVisibleOnCamera;

};