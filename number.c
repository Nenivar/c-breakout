#include <assert.h>

#include "number.h"

const int NUM_HEIGHT = 5;
const int NUM_WIDTH = 4;

const TILE ZERO [5] [4] = {
    {1,1,1,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1}
};
const TILE ONE [5] [4] = {
    {0,1,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {1,1,1,1}
};
const TILE TWO [5] [4] = {
    {1,1,1,1},
    {0,0,0,1},
    {0,1,1,0},
    {1,0,0,0},
    {1,1,1,1}
};
const TILE THREE [5] [4] = {
    {1,1,1,1},
    {0,0,0,1},
    {0,1,1,1},
    {0,0,0,1},
    {1,1,1,1}
};
const TILE FOUR [5] [4] = {
    {0,0,1,0},
    {0,1,1,0},
    {1,1,1,1},
    {0,0,1,0},
    {0,0,1,0}
};
const TILE FIVE [5] [4] = {
    {1,1,1,1},
    {1,0,0,0},
    {1,1,1,0},
    {0,0,0,1},
    {1,1,1,0}
};
const TILE SIX [5] [4] = {
    {0,1,1,1},
    {1,0,0,0},
    {1,1,1,0},
    {1,0,0,1},
    {0,1,1,0}
};
const TILE SEVEN [5] [4] = {
    {1,1,1,1},
    {0,0,0,1},
    {0,0,1,0},
    {0,1,0,0},
    {1,0,0,0}
};
const TILE EIGHT [5] [4] = {
    {1,1,1,1},
    {1,0,0,1},
    {1,1,1,1},
    {1,0,0,1},
    {1,1,1,1}
};
const TILE NINE [5] [4] = {
    {1,1,1,1},
    {1,0,0,1},
    {1,1,1,1},
    {0,0,0,1},
    {1,1,1,1}
};

// places a 2D array of TILE into a grid at an (x, y) pos.
static void placeDigitArrayAt (const TILE array [NUM_HEIGHT] [NUM_WIDTH], grid *g, int x, int y) {
    for (int yy = 0; yy < NUM_WIDTH; yy++)
        for (int xx = 0; xx < NUM_HEIGHT; xx++)
            setTileAt (g, array [xx] [yy], yy + x, xx + y);
}

// maps digits to 2D arrays
static void placeDigitAt (int digit, grid *g, int x, int y) {
    switch (digit) {
        case 0:
            placeDigitArrayAt (ZERO, g, x, y); break;
        case 1:
            placeDigitArrayAt (ONE, g, x, y); break;
        case 2:
            placeDigitArrayAt (TWO, g, x, y); break;
        case 3:
            placeDigitArrayAt (THREE, g, x, y); break;
        case 4:
            placeDigitArrayAt (FOUR, g, x, y); break;
        case 5:
            placeDigitArrayAt (FIVE, g, x, y); break;
        case 6:
            placeDigitArrayAt (SIX, g, x, y); break;
        case 7:
            placeDigitArrayAt (SEVEN, g, x, y); break;
        case 8:
            placeDigitArrayAt (EIGHT, g, x, y); break;
        case 9:
            placeDigitArrayAt (NINE, g, x, y); break;
    }
}

void placeNumberAt (int num, grid *g, int x, int y) {
    int digits [10], c = 0;

    if (num == 0) {
        digits [0] = 0;
        c = 1;
    } else {
        while (num > 0) {
            digits [c] = num % 10;
            num /= 10;
            c++;
        }
    }
    for (int i = 0; i < c; i++)
        placeDigitAt (digits [i], g, x + (NUM_WIDTH + 1) * (c - i - 1), y);
}

/*
 *  TESTING
 */

int numberMain () {
    grid *g = newGrid (20, 20, 0);
    placeNumberAt (23, g, 1, 0);

    assert (getTileAt (g, 0, 0) == AIR);
    assert (getTileAt (g, 1, 0) == WALL);

    succeed ("Number module OK");
    return 0;
}