#include "SpriteImporter.h"
#include <iostream>
#include <fstream>
#include <sstream>

Sprite* importSprite(const std::string& filename)
{
	std::ifstream inputFile(filename);

	if (!inputFile.is_open())
		return new Sprite(0, 0, 0, 0);

	int width, height;

	std::string line;
	std::getline(inputFile, line);
	width = std::stoi(line);

	std::getline(inputFile, line);
	height = std::stoi(line);

	Sprite* importedSprite = new Sprite(width, height,0,0);

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