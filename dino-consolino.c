#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include "header.h"


int main()
{
	/*FILE* fp = ("highscore.txt", "w");
	if (fp==NULL)
	{
		exit(EXIT_FAILURE);
	}

	int uvijet = 1;

	while (uvijet)
	{
		odabir(&uvijet);
	}*/

	TERMINALSIZE terminalSize = getTerminalSize();

	//printf("terminal size %d %d", terminalSize.columns, terminalSize.rows);

	char* mainBuffer = (char*)malloc(terminalSize.columns * terminalSize.rows * sizeof(char));

	clearBuffer(mainBuffer, &terminalSize);

	int dino_jump_height = 0;
	int dino_jump = 0;
	int i = 0;

	dino_jump = 1;

	do {
		if (kbhit() && getch() == ' ') {
			dino_jump = 1;
		}

		drawBuffer(mainBuffer, &terminalSize);
		clearBuffer(mainBuffer, &terminalSize);
		drawGround(mainBuffer, &terminalSize);

		if (i <= 0) {
			i=50;
		}
		else {
			i -=2;
		}
		drawCactus(mainBuffer, &terminalSize, i);
		


		dino_jump_height += dino_jump;
		if (dino_jump_height >= 4) {
			dino_jump = -1;
		}
		else if (dino_jump_height <= 0 && dino_jump != 0) {
			dino_jump = 0;
		}
		drawDino(mainBuffer, &terminalSize, 1, 5 + dino_jump_height);

		Sleep(500);
	} while (1);

	free(mainBuffer);

	return 0;
}
