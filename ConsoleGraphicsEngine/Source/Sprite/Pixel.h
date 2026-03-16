#pragma once
#include <Windows.h>

struct Pixel {
    wchar_t symbol = L'█';
    WORD color = 15; // branco padrão
    bool active = true;
};