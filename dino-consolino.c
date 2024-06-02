#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include "header.h"


int main()
{
	int uvijet = 1;
	FILE* fp = fopen("highscores.bin", "rb+");
	if (fp == NULL)
	{
		fp = fopen("highscores.bin", "wb+");
		fwrite(&PlayerCount, sizeof(int), 1, fp);
	}
	else
	{
		fread(&PlayerCount, sizeof(int), 1, fp);
	}

	while (uvijet)
	{
		odabir(&uvijet, fp);
	}

	fclose(fp);

	return 0;
}
