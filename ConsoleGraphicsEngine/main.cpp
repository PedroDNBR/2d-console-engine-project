#include <iostream>
#include "Source/Core/ConsoleEngine.h"

int main() {
    ConsoleEngine engine;

    engine.start();
    engine.update();
    engine.cleanup();

    std::cout << "Game Finished\n";
}

/* FUNCIONAL, O MEHOR ATÉ AGORA
#include <iostream>
#include <windows.h>
#include <vector>
#include <locale>
#include "Window.h"

int main() {
    std::setlocale(LC_ALL, ".UTF-8");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    const int resolutionX = 106;
    const int resolutionY = 60;

    const int bufferX = resolutionX * 2;

    bool running = true;
    DWORD lastFrame = GetTickCount();
    const DWORD FRAME_DELAY = 33;

    size_t offset = 0;

    // cria buffer de CHAR_INFO
    std::vector<CHAR_INFO> screen(bufferX * resolutionY);

    SMALL_RECT rect = { 0, 0, (SHORT)(bufferX - 1), (SHORT)(resolutionY - 1) };
    COORD bufferSize = { (SHORT)bufferX, (SHORT)resolutionY };
    COORD bufferCoord = { 0, 0 };

    Window::CreateGameWindow(&handle, bufferX, resolutionY);

    // loop principal
    while (running) {
        if (GetKeyState('A') & 0x8000)
            running = false;

        DWORD now = GetTickCount();
        if (now - lastFrame >= FRAME_DELAY) {
            lastFrame = now;

            // Preenche o buffer com blocos coloridos
            for (int y = 0; y < resolutionY; ++y) {
                for (int x = 0; x < resolutionX; ++x) {
                    // cor baseada na posição + offset (animação)
                    WORD color = (x + y + offset) % 16;

                    // posição do pixel lógico no buffer real (duplicado)
                    int realX = x * 2;

                    // escreve dois blocos '█' lado a lado
                    CHAR_INFO& cell1 = screen[y * bufferX + realX];
                    cell1.Char.UnicodeChar = L'█';
                    cell1.Attributes = color;

                    CHAR_INFO& cell2 = screen[y * bufferX + (realX + 1)];
                    cell2.Char.UnicodeChar = L'█';
                    cell2.Attributes = color;
                }
            }

            // Desenha tudo de uma vez
            WriteConsoleOutput(handle, screen.data(), bufferSize, bufferCoord, &rect);

            // avança o offset da animação
            offset = (offset + 1) % 16;
        }

        Sleep(1);
    }

    // Restaura cor padrão e mensagem final
    SetConsoleTextAttribute(handle, 15);
    std::cout << "\nGame Finished\n";
}

*/

/*
#include <iostream>
#include <windows.h>
#include <locale>

int main()
{
    std::setlocale(LC_ALL, ".UTF-8");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << std::endl;
    std::cout << std::endl;

    uint8_t resolutionX = 106;
    uint8_t resolutionY = 60;

    bool running = true;

    DWORD lastFrame = GetTickCount();
    const DWORD FRAME_DELAY = 100;

    size_t offset = 0;
    while (running)
    {
        if (GetKeyState('A') & 0x8000)
            running = false;

        DWORD now = GetTickCount();
        if (now - lastFrame >= FRAME_DELAY)
        {
            lastFrame = now;

            COORD coord = { 0, 0 };
            SetConsoleCursorPosition(handle, coord);
            std::cout << std::endl;
            std::cout << std::endl;

            for (int y = 0; y < resolutionY; ++y) {
                for (int x = 0; x < resolutionX; ++x) {
                    SetConsoleTextAttribute(handle, (x + y + offset) % 16);
                    std::cout << u8"██";
                    //std::cout << u8"##";
                }
                SetConsoleTextAttribute(handle, 0);
                std::cout << std::endl;
            }
            offset = (offset + 1) % 16;
        }
        Sleep(1);

        SetConsoleTextAttribute(handle, 0);
        std::cout << "";
    }

    SetConsoleTextAttribute(handle, 0);
    std::cout << "";
    SetConsoleTextAttribute(handle, 15);
    std::cout << "Game Finished";
}
*/

/*
#include <iostream>
#include <windows.h>
#include <locale>
#include <vector>

int main()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << std::endl << std::endl;

    uint8_t resolutionX = 106;
    uint8_t resolutionY = 60;

    bool running = true;

    DWORD lastFrame = GetTickCount();
    const DWORD FRAME_DELAY = 100;

    size_t offset = 0;

    // Habilitar o cursor invisível para evitar flickering
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(handle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &cursorInfo);

    // Buffer para armazenar todo o conteúdo do frame
    std::vector<std::vector<int>> colorBuffer(resolutionY, std::vector<int>(resolutionX));

    // Loop principal
    while (running)
    {
        if (GetKeyState('A') & 0x8000)
            running = false;

        DWORD now = GetTickCount();
        if (now - lastFrame >= FRAME_DELAY)
        {
            lastFrame = now;

            // Limpa o buffer de cor para o frame atual
            for (int y = 0; y < resolutionY; ++y)
            {
                for (int x = 0; x < resolutionX; ++x)
                {
                    // Defina a cor com base na posição (x, y)
                    colorBuffer[y][x] = (x + y + offset) % 16;
                }
            }

            // Volta o cursor para o topo da tela
            SetConsoleCursorPosition(handle, { 0, 0 });

            // Imprime o quadro com as cores
            for (int y = 0; y < resolutionY; ++y)
            {
                for (int x = 0; x < resolutionX; ++x)
                {
                    SetConsoleTextAttribute(handle, colorBuffer[y][x]); // Aplica a cor para cada caractere
                    std::cout << u8"##";  // ou u8"██", dependendo do tamanho do caractere
                }
                std::cout << "\n";
            }

            offset = (offset + 1) % 16; // Desloca a cor por frame
        }

        Sleep(1); // Evita uso 100% da CPU
    }

    // Restaura as configurações após terminar
    SetConsoleTextAttribute(handle, 15);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(handle, &cursorInfo);
    std::cout << "\nGame Finished\n";
}
*/