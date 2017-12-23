#include <stdbool.h>

#include "base.h"

// types of tiles in the grid
enum TILE {
    AIR, WALL, BRICK_BLU, BRICK_GRN, BRICK_YLW, BRICK_BRN, BRICK_ORG, BRICK_RED
};
typedef enum TILE TILE;

// the space required from the top for the score
extern const int TOP_SPACE;

// 2D array of int
struct grid;
typedef struct grid grid;

// create a new grid with a given width & height
// min grid height & width = ()
// starts filled with AIR, a wall, and some bricks
grid *newGrid (uint8_t width, uint8_t height, int layers);
// safely deletes a given grid
void freeGrid (grid *g);

// returns the width of an individual tile
// for hitbox, drawing
int getTileWidth ();
// returns the no. tiles in the x dir.
int getGridWidth (grid *g);
// returns the no. tiles in the y dir.
int getGridHeight (grid *g);
// returns the no. layers of bricks
int getLayers (grid *g);

// set a tile to a type at the given x, y pos.
void setTileAt (grid *g, TILE tile, uint8_t x, uint8_t y);
// set a tile to a type at the given x, y world pos.
void setTileAtWorld (grid *g, TILE tile ,uint8_t x, uint8_t y);
// returns the tile at the given x, y pos.
TILE getTileAt (grid *g, uint8_t x, uint8_t y);
// returns the tile at the given x, y world pos.
TILE getTileAtWorld (grid *g, uint8_t x, uint8_t y);

// checks whether a given x, y pos. is inside the grid
void gridOobCheck (grid *g, uint8_t x, uint8_t y);
// returns whether a position is within a grid or not
bool isWithinGrid (grid *g, uint8_t x, uint8_t y);