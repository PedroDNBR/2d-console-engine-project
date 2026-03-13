#pragma once
#include "Sprite.h"
#include <string>
#include <memory>

std::unique_ptr<Sprite> importSprite(const std::string& filename);

std::unique_ptr<Sprite> importSpriteFromBinary(const std::string& filename);