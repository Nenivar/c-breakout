#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "ball.h"

/*
 *  STRUCTURES
 */
const int BALL_DIM = 1;

struct ball {
    float x, y,
        velX, velY,
        speed;
    grid *g;
    paddle *p;
};

/*
 *  ACCESS
 */
ball *newBall (grid *g, paddle *p) {
    ball *b = malloc (sizeof (ball));
    b->x = (getGridWidth (g) * getTileWidth () - BALL_DIM) / 2;
    b->y = getLayers (g) + TOP_SPACE + 4;
    b->speed = 0.6f;

    srand (time (NULL));
    float perc = ((rand () % 200) - 100) / 100.0f;
    b->velX = sin (perc) * b->speed;
    b->velY = cos (perc) * b->speed;

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

float getBallSpeed (ball *b) {
    return b->speed;
}

/*
 *  MOVEMENT
 */
// checks whether two rectangles intersect
static bool checkIntersection (float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2) {
        bool xO = (x1 >= x2 && x1 <= x2 + w2)
            || (x2 >= x1 && x2 <= x1 + w1);
        bool yO = (y1 >= y2 && y1 <= y2 + h2)
            || (y2 >= y1 && y2 <= y1 + h1);
        return xO && yO;
    }

// moves the ball according to its velocity
static void move (ball *b) {
    b->x += b->velX;
    b->y += b->velY;
}

// checks whether a ball is going to collide with a paddle
static bool checkPaddleCollision (ball *b) {
    return checkIntersection (getPaddleX (b->p), getPaddleY (b->p),
                            getPaddleWidth (b->p), getPaddleHeight (b->p),
                            b->x, b->y,
                            BALL_DIM, BALL_DIM);
}

// reflects the ball (changes velocity)
// based on the distance from the center of the paddle
// (further away = higher angle)
static void onPaddleCollide (ball *b) {
    float halfway = getPaddleX (b->p) + getPaddleWidth () / 2;
    float paddleBallDx = halfway - (b->x - (BALL_DIM * 0.5f));
    float perc = (1.0f / (getPaddleWidth () / 2)) * paddleBallDx;

    b->velX = -sin (perc) * getBallSpeed (b);
    b->velY = -cos (perc) * getBallSpeed (b);
}

// checks whether a ball is going to collide with the side of a (non-air) tile
static bool checkGridXCollision (ball *b) {
    float nextX = b->x + b->velX;
    return getTileAtWorld (b->g, nextX, b->y) != AIR;
}

// reflects the ball in the x direction
// and removes the hit tile if not a wall
static void onGridXCollide (ball *b) {
    float nextX = b->x + b->velX;
    b->velX *= -1;
    if (getTileAtWorld (b->g, nextX, b->y) != WALL) {
        setTileAtWorld (b->g, AIR, (int) nextX, (int) b->y);
        increaseBricksBroken (b->g);
    }
}

// checks whether a ball is going to collide with the top/bottom of a (non-air) tile
static bool checkGridYCollision (ball *b) {
    float nextY = b->y + b->velY;
    return getTileAtWorld (b->g, b->x, nextY) != AIR;
}

// reflects the ball in the y direction
// and removes the hit tile if not a wall
static void onGridYCollide (ball *b) {
    float nextY = b->y + b->velY;
    b->velY *= -1;
    if (getTileAtWorld (b->g, b->x, nextY) != WALL) {
        setTileAtWorld (b->g, AIR, (int) b->x, (int) nextY);
        increaseBricksBroken (b->g);
    }
}

// checks for collisions with the grid & paddle
// acts accordingly & moves the ball
void tickBall (ball *b) {
    float nextY = b->y + b->velY;
    if (nextY <= getGridHeight (b->g)) {
        if (checkGridXCollision (b)) {
            onGridXCollide (b);
        } else if (checkGridYCollision (b)) {
            onGridYCollide (b);
        }
    }

    if (checkPaddleCollision (b)) onPaddleCollide (b);

    move (b);
}

/*
 *  TESTING
 */
int ballMain () {
    grid *g = newGrid (20, 15, 0);
    paddle *p = newPaddle (g);
    ball *b = newBall (g, p);
    float startX = getBallX (b), startY = getBallY (b);
    float velX = getBallVelX (b), velY = getBallVelY (b);

    assert (getBallX (b) == startX);
    assert (getBallY (b) == startY);
    assert (getBallVelX (b) == velX);
    assert (getBallVelY (b) == velY);
    tickBall (b);
    assert (getBallX (b) == startX + velX);
    assert (getBallY (b) == startY + velY);
    assert (getBallVelX (b) == velX);
    assert (getBallVelY (b) == velY);

    succeed ("Ball module OK");
    return 0;
}