#include <assert.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>

#include "ball.h"

/*
 *  STRUCTURES
 */
const int BALL_DIM = 1;

struct ball {
    float x, y,
            velX, velY;
    grid *g;
    paddle *p;
};

/*
 *  ACCESS
 */

ball *newBall (grid *g, paddle *p) {
    ball *b = malloc (sizeof (ball));
    b->x = getGridWidth (g) / 2;
    b->y = getGridHeight (g) / 2;
    b->velX = 0;
    b->velY = -0.5f;
    b->g = g;
    b->p = p;

    return b;
}

void freeBall (ball *b) {
    free (b);
}

float getBallX (ball *b) {
    return b->x;
}

float getBallY (ball *b) {
    return b->y;
}

float getBallVelX (ball *b) {
    return b->velX;
}

float getBallVelY (ball *b) {
    return b->velY;
}

/*
 *  MOVEMENT
 */
static void move (ball *b) {
    float x = b->x + b->velX;
    x = x > 0 ? x : 0;
    x = x < getGridWidth (b->g) ? x : getGridWidth (b->g);
    float y = b->y + b->velY;
    y = y > 0 ? y : 0;
    y = y < getGridHeight (b->g) ? y : getGridHeight (b->g);

    gridOobCheck (b->g, x, y);
    b->x = x; b->y = y;
}

static void onGridCollide (ball *b) {
    b->velX = -b->velX;
    b->velY = -b->velY;
}

static void onPaddleCollide (ball *b) {
    // algorithm
}

static bool checkGridCollision (ball *b) {
    return getTileAt (b->g, b->x, b->y) != AIR;
}

static bool checkPaddleCollision (ball *b) {
    return b->x >= getPaddleX (b->p)
        && b->x <= getPaddleX (b->p) + PADDLE_WIDTH
        && b->y >= PADDLE_Y
        && b->y <= PADDLE_Y + PADDLE_HEIGHT;
}

void tick (ball *b) {
    move (b);

    if (checkGridCollision (b)) onGridCollide (b);
    if (checkPaddleCollision (b)) onPaddleCollide (b);
}

/*
 *  TESTING
 */
int ballMain () {
    grid *g = newGrid (20, 10);
    paddle *p = newPaddle (g);
    ball *b = newBall (g, p);

    assert (getBallX (b) == 10);
    assert (getBallY (b) == 5);
    assert (getBallVelX (b) == 0);
    assert (getBallVelY (b) == -0.5f);
    tick (b);
    assert (getBallX (b) == 10);
    assert (getBallY (b) == 4.5f);
    assert (getBallVelX (b) == 0);
    assert (getBallVelY (b) == -0.5f);

    succeed ("Ball module OK");
    return 0;
}