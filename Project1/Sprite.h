#pragma once
#include <vector>
#include "Pixel.h"

class Sprite
{
    public:
    uint8_t width, height;
    std::vector<Pixel> data;

    Sprite(uint8_t w, uint8_t h) : width(w), height(h), data(w* h) {}

    void setPixel(int x, int y, Pixel p);

    Pixel getPixel(int x, int y) const;
};

