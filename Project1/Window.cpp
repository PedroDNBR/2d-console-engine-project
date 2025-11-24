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
}
