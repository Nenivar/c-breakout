#include <assert.h>
#include <malloc.h>

#include "grid.h"

/*
 *  STRUCTURES
 */
struct grid {
    int width, height, layers,
        maxBreakable, bricksBroken;
    TILE **map;
};

const int TOP_SPACE = 6;

/*
 *  ERROR HANDLING
 */
void gridOobCheck (grid *g, int x, int y) {
    if (!isWithinGrid (g, x, y)) {
        char error [50];
        sprintf (error, "Grid position (%d, %d) out of bounds (%d, %d)!",
                x, y, g->width - 1, g->height - 1);
        fail (error);
    }
}

/*
 *  GRID MANIPULATION
 */

// fills a grid with layers of breakable bricks
void populateGrid (grid *g, int startY, int layers) {
    TILE colourCycle = BRICK_RED;

    for (int y = startY; y < startY + layers; y++) {
        for (int i = 1; i < g->width - 1; i++)
            g->map [i] [y] = colourCycle;       

        colourCycle = colourCycle <= BRICK_BLU
            ? BRICK_RED : colourCycle - 1;
    }
}

// creates a square wall grid from a y position
void wallGrid (grid *g, int startY) {
    for (int y = startY; y < g->height; y++) {
        for (int x = 0; x < g->width; x++) 
            if (y == startY || x == 0 || x == g->width - 1)
                g->map [x] [y] = WALL;
    }
}

grid *newGrid (int width, int height, int layers) {
    grid *g = malloc (sizeof (g) + sizeof (TILE) * width * 2);
    
    g->width = width; g->height = height;
    g->maxBreakable = layers * (width - 2); g->bricksBroken = 0;

    g->map = malloc (sizeof (TILE) * width * 2);
    for (int i = 0; i < width; i++)
        g->map [i] = malloc (sizeof (TILE) * height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++)
            g->map [x] [y] = AIR;
    }

    g->layers = layers;

    wallGrid (g, TOP_SPACE);
    if (layers != 0) populateGrid (g, TOP_SPACE + 3, g->layers);

    return g;
}

void freeGrid (grid *g) {
    for (int i = 0; i < getGridWidth (g); i++) free (g->map [i]);
    free (g);
}

void setTileAt (grid *g, TILE tile, int x, int y) {
    gridOobCheck (g, x, y);
    g->map [x] [y] = tile;
}

void setTileAtWorld (grid *g, TILE tile, int x, int y) {
    setTileAt (g, tile, x / getTileWidth (), y);
}

int getBricksBroken (grid *g) {
    return g->bricksBroken;
}

void increaseBricksBroken (grid *g) {
    g->bricksBroken++;
}

int getMaxBreakableBricks (grid *g) {
    return g->maxBreakable;
}

TILE getTileAt (grid *g, int x, int y) {
    gridOobCheck (g, x, y);
    return g->map [x] [y];
}

TILE getTileAtWorld (grid *g, int x, int y) {
    return getTileAt (g, x / getTileWidth (), y);   
}

int getGridWidth (grid *g) {
    return g->width;
}

int getGridHeight (grid *g) {
    return g->height;
}

int getLayers (grid *g) {
    return g->layers;
}

bool isWithinGrid (grid *g, int x, int y) {
    return x >= 0 && x < g->width
        && y >= 0 && y < g->height;
}

bool isWithinGridWorld (grid *g, int x, int y) {
    return isWithinGridWorld (g, x / getTileWidth (), y);
}

int getTileWidth () {
    return 4;
}

/*
 *  TESTING
 */
int gridMain () {
    grid *new = newGrid (20, 15, 0);
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