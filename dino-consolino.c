#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <wchar.h>

typedef struct TerminalSize {
	int columns;
	int rows;
} TERMINALSIZE;

TERMINALSIZE getTerminalSize();
void drawBuffer(char*, TERMINALSIZE*);
void clearBuffer(char*, TERMINALSIZE*);
void putCharacter(char*, TERMINALSIZE*, char);

void drawGround(char*, TERMINALSIZE*);

int main()
{
	TERMINALSIZE terminalSize = getTerminalSize();

	//printf("terminal size %d %d", terminalSize.columns, terminalSize.rows);

	char* mainBuffer = (char *)malloc(terminalSize.columns * terminalSize.rows * sizeof(char));

	clearBuffer(mainBuffer, &terminalSize);

	drawGround(mainBuffer, &terminalSize);

	do {
		drawBuffer(mainBuffer, &terminalSize);
		Sleep(500);
	} while (1);

	free(mainBuffer);

	return 0;
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
