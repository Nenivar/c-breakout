#include "paddle.h"
#include "grid.h"

struct state;
typedef struct state state;

state *newState (grid *g);
void freeState ();

grid *getGrid (state *s);