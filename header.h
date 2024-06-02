#pragma once
#include <stdio.h>

typedef struct TerminalSize {
	int columns;
	int rows;
} TERMINALSIZE;

typedef struct member
{
	int score;
	char ime[20];
} MEMBER;

static int PlayerCount = 0;

int MainGame();
void odabir(int* n, FILE* fp);
TERMINALSIZE getTerminalSize();
void drawBuffer(char*, TERMINALSIZE*);
void clearBuffer(char*, TERMINALSIZE*);
void putCharacter(char*, TERMINALSIZE*, int, int, char);
void drawGround(char*, TERMINALSIZE*);
void drawCactus(char*, TERMINALSIZE*, int);
int drawDinoAndCheck(char*, TERMINALSIZE*, int, int);
void unosKorisnika(FILE*);
void* loadingplayers(FILE*);
void ispisivanjekorisnika(MEMBER*);
int izlazizprograma(MEMBER*);
void* pronalazakKorisnika(MEMBER*, char*);
void brisanjeDatoteke(FILE*);