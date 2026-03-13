#include "window.h"

void Window::CreateGameWindow(HANDLE* handle, int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFOEX info = { sizeof(info) };
	GetConsoleScreenBufferInfoEx(*handle, &info);

	info.dwSize.X = x;
	info.dwSize.Y = y;
	info.srWindow = { 0, 0, (SHORT)(x - 1), (SHORT)(y - 1) };
	SetConsoleScreenBufferInfoEx(*handle, &info);

	// aplica o mesmo retângulo à janela
	SMALL_RECT windowRect = { 0, 0, (SHORT)(x - 1), (SHORT)(y - 1) };
	SetConsoleWindowInfo(*handle, TRUE, &windowRect);

	CONSOLE_FONT_INFOEX cfi = {};
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 16;   // largura do caractere
	cfi.dwFontSize.Y = 32;  // altura do caractere
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");

	SetCurrentConsoleFontEx(handle, FALSE, &cfi);
}
