#include <assert.h>
#include <malloc.h>
#include <stdint.h>

#include "state.h"
#include "grid.h"

/*
 *  STRUCTURES
 */

const int PADDLE_WIDTH = 5;

struct paddle {
    grid *g;
    uint8_t x;
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

void movePaddle (paddle *p, uint8_t dx) {
    uint8_t newLoc = p->x + dx;

    if (newLoc >= 0 && (newLoc + PADDLE_WIDTH) < getWidth (p->g))
        p->x = newLoc;
}

uint8_t getPaddleX (paddle *p) {
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