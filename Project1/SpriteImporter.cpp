#include "SpriteImporter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

std::unique_ptr<Sprite> importSprite(const std::string& filename)
{
	std::ifstream inputFile(filename);

	if (!inputFile.is_open())
	{
		std::cout << "Failed to open file: " << filename << std::endl;
		return std::make_unique<Sprite>(0, 0);
	}

	int width, height;

	std::string line;
	std::getline(inputFile, line);
	width = std::stoi(line);

	std::getline(inputFile, line);
	height = std::stoi(line);

	std::unique_ptr<Sprite> importedSprite = std::make_unique<Sprite>(width, height);

	int index = 0;
	while (std::getline(inputFile, line, ';'))
	{
		Pixel pixel;
		pixel.symbol = L'█';

		if (line == "#")
		{
			pixel.active = false;
			pixel.color = 0;
		}
		else
		{
			pixel.active = true;
			pixel.color = std::stoi(line);
		}

		importedSprite->setPixel(index % width, index / width, pixel);

		index++;
	}

	return importedSprite;
}

namespace
{
	constexpr char SPRITE_MAGIC[4] = {'T', 'S', 'P', 'R'};
	constexpr uint32_t SPRITE_VERSION = 1;
	template<typename T>
	bool readBinary(std::ifstream& inputFile, T& value)
	{
		inputFile.read(reinterpret_cast<char*>(&value), sizeof(T));
		return inputFile.good();
	}
}

std::unique_ptr<Sprite> importSpriteFromBinary(const std::string& filename)
{
	std::ifstream inputFile(filename, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open binary file: " << filename << std::endl;
		return std::make_unique<Sprite>(0, 0);
	}

	std::array<char, 4> magic{};
	inputFile.read(magic.data(), magic.size());

	if (!inputFile.good() || !std::equal(magic.begin(), magic.end(), std::begin(SPRITE_MAGIC)))
	{
		std::cout << "Invalid sprite binary file: " << filename << std::endl;
		return std::make_unique<Sprite>(0, 0);
	}

	uint32_t version = 0;
	uint8_t width = 0;
	uint8_t height = 0;

	if (!readBinary(inputFile, version) || !readBinary(inputFile, width) || !readBinary(inputFile, height))
	{
		std::cout << "Failed to read sprite header: " << filename << std::endl;
		return std::make_unique<Sprite>(0, 0);
	}

	if (version != SPRITE_VERSION)
	{
		std::cout << "Unsupported sprite version: "
			<< static_cast<int>(version)
			<< " in file: "
			<< filename
			<< std::endl
			<< " Curent version is"
			<< static_cast<int>(SPRITE_VERSION)
			<< std::endl;

		return std::make_unique<Sprite>(0, 0);
	}

	std::unique_ptr<Sprite> importedSprite = std::make_unique<Sprite>(width, height);
	const uint32_t pixelCount = static_cast<uint32_t>(width) * static_cast<uint32_t>(height);

	for (uint32_t i = 0; i < pixelCount; i++)
	{
		uint8_t activeByte = 0;
		uint8_t colorByte = 0;

		if (!readBinary(inputFile, activeByte) || !readBinary(inputFile, colorByte))
		{
			std::cout << "Failed to read pixel data at index " << i << " in file: " << filename << std::endl;
			return std::make_unique<Sprite>(0, 0);
		}

		Pixel pixel;
		pixel.symbol = L'█';
		pixel.active = (activeByte != 0);
		pixel.color = static_cast<WORD>(colorByte);

		int x = static_cast<int>(i % width);
		int y = static_cast<int>(i / width);

		importedSprite->setPixel(x, y, pixel);
	}


	return importedSprite;
}