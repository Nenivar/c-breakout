#include <malloc.h>

#include "grid.h"
#include "paddle.h"

/*
 *  STRUCTURES
 */
struct state {
    grid *g;
    paddle *p;
};
typedef struct state state;

/*
 *  ACCESS
 */
state *newState (grid *g) {
    state *s = malloc (sizeof (state));
    s->g = g;
    return s;
}

grid *getGrid (state *s) {
    return s->g;
}

void freeState (state *s) {
    free (s->g);
    free (s);
}