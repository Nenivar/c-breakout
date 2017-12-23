#include <assert.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>

#include "grid.h"

/*
 *  STRUCTURES
 */
struct grid {
    int width, height, layers;
    TILE **map;
};

const int TOP_SPACE = 6;

/*
 *  ERROR HANDLING
 */
// out of bounds check
void gridOobCheck (grid *g, uint8_t x, uint8_t y) {
    if (!(x>= 0 && x < g->width && y>= 0 && y < g->height)){
        char error [50];
        sprintf (error, "Grid position (%d, %d) out of bounds (%d, %d)!",
                x, y, g->width - 1, g->height - 1);
        fail (error);
    }
}

/*
 *  GRID MANIPULATION
 */

void populateGrid (grid *g, int startY, int layers) {
    TILE colourCycle = BRICK_RED;
    printf ("\n\nPOPULATE\n\n");
    
    for (int y = startY; y < startY + layers; y++) {
        for (int i = 1; i < g->width - 1; i++) {
            
            g->map [i] [y] = colourCycle;

        /*g->map [i] [startY] = BRICK_RED;
        g->map [i] [startY + 1] = BRICK_ORG;
        g->map [i] [startY + 2] = BRICK_YLW;
        g->map [i] [startY + 3] = BRICK_GRN;
        g->map [i] [startY + 4] = BRICK_BLU;*/
        }

        colourCycle = colourCycle <= BRICK_BLU
            ? BRICK_RED : colourCycle - 1;
    }
}

grid *newGrid (uint8_t width, uint8_t height) {
    grid *g = malloc (sizeof (g));
    g->width = width; g->height = height;

    g->map = malloc (sizeof (TILE) * width * 2);
    for (int i = 0; i < width; i++)
        g->map [i] = malloc (sizeof (TILE) * height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++){
            g->map [x] [y] = AIR;
            if (y == 6 || (x == 0 && y >= 6) || (x == width - 1 && y >= 6))
                g->map [x] [y] = WALL;
        }
    }

    g->layers = 6;

    populateGrid (g, TOP_SPACE + 1, g->layers);

    return g;
}

void setTileAt (grid *g, TILE tile, uint8_t x, uint8_t y) {
    gridOobCheck (g, x, y);
    g->map [x] [y] = tile;
}

void setTileAtWorld (grid *g, TILE tile, uint8_t x, uint8_t y) {
    setTileAt (g, tile, x / getTileWidth (), y);
}

TILE getTileAt (grid *g, uint8_t x, uint8_t y) {
    gridOobCheck (g, x, y);
    return g->map [x] [y];
}

TILE getTileAtWorld (grid *g, uint8_t x, uint8_t y) {
    return getTileAt (g, x / getTileWidth (), y);   
}

int getTileWidth () {
    return 4;
}

int getGridWidth (grid *g) {
    return g->width;
}

int getLayers (grid *g) {
    return g->layers;
}

int getGridHeight (grid *g) {
    return g->height;
}

bool isWithinGrid (grid *g, uint8_t x, uint8_t y) {
    return x >= 0 && x < g->width
        && y >= 0 && y < g->height;
}

bool isWithinGridWorld (grid *g, uint8_t x, uint8_t y) {
    return isWithinGridWorld (g, x / getTileWidth (), y);
}

void freeGrid (grid *g) {
    for (int i = 0; i < getGridWidth (g); i++) free (g->map [i]);
    free (g);
}

/*
 *  TESTING
 */
int gridMain () {
    grid *new = newGrid (20, 15);
    assert (new->width == 20);
    assert (new->height == 15);
    
    assert (getTileAt (new, 0, TOP_SPACE) == WALL);
    assert (getTileAt (new, 10, 3) == AIR);
    assert (getTileAt (new, 9, 2) == AIR);

    setTileAt (new, BRICK_RED, 9, 2);
    assert (new->map [9] [2] == BRICK_RED);
    assert (getTileAt (new, 9, 2) == BRICK_RED);
    setTileAt (new, BRICK_YLW, 9, 2);
    assert (getTileAt (new, 9, 2) == BRICK_YLW);

    freeGrid (new);
    succeed ("Grid module OK");
    return 0;
}