#include <stdint.h>

#include "base.h"

// types of tiles in the grid
enum TILE {
    AIR, WALL, BRICK_BLU, BRICK_GRN, BRICK_YLW, BRICK_BRN, BRICK_ORG, BRICK_RED
};
typedef enum TILE TILE;


// 2D array of uint8_t
struct grid;
typedef struct grid grid;

// create a new grid with a given width & height
// starts filled with AIR & a wall
grid *newGrid (uint8_t width, uint8_t height);
// safely deletes a given grid
void freeGrid (grid *g);

// set a tile to a type at the given x, y pos.
void setTileAt (grid *g, TILE tile, uint8_t x, uint8_t y);
// returns the tile at the given x, y pos.
TILE getTileAt (grid *g, uint8_t x, uint8_t y);

// returns the width of the grid
uint8_t getGridWidth (grid *g);
// returns the height of the grid
uint8_t getGridHeight (grid *g);

// checks whether a given x, y pos. is inside the grid
void gridOobCheck (grid *g, uint8_t x, uint8_t y);