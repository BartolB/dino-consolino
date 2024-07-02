#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int odabir(FILE** fp)
{
    int n = 0;
    do
    {
        wprintf(L"\n");
        wprintf(L"Odaberite jednu od ponudenih opcija: \n");
        wprintf(L"\n");
        wprintf(L"Opcija 1: Pokreni igricu! \n");
        wprintf(L"Opcija 2: Procitati highscorove i imena\n");
        wprintf(L"Opcija 3: Potraziti korisnika po njegovom imenu i ispisivanje! \n");
        wprintf(L"Opcija 4: Obrisi datoteku s highscorovima \n");
        wprintf(L"Opcija 5: Zavrsiti s programom! \n");
        n = 0;
        scanf("%d", &n);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } while (n < 1 || n > 5);
   
    MEMBER* PlayerArray = (MEMBER*)loadingplayers(*fp);
    char findname[20] = { "\0" };

    switch (n)
    {
    case 1:
        LoadingGame(*fp);
        break;
    case 2:
        if (PlayerArray != NULL)
        {
            PrintingPlayers(PlayerArray);
        }
        break;

    case 3:
        wprintf(L"Unesite ime korisnika!\n");
        getchar();
        scanf("%19[^\n]", findname);

        FindPlayer(PlayerArray, findname);
        break;

    case 4:
        DeleteDocument(*fp);
        PlayerCount = 0;
        *fp = NULL;
        break;
    case 5:
        n = ExitProgram(PlayerArray);
    default:
        break;
    }

    return n;
}

void LoadingGame(FILE* fp)
{
    rewind(fp);
    fread(&PlayerCount, sizeof(int), 1, fp);
    wprintf(L"Broj korisnika: %d\n", PlayerCount);
    MEMBER temp = { 0 };
    wprintf(L"Unesite ime korisnika! \n");
    scanf("%19[^\n]", temp.ime);
    getchar();
    wprintf(L"\n");
    temp.score  = MainGame();
    fseek(fp, sizeof(int) + sizeof(MEMBER) * PlayerCount, SEEK_SET);
    fwrite(&temp, sizeof(MEMBER), 1, fp);
    rewind(fp);
    PlayerCount++;
    fwrite(&PlayerCount, sizeof(int), 1, fp);
    wprintf(L"\n");
}

int ExitProgram(MEMBER* player)
{
    if (player != NULL)
    {
        free(player);
    }
    wprintf(L"Zelite li uistinu izaci iz programa?\n");
    wprintf(L"Utipkajte \"da\" ako uistinu zelite izaci iz programa u suprotno utipkajte \"ne\"!\n");
    char potvrda[3] = { 0 };
    scanf("%2s", potvrda);

    if (!strcmp("da", potvrda) || !strcmp("Da", potvrda) || !strcmp("DA", potvrda))
    {
        exit(EXIT_SUCCESS);
    }
    else
        return 1;
}

void* loadingplayers(FILE* fp)
{
    rewind(fp);
    fread(&PlayerCount, sizeof(int), 1, fp);
    MEMBER* poljekorisnika = (MEMBER*)calloc(PlayerCount, sizeof(MEMBER));

    if (PlayerCount == 0)
    {
        perror("Zauzimanje memorije za korisnike");
        return NULL;
    }
    fread(poljekorisnika, sizeof(MEMBER), PlayerCount, fp);

    return poljekorisnika;
}

int compare_player(const void* p, const void* q)
{
    MEMBER x = *(MEMBER*)p;
    MEMBER y = *(MEMBER*)q;

    if (x.score < y.score) {
        return 1;
    }
    else if (x.score > y.score) {
        return -1;
    }

    return 0;
}

void sortPlayers(MEMBER* playerarray, int n)
{
    qsort(playerarray, n, sizeof(MEMBER), compare_player);
}


void PrintingPlayers(MEMBER* player)
{

    if (player == NULL)
    {
        wprintf(L"Polje korisnika je prazno!\n");
        return;
    }

    sortPlayers(player, PlayerCount);

    for (int i = 0; i < PlayerCount; i++)
    {
        
        wprintf(L"Ime: %hs\tScore: %d\n",
            (player + i)->ime,
            (player + i)->score);
    }
}


void* FindPlayer(MEMBER* playerarray, char* find)
{
    if (playerarray == NULL)
    {
        wprintf(L"Polje korisnika je prazno!\n");
        return NULL;
    }

    for (int i = 0; i < PlayerCount; i++)
    {
        if (!strcmp(find, (playerarray + i)->ime))
        {
            wprintf(L"Korisnik je pronaden!\n");
            wprintf(L"Ime:%hs\tScore:%d\n", (playerarray + i)->ime, (playerarray + i)->score);
            return NULL;
        }
    }

    wprintf(L"Korisnik sa takvim imenom ne postoji!\n");
    return NULL;
}

void DeleteDocument(FILE* fp)
{
    char* filename = "highscores.bin";
    wprintf(L"Zelite li uistinu obrisati datoteku?\n");
    wprintf(L"Utipkajte \"da\" ako uistinu zelite obrisati datoteku u suprotno utipkajte\
    \"ne\"!\n");
    char potvrda[3] = { '\0' };
    scanf("%2s", potvrda);
    if (!strcmp("da", potvrda))
    {
        fclose(fp);
        remove(filename) == 0 ? wprintf(L"Uspjesno obrisana datoteka!\n")
            : wprintf(L"Neuspjesno brisanje datoteke!\n");
    }
}