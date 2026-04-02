#include "AssetManager.h"

Sprite& AssetManager::loadSprite(const std::string& path)
{
	auto spriteIterator = spriteCache.find(path);

	if(spriteIterator != spriteCache.end())
		return *spriteIterator->second;

	auto newSprite = spriteCache.emplace(path, importSpriteFromBinary(path));

	return *newSprite.first->second;
}

Sprite& AssetManager::getSprite(const std::string& path)
{
	return *spriteCache.at(path);
}
