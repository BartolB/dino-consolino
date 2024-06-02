#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include "header.h"

int MainGame() {

	TERMINALSIZE terminalSize = getTerminalSize();

	//printf("terminal size %d %d", terminalSize.columns, terminalSize.rows);

	char* mainBuffer = (char*)malloc(terminalSize.columns * terminalSize.rows * sizeof(char));

	clearBuffer(mainBuffer, &terminalSize);

	int dino_jump_height = 0;
	int dino_jump = 0;
	int cactus_pos = 50;



	do {
		if (dino_jump == 0) {
			if (kbhit() && getch() == ' ') {
				dino_jump = 1;
			}
		}

		clearBuffer(mainBuffer, &terminalSize);
		drawGround(mainBuffer, &terminalSize);

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
			printf("\x1b[2J");
			printf("\nGame over!!1111\n");
			return 0;
		}

		drawBuffer(mainBuffer, &terminalSize);

		//Sleep(10);
	} while (1);

	free(mainBuffer);

	return 0;
}