#pragma once
#include "../Sprite/Sprite.h"
#include <string>
#include <unordered_map>
#include "../Sprite/SpriteImporter.h"

class AssetManager
{
public:
	Sprite& loadSprite(const std::string& path);
	Sprite& getSprite(const std::string& path);

private:
	std::unordered_map<std::string, std::unique_ptr<Sprite>> spriteCache;

};

