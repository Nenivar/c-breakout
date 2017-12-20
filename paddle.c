#include <assert.h>
#include <malloc.h>
#include <stdint.h>

#include "paddle.h"

/*
 *  STRUCTURES
 */
const float PADDLE_WIDTH = 7;
const float PADDLE_HEIGHT = 0.6f;

struct paddle {
    grid *g;
    float x;
};

/*
 *  PADDLE MANIPULATION
 */
paddle *newPaddle (grid *g) {
    paddle *p = malloc (sizeof (paddle));
    p->g = g;
    p->x = (getGridWidth (g) - PADDLE_WIDTH) / 2;
    return p;
}

void movePaddle (paddle *p, float dx) {
    float newLoc = p->x + dx;

    if (newLoc >= 0 && (newLoc + PADDLE_WIDTH) < getGridWidth (p->g) * getTileWidth ())
        p->x = newLoc;
}

float getPaddleX (paddle *p) {
    return p->x;
}

float getPaddleY (paddle *p) {
    return getGridHeight (p->g) - PADDLE_HEIGHT;
}

float getPaddleWidth () {
    return PADDLE_WIDTH;
}

float getPaddleHeight () {
    return PADDLE_HEIGHT;
}

void freePaddle (paddle *p) {
    free (p);
}

/*
 *  TESTING
 */
int paddleMain () {
    grid *g = newGrid (25, 10);
    paddle *p = newPaddle (g);

    uint8_t startX = (25 - PADDLE_WIDTH) / 2;

    assert (getPaddleX (p) == startX);
    movePaddle (p, -1);
    assert (getPaddleX (p) == startX - 1);
    movePaddle (p, -startX + 1);
    assert (getPaddleX (p) == 0);
    movePaddle (p, -3);
    assert (getPaddleX (p) == 0);
    movePaddle (p, 10);
    assert (getPaddleX (p) == 10);
    movePaddle (p, 100);
    assert (getPaddleX (p) == 10);
    movePaddle (p, -10);
    assert (getPaddleX (p) == 0);
    movePaddle (p, getGridWidth (g) - PADDLE_WIDTH - 1);
    assert (getPaddleX (p) == getGridWidth (g) - PADDLE_WIDTH - 1);
    movePaddle (p, 1);
    assert (getPaddleX (p) == getGridWidth (g) - PADDLE_WIDTH - 1);

    freePaddle (p);
    succeed ("Paddle module OK");
    return 0;
}