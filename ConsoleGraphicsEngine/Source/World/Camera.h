#pragma once

struct Camera
{
    float x = 0;
    float y = 0;
    int width;
    int height;

    bool isOnCamera(float worldX, float worldY, int w, int h) const
    {
        if (worldX + w <= x) return false;
        if (worldX >= x + width) return false;

        if (worldY + h <= y) return false;
        if (worldY >= y + height) return false;

        return true;
    }
};