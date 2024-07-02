#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include "header.h"


void clearBuffer(wchar_t* buffer, TERMINALSIZE* terminalSize)
{
	wmemset(buffer, L' ', (int)(terminalSize->columns * terminalSize->rows));
}


void drawBuffer(wchar_t* buffer, TERMINALSIZE* terminalSize)
{
	HANDLE console;
	console = CreateFileW(L"CONOUT$", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		0, NULL);
	if (console == INVALID_HANDLE_VALUE)
		return;

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(console, &cursorInfo);

	for (long int y = terminalSize->rows - 1; y > 0; y--) {
		for (long int x = 0; x < terminalSize->columns; x++) {
			wchar_t character = *(buffer + x + y * terminalSize->columns);

			COORD position = { x, terminalSize->rows - y };

			SetConsoleCursorPosition(console, position);
			if (wprintf(L"%wc", character) < 0) {
				perror("wprintf");
			}
		}
	}

	CloseHandle(console);
}

TERMINALSIZE getTerminalSize()
{
	TERMINALSIZE result = { 0, 0 };

	HANDLE console;
	CONSOLE_SCREEN_BUFFER_INFO info;
	console = CreateFileW(L"CONOUT$", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		0, NULL);
	if (console == INVALID_HANDLE_VALUE)
		return result;

	/* Calculate the size of the console window. */
	if (GetConsoleScreenBufferInfo(console, &info) == 0)
		return result;

	CloseHandle(console);
	result.columns = info.srWindow.Right - info.srWindow.Left + 1;
	result.rows = info.srWindow.Bottom - info.srWindow.Top + 1;

	return result;
}


void putCharacter(wchar_t* buffer, TERMINALSIZE* terminalSize, int x, int y, wchar_t character)
{
	*(buffer + x + y * terminalSize->columns) = character;
}

wchar_t getCharacter(wchar_t* buffer, TERMINALSIZE* terminalSize, int x, int y)
{
	return *(buffer + x + y * terminalSize->columns);
}


void drawGround(wchar_t* buffer, TERMINALSIZE* terminalSize)
{
	const int row = 5;

	for (int x = 0; x < terminalSize->columns; x++) {
		putCharacter(buffer, terminalSize, x, row, L'█');
	}
}

int drawDinoAndCheck(wchar_t* buffer, TERMINALSIZE* terminalSize, int x, int y) {
	const wchar_t dino[] =
		L"        ▄██████▄"
		L"        █▄██████"
		L"        ███████▄"
		L"       ██████   "
		L"█    ███████████"
		L"█████████████  █"
		L" ███████████    "
		L"    ██  ██      "
		L"    █    █      "
		L"    ██   ██     ";

	const dino_cols = 16;
	const dino_rows = 10;

	for (int j = 0; j < dino_cols; j++) {
		for (int i = 0; i < dino_rows; i++) {
			wchar_t character = dino[j + i * dino_cols];

			if (character == ' ') {
				continue;
			}

			wchar_t existing = getCharacter(buffer, terminalSize, j + x, dino_rows - i + y);

			if (existing != 0 && existing != L' ') {
				return 0;
			}

			putCharacter(buffer, terminalSize, j + x, dino_rows - i + y, character);
		}
	}

	return 1;
}

void drawCactus(wchar_t* buffer, TERMINALSIZE* terminalSize, int i) {
	putCharacter(buffer, terminalSize, i, 6, L'|');
	putCharacter(buffer, terminalSize, i, 7, L'<');
	putCharacter(buffer, terminalSize, i, 8, L'┌');
	putCharacter(buffer, terminalSize, i+1, 8, L'^');
	putCharacter(buffer, terminalSize, i+2, 8, L'┐');
	putCharacter(buffer, terminalSize, i+2, 6, L'|');
	putCharacter(buffer, terminalSize, i+2, 7, L'>');
}
