#include <stdint.h>

enum TILE;
typedef enum TILE TILE;

struct grid;
typedef struct grid grid;

grid *newGrid (uint8_t width, uint8_t height);
void freeGrid (grid *g);

// adds a tile at the given x, y pos.
void setTileAt (grid *g, TILE tile, uint8_t x, uint8_t y);
// returns the tile at the given x, y pos.
TILE getTileAt (grid *g, uint8_t x, uint8_t y);

uint8_t getWidth (grid *g);
uint8_t getHeight (grid *g);

bool gridOobCheck (grid *g, uint8_t x, uint8_t y);