#pragma once
#include <stdio.h>

typedef struct TerminalSize {
	int columns;
	int rows;
} TERMINALSIZE;

typedef struct member {
	char name[30];
	int highscore;
} MEMBER;


int options(int* n);
TERMINALSIZE getTerminalSize();
void drawBuffer(char*, TERMINALSIZE*);
void clearBuffer(char*, TERMINALSIZE*);
void putCharacter(char*, TERMINALSIZE*, int, int, char);
void drawGround(char*, TERMINALSIZE*);
void drawCactus(char*, TERMINALSIZE*, int);
void drawDino(char*, TERMINALSIZE*, int, int);