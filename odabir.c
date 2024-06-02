#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void odabir(int* n, FILE* fp)
{
    do
    {
        printf("Odaberite jednu od ponudenih opcija: \n");
        printf("\n");
        printf("Opcija 1: Pokreni igricu! \n");
        printf("Opcija 2: Procitati highscorove i imena\n");
        printf("Opcija 3: Potraziti korisnika po njegovom imenu i ispisivanje! \n");
        printf("Opcija 4: Obrisi datoteku s highscorovima \n");
        printf("Opcija 5: Zavrsiti s programom! \n");
        *n = 0;
        scanf("%d", n);
    } while (*n < 1 || *n > 5);

    static MEMBER* PlayerArray = NULL;
    char findname[20] = { "\0" };

    switch (*n)
    {
    case 1:
        unosKorisnika(fp);
        break;
    case 2:
        if (PlayerArray != NULL)
        {
            free(PlayerArray);
            PlayerArray = NULL;
        }
        PlayerArray = (MEMBER*)loadingplayers(fp);
        if (PlayerArray == NULL)
        {
            exit(EXIT_FAILURE);
        }
        if (PlayerArray != NULL)
        {
            ispisivanjekorisnika(PlayerArray);
        }
        break;

    case 3:
        printf("Unesite novi naziv datoteke!\n");
        getchar();
        scanf("%19[^\n]", findname);

        pronalazakKorisnika(PlayerArray, findname);
        break;

    case 4:
        brisanjeDatoteke(fp);
        break;
    case 5:
        *n = izlazizprograma(PlayerArray);
    default:
        break;
    }
}

void unosKorisnika(FILE* fp)
{
    rewind(fp);
    fread(&PlayerCount, sizeof(int), 1, fp);
    printf("Broj korisnika: %d\n", PlayerCount);
    MEMBER temp = { 0 };
    printf("Unesite ime korisnika! \n");
    getchar();
    scanf("%19[^\n]", temp.ime);
    getchar();
    temp.score  = MainGame();
    fseek(fp, sizeof(int) + sizeof(MEMBER) * PlayerCount, SEEK_SET);
    fwrite(&temp, sizeof(MEMBER), 1, fp);
    rewind(fp);
    PlayerCount++;
    printf("%d\n", PlayerCount);
    fwrite(&PlayerCount, sizeof(int), 1, fp);
    printf("\n");
}

int izlazizprograma(MEMBER* player)
{
    free(player);
    printf("Zelite li uistinu izaci iz programa?\n");
    printf("Utipkajte \"da\" ako uistinu zelite izaci iz programa u suprotno utipkajte \"ne\"!\n");
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
    printf("brojkorisnika: %d\n", PlayerCount);
    MEMBER* poljekorisnika = (MEMBER*)calloc(PlayerCount, sizeof(MEMBER));

    if (PlayerCount == 0)
    {
        perror("Zauzimanje memorije za studente");
        return NULL;
    }
    fread(poljekorisnika, sizeof(MEMBER), PlayerCount, fp);

    return poljekorisnika;
}

void ispisivanjekorisnika(MEMBER* player)
{

    if (player == NULL)
    {
        printf("Polje studenata je prazno!\n");
        return;
    }

    for (int i = 0; i < PlayerCount; i++)
    {
        printf("Ime: %s\tScore: %d\n",
            (player + i)->ime,
            (player + i)->score);
    }
}

void* pronalazakKorisnika(MEMBER* playerarray, char* find)
{

    if (playerarray == NULL)
    {
        printf("Polje studenata je prazno!\n");
        return NULL;
    }

    for (int i = 0; i < PlayerCount; i++)
    {
        if (!strcmp(find, (playerarray + i)->ime))
        {
            printf("Student je pronaden!\n");
            printf("Ime:%s\tScore:%d\n", (playerarray + i)->ime, (playerarray + i)->score);
            return NULL;
        }
    }

    printf("Student sa takvim imenom ne postoji!\n");
    return NULL;
}

void brisanjeDatoteke(FILE* fp)
{

    char* filename = "highscores.bin";
    printf("Zelite li uistinu obrisati datoteku?\n");
    printf("Utipkajte \"da\" ako uistinu želite obrisati datoteku u suprotno utipkajte\
    \"ne\"!\n");
    char potvrda[3] = { '\0' };
    scanf("%2s", potvrda);
    if (!strcmp("da", potvrda))
    {
        fclose(fp);
        remove(filename) == 0 ? printf("Uspjesno obrisana datoteka!\n")
            : printf("Neuspjesno brisanje datoteke!\n");
    }
}