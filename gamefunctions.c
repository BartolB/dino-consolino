#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include <conio.h>
#include "header.h"

int MainGame() {

	TERMINALSIZE terminalSize = getTerminalSize();

	wchar_t* mainBuffer = (wchar_t*)malloc(terminalSize.columns * terminalSize.rows * sizeof(wchar_t));

	clearBuffer(mainBuffer, &terminalSize);

	int dino_jump_height = 0;
	int dino_jump = 0;
	int cactus_pos = 50;
	int score = 0;

	do {
		if (dino_jump == 0) {
			if (_kbhit() && _getch() == ' ') {
				dino_jump = 1;
			}
		}

		clearBuffer(mainBuffer, &terminalSize);
		drawGround(mainBuffer, &terminalSize);

		score++;

		if (cactus_pos <= 0) {
			cactus_pos = 110;
		}
		else {
			cactus_pos -= 2;
		}
		drawCactus(mainBuffer, &terminalSize, cactus_pos);

		dino_jump_height += dino_jump;
		if (dino_jump_height >= 7) {
			dino_jump = -1;
		}
		else if (dino_jump_height <= 0 && dino_jump != 0) {
			dino_jump = 0;
		}

		int success = drawDinoAndCheck(mainBuffer, &terminalSize, 1, 5 + dino_jump_height);
		if (!success) {
			wprintf(L"\x1b[2J");
			wprintf(L"\nGame over!!1111\n");
			wprintf(L"\nVas score je %d\n", score);
			return score;
		}

		drawBuffer(mainBuffer, &terminalSize);
	} while (1);

	free(mainBuffer);

	return 0;
}