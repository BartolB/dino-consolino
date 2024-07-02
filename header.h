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

extern int PlayerCount;

int MainGame();
int odabir(FILE** fp);
TERMINALSIZE getTerminalSize();
void drawBuffer(wchar_t*, TERMINALSIZE*);
void clearBuffer(wchar_t*, TERMINALSIZE*);
void putCharacter(wchar_t*, TERMINALSIZE*, int, int, wchar_t);
void drawGround(wchar_t*, TERMINALSIZE*);
void drawCactus(wchar_t*, TERMINALSIZE*, int);
int drawDinoAndCheck(wchar_t*, TERMINALSIZE*, int, int);
void LoadingGame(FILE*);
void* loadingplayers(FILE*);
void PrintingPlayers(MEMBER*);
int ExitProgram(MEMBER*);
void* FindPlayer(MEMBER*, char*);
void DeleteDocument(FILE*);