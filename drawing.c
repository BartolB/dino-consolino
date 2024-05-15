#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include "header.h"

#define F 219
#define E 32


void clearBuffer(char* buffer, TERMINALSIZE* terminalSize)
{
	memset(buffer, 0, (int)(terminalSize->columns * terminalSize->rows * sizeof(char)));
}


void drawBuffer(char* buffer, TERMINALSIZE* terminalSize)
{
	printf("\x1b[2J");

	for (long int y = terminalSize->rows - 1; y > 0; y--) {
		for (long int x = 0; x < terminalSize->columns; x++) {
			char character = *(buffer + x + y * terminalSize->columns);
			if (character == 0) {
				character = ' ';
			}

			printf("%c", character);
			fflush(stdout);
		}

		printf("\n");
	}
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


void putCharacter(char* buffer, TERMINALSIZE* terminalSize, int x, int y, char character)
{
	*(buffer + x + y * terminalSize->columns) = character;
}


void drawGround(char* buffer, TERMINALSIZE* terminalSize)
{
	const int row = 5;

	for (int x = 0; x < terminalSize->columns; x++) {
		putCharacter(buffer, terminalSize, x, row, 219);
	}
}

void drawDino(char* buffer, TERMINALSIZE* terminalSize, int x, int y) {
	const char dino[] =
		"        ÜÛÛÛÛÛÛÜ"
		"        ÛÜÛÛÛÛÛÛ"
		"        ÛÛÛÛÛÛÛÜ"
		"       ÛÛÛÛÛÛ   "
		"Û    ÛÛÛÛÛÛÛÛÛÛÛ"
		"ÛÛÛÛÛÛÛÛÛÛÛÛÛ  Û"
		" ÛÛÛÛÛÛÛÛÛÛÛ    "
		"    ÛÛ  ÛÛ      "
		"    Û    Û      "
		"    ÛÛ   ÛÛ     ";

	const dino_cols = 16;
	const dino_rows = 10;


	for (int j = 0; j < dino_cols; j++) {
		for (int i = 0; i < dino_rows; i++) {
			putCharacter(buffer, terminalSize, j + x, dino_rows - i + y, dino[j + i * dino_cols]);
		}
	}
}

void drawCactus(char* buffer, TERMINALSIZE* terminalSize, int i) {
	putCharacter(buffer, terminalSize, i, 6, 124);
	putCharacter(buffer, terminalSize, i, 7, 60);
	putCharacter(buffer, terminalSize, i, 8, 124);
	putCharacter(buffer, terminalSize, i, 9, 218);
	putCharacter(buffer, terminalSize, i+1, 9, 94);
	putCharacter(buffer, terminalSize, i+2, 9, 191);
	putCharacter(buffer, terminalSize, i+2, 8, 124);
	putCharacter(buffer, terminalSize, i+2, 6, 124);
	putCharacter(buffer, terminalSize, i+2, 7, 62);
}
