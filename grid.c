#include <assert.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdint.h>

#include "grid.h"

/*
 *  STRUCTURES
 */
enum TILE {
    AIR, WALL, BRICK_RED, BRICK_YLW, BRICK_GRN
};
typedef enum TILE TILE;

struct grid {
    uint8_t width, height;
    TILE **map;
};
typedef struct grid grid;

/*
 *  ERROR HANDLING
 */
// out of bounds check
bool gridOobCheck (grid *g, uint8_t x, uint8_t y) {
    if (!(x>= 0 && x < g->width
        && y>= 0 && y < g->height)) return true;
    return false;
}

/*
 *  GRID MANIPULATION
 */
// creates new grid & fills it with AIR
grid *newGrid (uint8_t width, uint8_t height) {
    grid *g = malloc (sizeof (g));
    g->width = width; g->height = height;

    g->map = malloc (sizeof (TILE) * width * 2);
    for (int i = 0; i < width; i++)
        g->map [i] = malloc (sizeof (TILE) * height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) 
            g->map [x] [y] = AIR;
    }

    return g;
}

// adds a tile at the given x, y pos.
void setTileAt (grid *g, TILE tile, uint8_t x, uint8_t y) {
    gridOobCheck (g, x, y);
    g->map [x] [y] = tile;
}

// returns the tile at the given x, y pos.
TILE getTileAt (grid *g, uint8_t x, uint8_t y) {
    gridOobCheck (g, x, y);
    return g->map [x] [y];
}

uint8_t getWidth (grid *g) {
    return g->width;
}

uint8_t getHeight (grid *g) {
    return g->height;
}

void freeGrid (grid *g) {
    for (int i = 0; i < getWidth (g); i++) free (g->map [i]);
    free (g);
}

/*
 *  TESTING
 */
void testGrid () {
    grid *new = newGrid (20, 5);
    assert (new->width == 20);
    assert (new->height == 5);
    
    assert (getTileAt (new, 0, 0) == AIR);
    assert (getTileAt (new, 10, 3) == AIR);
    assert (getTileAt (new, 9, 2) == AIR);

    setTileAt (new, BRICK_RED, 9, 2);
    assert (new->map [9] [2] == BRICK_RED);
    assert (getTileAt (new, 9, 2) == BRICK_RED);
    setTileAt (new, BRICK_YLW, 9, 2);
    assert (getTileAt (new, 9, 2) == BRICK_YLW);

    freeGrid (new);
}