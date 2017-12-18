#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

#include "grid.h"
#include "paddle.h"

/*
 *  STRUCTURES
 */
const int BALL_DIM = 1;

struct ball {
    uint8_t x, y,
            velX, velY;
};
typedef struct ball ball;

/*
 *  ACCESS
 */

ball *newBall () {
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

void move (ball *b, grid *g) {
    int x = b->x + b->velX;
    int y = b->y + b->velY;

    if (gridOobCheck (g, x, y)) {
        b->x = x; b->y = y;
    }
}

void onGridCollide (ball *b, grid *g) {
    b->x = -b->x;
    b->y = -b->y;
}

void onPaddleCollide (ball *b, paddle *p) {
    // algorithm
}

bool checkGridCollision (ball *b, grid *g) {
    return getTileAt (g, b->x, b->y) != AIR;
}

bool checkPaddleCollision (ball *b, paddle *p) {
    return b->x >= getPaddleX (p)
        && b->x <= getPaddleX (p) + PADDLE_WIDTH
        && b->y >= PADDLE_Y
        && b->y <= PADDLE_Y + PADDLE_HEIGHT;
}

void tick (ball *b, grid *g, paddle *p) {
    move (b, g);

    if (checkGridCollision (b, g)) onGridCollide (b, g);
    if (checkPaddleCollision (b, p)) onPaddleCollide (b, p);
}

/*
 *  TESTING
 */
void testBall () {
    ball *b = newBall ();
}