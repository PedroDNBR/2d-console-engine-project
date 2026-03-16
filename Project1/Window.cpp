#include "window.h"

void Window::CreateGameWindow(HANDLE* handle, int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFOEX info = { sizeof(info) };
	GetConsoleScreenBufferInfoEx(*handle, &info);

	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(*handle, &consoleScreenBufferInfo);

	info.dwSize.X = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;
	info.dwSize.Y = consoleScreenBufferInfo.srWindow.Bottom - consoleScreenBufferInfo.srWindow.Top + 1;
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

void Window::GetWindowSize(HANDLE* handle, int& width, int& height)
{
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(*handle, &consoleScreenBufferInfo);

	width = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;
	height = consoleScreenBufferInfo.srWindow.Bottom - consoleScreenBufferInfo.srWindow.Top + 1;
}
