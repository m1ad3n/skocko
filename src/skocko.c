#include "skocko.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

int getch()
{
    struct termios oldattr, newattr;
    int ch;

    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );

    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );

    return ch;
}

int main()
{
    setlocale(LC_ALL, "");
    srand(time(0));

    count = 0;
    trys = 0;
    key = 0x0;

    for (i = 0; i < 4; i++)
    {
        places[i] = 0;
        comb[i] = symbols[rand() % 6];
    }

    printf("\n");
    for (i = 0; i < 6; i++)
        printf("%lc - %d\n", symbols[i], i + 1);
    printf("\n");

    while (key != 113)
    {
        key_check();

        if (count == 4)
        {
            check = comb_check();
            if (check == 1 || check == 2) break;
        }

        key = getch();
    }
       
    if (key != 0x71)
    {
        printf("\nWanna play again [y/N] ");
        if (getch() == 121)
        {
            system("clear");
            main();
        }
    }

    printf("\nGoodbye\n\n");
    return 0;
}

void key_check()
{
    if (key == 127)
    {
        if (count == 0) printf("%c", 7);
        else
        {
            for (i = count; i < 5; i++)
                printf("  ");
            
            printf("CANCELLED\n");
            count = 0;
        }
    }
    else if (key >= 49 && key <= 54)
    {
        printf("%lc ", symbols[(int)key - 49]);
        used_symbols[count++] = symbols[(int)key - 49];
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
            printf("\033[0;31m");
            printf(" %lc", SQUARE);
        }
    }

    for (i = 0; i < 4; i++)
    {
        if (places[i] == 2)
        {
            printf("\033[1;93m");

            printf(" %lc", SQUARE);
        }
    }

    printf("\033[0;37m");

    for (i = 0; i < 4; i++)
        if (places[i] == 0)
            printf(" %lc", SQUARE);

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
            printf("%lc ", comb[i]);
        }

        printf("\n");
        return 2;
    }

    printf("\n");
    return 0;
}