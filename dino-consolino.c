#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#include <wchar.h>
#include "header.h"

int PlayerCount = 0;

int main()
{
	// unicode
	_setmode(_fileno(stdout), _O_U16TEXT);

	int uvjet = 1;

	FILE** fp = NULL;
	FILE* a = fopen("highscores.bin", "rb+");
	fp = &a;
	while (uvjet)
	{
		if (*fp == NULL)
		{
			*fp = fopen("highscores.bin", "wb+");
			fwrite(&PlayerCount, sizeof(int), 1, *fp);
		}
		else
		{
			rewind(*fp);
			fread(&PlayerCount, sizeof(int), 1, *fp);
		}
		uvjet = odabir(fp);
	}

	fclose(*fp);

	return 0;
}
