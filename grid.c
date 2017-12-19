#include <assert.h>
#include <malloc.h>
#include <stdint.h>

#include "grid.h"

/*
 *  STRUCTURES
 */
struct grid {
    uint8_t width, height;
    TILE **map;
};

/*
 *  ERROR HANDLING
 */
// out of bounds check
void gridOobCheck (grid *g, uint8_t x, uint8_t y) {
    if (!(x>= 0 && x < g->width && y>= 0 && y < g->height)){
        char error [50];
        sprintf (error, "Grid position (%d, %d) out of bounds (%d, %d)!",
                x, y, g->width, g->height);
        fail (error);
    }
}

/*
 *  GRID MANIPULATION
 */

grid *newGrid (uint8_t width, uint8_t height) {
    grid *g = malloc (sizeof (g));
    g->width = width; g->height = height;

    g->map = malloc (sizeof (TILE) * width * 2);
    for (int i = 0; i < width; i++)
        g->map [i] = malloc (sizeof (TILE) * height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++){
            g->map [x] [y] = AIR;
            if (y == 0) g->map [x] [y] = WALL;
            if (x == 0) g->map [x] [y] = WALL;
            if (x == width - 1) g->map [x] [y] = WALL;
        }
    }

    return g;
}

void setTileAt (grid *g, TILE tile, uint8_t x, uint8_t y) {
    gridOobCheck (g, x, y);
    g->map [x] [y] = tile;
}

TILE getTileAt (grid *g, uint8_t x, uint8_t y) {
    gridOobCheck (g, x, y);
    return g->map [x] [y];
}

uint8_t getGridWidth (grid *g) {
    return g->width;
}

uint8_t getGridHeight (grid *g) {
    return g->height;
}

void freeGrid (grid *g) {
    for (int i = 0; i < getGridWidth (g); i++) free (g->map [i]);
    free (g);
}

/*
 *  TESTING
 */
int gridMain () {
    grid *new = newGrid (20, 5);
    assert (new->width == 20);
    assert (new->height == 5);
    
    assert (getTileAt (new, 0, 0) == WALL);
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