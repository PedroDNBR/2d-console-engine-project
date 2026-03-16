#include "Sprite.h"

void Sprite::setPixel(int x, int y, Pixel p)
{
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    data[y * width + x] = p;
}

Pixel Sprite::getPixel(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height) return Pixel();
    return data[y * width + x];
}
