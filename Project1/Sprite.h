#pragma once
#include <vector>
#include "Pixel.h"

class Sprite
{
    public:
    int width, height;
    std::vector<Pixel> data;

    Sprite(int w, int h, int posX, int posY) : width(w), height(h), data(w* h) {}

    void setPixel(int x, int y, Pixel p);

    Pixel getPixel(int x, int y) const;
};

