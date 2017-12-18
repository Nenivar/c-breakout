#include <assert.h>
#include <malloc.h>
#include <stdint.h>

#include "state.h"
#include "grid.h"

#include "paddle.h"

/*
 *  STRUCTURES
 */

const int PADDLE_WIDTH = 5;
const int PADDLE_HEIGHT = 1;
const int PADDLE_Y = 10;

struct paddle {
    grid *g;
    float x;
};
typedef struct paddle paddle;

/*
 *  PADDLE MANIPULATION
 */
paddle *newPaddle (grid *g) {
    paddle *p = malloc (sizeof (paddle));
    p->g = g;
    p->x = 0;
    return p;
}

void movePaddle (paddle *p, float dx) {
    float newLoc = p->x + dx;

    if (newLoc >= 0 && (newLoc + PADDLE_WIDTH) < getWidth (p->g))
        p->x = newLoc;
}

float getPaddleX (paddle *p) {
    return p->x;
}

void freePaddle (paddle *p) {
    free (p);
}

/*
 *  TESTING
 */
void testPaddle (grid *g) {
    paddle *p = newPaddle (g);

    assert (getPaddleX (p) == 0);
    movePaddle (p, -1);
    assert (getPaddleX (p) == 0);
    movePaddle (p, 10);
    assert (getPaddleX (p) == 10);
    movePaddle (p, 100);
    assert (getPaddleX (p) == 10);
    movePaddle (p, -10);
    assert (getPaddleX (p) == 0);
    movePaddle (p, getWidth (g) - PADDLE_WIDTH - 1);
    assert (getPaddleX (p) == getWidth (g) - PADDLE_WIDTH - 1);
    movePaddle (p, 1);
    assert (getPaddleX (p) == getWidth (g) - PADDLE_WIDTH - 1);

    freePaddle (p);
}