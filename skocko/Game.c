#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#ifdef _WIN32
    #include <Windows.h>
#endif

char symbols[5], used_symbols[4], comb[4], places[4], temp[4];
int i, y, trys, count, key, check;

void key_check();
int comb_check();

int main()
{
    srand(time(0));

    count = 0;
    trys = 0;
    key = 0x0;

    for (i = 0; i < 5; i++)
        symbols[i] = i + 2;

    for (i = 0; i < 4; i++)
    {
        places[i] = 0;
        comb[i] = symbols[rand() % 5];
    }

    for (i = 2; i < 7; i++)
        printf("%c - %d\n", i, i - 1);
    printf("\n");

    for ( ; key != 0x71 ; )
    {
        key_check();

        if (count == 4)
        {
            check = comb_check();
            if (check == 1 || check == 2) break;
        }

        key = _getch();
    }
       
    if (key != 0x71)
    {
        printf("\nWanna play again [y/N] ");
        if (_getch() == 'y')
        {
            #ifdef _WIN32
                system("cls");
            #elif defined(__linux__)
                system("clear");
            #endif

            main();
        }
    }
}

int comb_check()
{
    count = 0;

    for (i = 0; i < 4; i++)
        temp[i] = comb[i];

    for (i = 0; i < 4; i++)
    {
        if (used_symbols[i] == comb[i])
        {
            places[i] = 1;
            used_symbols[i] = 221;
            temp[i] = 220;
        }
    }

    for (i = 0; i < 4; i++)
    {
        if (places[i]) continue;
        for (y = 0; y < 4; y++)
        {
            if (used_symbols[i] == temp[y])
            {
                places[i] = 2;
                temp[y] = 220;
                break;
            }
        }
    }

    printf(" ");

    for (i = 0; i < 4; i++)
    {
        if (places[i] == 1)
        {
            #ifdef _WIN32
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            #elif defined(__linux__)
                printf("\033[0;31m");
            #endif

            printf(" %c", 254);
        }
    }

    for (i = 0; i < 4; i++)
    {
        if (places[i] == 2)
        {
            #ifdef _WIN32
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            #elif defined(__linux__)
                printf("\033[0;33m");
            #endif

            printf(" %c", 254);
        }
    }

    #ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    #elif defined(__linux__)
        printf("\033[0;37m");
    #endif

    for (i = 0; i < 4; i++)
        if (places[i] == 0)
            printf(" %c", 254);

    if (places[0] == places[1]
        && places[1] == places[2]
        && places[0] == places[3]
        && places[3] == 1)
    {
        printf("\n\nYou won\n");
        return 1;
    }

    for (i = 0; i < 4; i++)
        places[i] = 0;

    if (++trys == 6)
    {
        printf("\n\nYou lost\nWanted Combination: ");

        for (i = 0; i < 4; i++)
        {
            #ifdef _WIN32
                printf("%c ", comb[i]);
            #elif defined(__linux__)
                printf("%d ", comb[i]);
            #endif
        }

        printf("\n");
        return 2;
    }

    printf("\n");
    return 0;
}

void key_check()
{
    if (key == 8)
    {
        if (count == 0) printf("%c", 7);
        else
        {
            for (i = count; i < 4; i++)
                printf("  ");
            
            printf("  CANCELLED\n");
            count = 0;
        }
    }
    else if (key >= 49 && key <= 53)
    {
        printf("%c ", symbols[(int)key - 49]);
        used_symbols[count++] = symbols[(int)key - 49];
    }
}