#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

#include "grid.h"
#include "paddle.h"

#include "ball.h"

/*
 *  STRUCTURES
 */
const int BALL_DIM = 1;

struct ball {
    uint8_t x, y,
            velX, velY;
    grid *g;
    paddle *p;
};
typedef struct ball ball;

/*
 *  ACCESS
 */

ball *newBall (grid *g, paddle *p) {
    ball *b = malloc (sizeof (ball));
    b->x = 0;
    b->y = 0;
    b->velX = 0;
    b->velY = 0;

    return b;
}

uint8_t getBallX (ball *b) {
    return b->x;
}

uint8_t getBallY (ball *b) {
    return b->y;
}

uint8_t getBallVelX (ball *b) {
    return b->velX;
}

uint8_t getBallVelY (ball *b) {
    return b->velY;
}

/*
 *  MOVEMENT
 */

static void move (ball *b) {
    int x = b->x + b->velX;
    int y = b->y + b->velY;

    if (gridOobCheck (b->g, x, y)) {
        b->x = x; b->y = y;
    }
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

void tick (ball *b, grid *g, paddle *p) {
    move (b);

    if (checkGridCollision (b)) onGridCollide (b);
    if (checkPaddleCollision (b)) onPaddleCollide (b);
    if (b->y < 0);
}

/*
 *  TESTING
 */
void testBall () {
    
}