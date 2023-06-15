#ifndef _SKOCKO_H
#define _SKOCKO_H 1

#define SQUARE  0x25A0
#define HEART   0x2665
#define DIAMOND 0x2666
#define CLUB    0x2663
#define SPADE   0x2660
#define SMILE	0x263B
#define STAR	0x2605

int
	symbols[6] = {HEART, DIAMOND, CLUB, SPADE, SMILE, STAR},
    used_symbols[4],
    comb[4],
    places[4],
    temp[4];

int
    i, y,
    trys,
    count,
    key,
    check;

int getch();
int comb_check();

void key_check();

#endif