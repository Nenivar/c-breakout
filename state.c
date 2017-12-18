#include <malloc.h>

#include "grid.h"
#include "paddle.h"
#include "ball.h"

#include "state.h"

/*
 *  STRUCTURES
 */
struct state {
    grid *g;
    paddle *p;
    ball *b;
};
typedef struct state state;

/*
 *  ACCESS
 */
state *newState (grid *g, paddle *p, ball *b) {
    state *s = malloc (sizeof (state));
    s->g = g;
    s->p = p;
    s->b = b;
    return s;
}

grid *getGrid (state *s) {
    return s->g;
}

paddle *getPaddle (state *s) {
    return s->p;
}

ball *getBall (state *s) {
    return s->b;
}

void freeState (state *s) {
    free (s->g);
    free (s->p);
    free (s->b);
    free (s);
}