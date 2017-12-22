#include <stdio.h>

#include "number.h"

const uint8_t NUM_HEIGHT = 5;
const uint8_t NUM_WIDTH = 4;

const int ZERO_ [5] [4] = {
    {1,1,1,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1}
};
const int ONE_ [5] [4] = {
    {0,1,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {1,1,1,1}
};
const bool *ZERO [4] [5] = {
    {true,   true,   true,   true},
    {true,  false,   false,  true},
    {true,  false,   false,  true},
    {true,  false,   false,  true},
    {true,   true,   true,   true}
};
const bool *ONE = {
    false,  false,  true,   false,
    false,  true,   true,   false,
    true,   false,  true,   false,
    false,  false,  true,   false,
    false,  true,   true,   true
};
const bool *TWO = {
    false,  true,   true,   true,
    true,   false,  false,  true,
    false,  false,  true,   false,
    false,  true,   false,  false,
    true,   true,   true,   true
};
const bool *THREE = {
    true,   true,   true,   true,
    true,   false,  false,  true,
    true,   true,   true,   true,
    true,   false,  false,  true,
    true,   true,   true,   true    
};

static void placeDigitArrayAt (const int array [NUM_HEIGHT] [NUM_WIDTH], grid *g, uint8_t x, uint8_t y) {
    //printf ("\nnew\n");
    /*for (int yy = 0; yy < NUM_HEIGHT; yy++) {
        for (int xx = 0; xx < NUM_WIDTH; xx++) if (array [xx] [yy] == 1) setTileAt (g, WALL, xx + x, yy + y);
    }*/
    for (int yy = 0; yy < NUM_WIDTH; yy++) {
        for (int xx = 0; xx < NUM_HEIGHT; xx++) setTileAt (g, array [xx] [yy], yy + x, xx + y);//printf ("%d", array [xx] [yy]);
        //printf ("\n");
    }
    /*int row = 0;
    for (int i = 0; i < NUM_HEIGHT * NUM_WIDTH; i++) {
        int x = i % NUM_WIDTH;
        if (array [x + row * NUM_WIDTH]) setTileAt (g, WALL, x, row);
        if ((i + 1) % NUM_WIDTH == 0) row++;
    }*/
}

static void placeDigitAt (uint8_t digit, grid *g, uint8_t x, uint8_t y) {
    switch (digit) {
        case 0:
            placeDigitArrayAt (ZERO_, g, x, y); break;
        case 1:
            placeDigitArrayAt (ONE_, g, x, y); break;
        /*case 2:
            placeDigitArrayAt (TWO, g, x, y); break;
        case 3:
            placeDigitArrayAt (THREE, g, x, y); break;*/
    }
}

void placeNumberAt (uint8_t num, grid *g, uint8_t x, uint8_t y) {
    int digits [10], c = 0;

    if (num == 0) {
        digits [0] = 0;
        c = 1;
    } else {
        while (num > 0) {
            digits [c] = num % 10;
            printf ("%d\n", num % 10);
            num /= 10;
            c++;
        }
    }
    printf ("\n");
    for (int i = 0; i < c; i++) placeDigitAt (digits [i], g, x + (NUM_WIDTH + 1) * (c - i - 1), y);//printf ("i%d:%d,", i, digits [i]);
    printf ("\n");
}

/*
 *  TESTING
 */

int numberMain () {
    grid *g = newGrid (20, 20);
    placeNumberAt (23, g, 1, 0);

    succeed ("Number module OK");
    return 0;
}