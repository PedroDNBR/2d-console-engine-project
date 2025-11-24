#include "ConsoleEngine.h"
#include "Window.h"

ConsoleEngine::ConsoleEngine(int w, int h) : logicalWidth(w), logicalHeight(h),
realWidth(w * 2), realHeight(h)
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    buffer.resize(realWidth * realHeight);
    rect = { 0, 0, (SHORT)(realWidth - 1), (SHORT)(realHeight - 1) };
    lastFrame = std::chrono::steady_clock::now();
    Window::CreateGameWindow(&handle, realWidth, realHeight);
    camera = { 0, 6, logicalWidth, logicalHeight };
}

void ConsoleEngine::clear()
{
    for (auto& c : buffer) {
        c.Char.UnicodeChar = L' ';
        c.Attributes = 0;
    }
}

void ConsoleEngine::drawPixel(int x, int y, wchar_t ch, WORD color)
{
    if (x < 0 || x >= logicalWidth || y < 0 || y >= logicalHeight) return;
    int realX = x * 2;

    CHAR_INFO pixel;
    pixel.Char.UnicodeChar = ch;
    pixel.Attributes = color;

    buffer[y * realWidth + realX] = pixel;
    buffer[y * realWidth + realX + 1] = pixel;
}

void ConsoleEngine::drawSprite(const Sprite* sprite, float worldX, float worldY, bool flip)
{
    if (sprite == nullptr) return;
    if (!isOnCamera(worldX, worldY, sprite->width, sprite->height)) return;
    for (int y = 0; y < sprite->height; ++y) {
        for (int x = 0; x < sprite->width; ++x) {
            Pixel p;
            if (flip)
                p = sprite->getPixel(sprite->width - 1 - x, y); // Acessa o pixel refletido
            else
                p = sprite->getPixel(x, y);

            if (!p.active) continue;
            drawPixel((int)std::ceil(worldX - camera.x) + x, (int)std::floor(worldY - camera.y) + y, p.symbol, p.color);
        }
    }
}

bool ConsoleEngine::isOnCamera(float worldX, float worldY, int w, int h)
{
    if (worldX + w <= camera.x) return false;
    if (worldX >= camera.x + camera.width) return false;

    if (worldY + h <= camera.y) return false;
    if (worldY >= camera.y + camera.height) return false;

    return true;
}

void ConsoleEngine::present()
{
    WriteConsoleOutput(handle, buffer.data(), { (SHORT)realWidth, (SHORT)realHeight }, { 0, 0 }, &rect);
}

void ConsoleEngine::handleInput()
{
    if (GetKeyState('P') & 0x8000) running = false;
}


void ConsoleEngine::run() 
{
    currentScene->start(this);
    while (running) {
        auto now = std::chrono::steady_clock::now();
        deltaTime = std::chrono::duration<float>(now - lastFrame).count();
        lastFrame = now;

        // ignore, just for testing, it will be moved to other method later
       /* if (GetKeyState('W') & 0x8000) camera.y += (-30.0f * deltaTime);
        if (GetKeyState('S') & 0x8000) camera.y += (30.0f * deltaTime);
        if (GetKeyState('A') & 0x8000) camera.x += (-30.0f * deltaTime);
        if (GetKeyState('D') & 0x8000) camera.x += (30.0f * deltaTime);*/

        handleInput();
        clear();
        currentScene->update(this, deltaTime);
        present();
    }
    currentScene->destroy();
    delete currentScene;
    currentScene = nullptr;
}
