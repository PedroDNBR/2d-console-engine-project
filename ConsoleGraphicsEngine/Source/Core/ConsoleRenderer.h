#pragma once
#include "Window.h"
#include <vector>
#include <chrono>
#include "../Sprite/Sprite.h"
#include "../Sprite/SpriteToRender.h"
#ifdef _DEBUG
#include "../Core/DebugDraw.h"
#endif

class ConsoleRenderer
{
private:
    HANDLE handle;
    int logicalWidth, logicalHeight;
    int realWidth, realHeight;
    std::vector<CHAR_INFO> buffer;
    SMALL_RECT rect;

    std::vector<SpriteToRender> spritesToRender;
#ifdef _DEBUG
    std::vector<DebugPixel> pixelsToRender;
#endif

    void resizeWindow(int newWidth, int newHeight);

public:
    ConsoleRenderer(int w, int h);
    void drawPixel(int x, int y, wchar_t ch, WORD color);
    void drawSprite(int viewX, int viewY, const Sprite* sprite, float worldX, float worldY, bool flip = false);
    void present(int viewX, int viewY);
    void clear();
    void queueSpriteDraw(const Sprite* sprite, float worldX, float worldY, bool flip = false);
#ifdef _DEBUG
    void queuePixelDraw(int x, int y, wchar_t ch, int color);
#endif
    bool hasWindowResized();

    int getLogicalWidth() { return logicalWidth; }
    int getLogicalHeight() { return logicalHeight; }

    int getRealWidth() { return realWidth; }
    int getRealHeight() { return realHeight; }
};

