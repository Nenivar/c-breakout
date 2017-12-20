#include <assert.h>
#include <malloc.h>
#include <math.h>
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
    b->velY = 0.2f;
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
static bool checkIntersection (float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2) {
        /*return !(x1 < (x2 + w2) && (x1 + w1) > x2
                && y1 > (y2 + h2) && (y1 + h1) < y2);*/
        
        bool xO = (x1 >= x2 && x1 <= x2 + w2)
            || (x2 >= x1 && x2 <= x1 + w1);
        bool yO = (y1 >= y2 && y1 <= y2 + h2)
            || (y2 >= y1 && y2 <= y1 + h1);
        return xO && yO;
    }

static void move (ball *b) {
    float x = b->x + b->velX;
    //if (x < 0) x = 0;
    //if (x > getGridWidth (b->g)) x = getGridWidth (b->g);

    //x = x > 0 ? x : 0;
    //x = x < getGridWidth (b->g) ? x : getGridWidth (b->g);
    /*x = x < 0 ? 0 : x;
    x = x > getGridWidth (b->g) ? getGridWidth (b->g) : x;*/

    float y = b->y + b->velY;
    //if (y < 0) y = 0;
    //if (y > getGridHeight (b->g)) y = getGridHeight (b->g);

    //y = y > 0 ? y : 0;
    //y = y < getGridHeight (b->g) ? y : getGridHeight (b->g);
    /*y = y < 0 ? 0 : y;
    y = y > getGridHeight (b->g) ? getGridHeight (b->g) : y;*/

    //gridOobCheck (b->g, x, y);
    b->x = x; b->y = y;
}

static void reflectVec (float x, float y, float nX, float nY) {
    float dot = x * nX - y * nY;
    float rX = x + 2 * nX * dot;
    float rY = y + 2 * nY * dot;
}

static void onGridCollide (ball *b, int x, int y) {
    // reflect x
    /*if (b->x <= 0 || b->x >= getGridWidth (b->g))
        b->velX = -b->velX;
    // reflect y
    if (b->y <= 0)
        b->velY = -b->velY;*/

    
    // below
    //if (b->y <= y - 0.5f || b->y >= y + 0.5f) b->velY = -b->velY;
    //if (b->x < x || b->x > x) b->velX = -b->velX;

    //if (b->y + 1 < y || b->y > y + 1) b->velY = -b->velY;
    float prevX = b->x - b->velX, prevY = b->y - b->velY;
    
    if (getTileAtWorld (b->g, x, y) != WALL) setTileAtWorld (b->g, AIR, x, y);
    
    /*if (perfY > y) {
        //b->y = y + 1;
        b->velY = -b->velY;
    } else if (perfX + 1 < x) {
        //b->x = x + 1;
        b->velX = -b->velX;
    } else if (perfY + 1 < y) {
        b->velY = -b->velY;
    }*/
    bool v = false, h = false;
    // left & right
    if (prevX < x || prevX > x + 1) {
        printf ("coll LR!\n");
        v = true;
        b->velX = -b->velX;
    }
    // bottom & top
    if (prevY > y + 1 || prevY < y) {
        printf ("coll TB!\n");
        h = true;
        b->velY = -b->velY;
    }

    // reflection
    /*float nX = h ? 1 : 0, nY = v ? 1 : 0;
    float dot = b->velX * nX - b->velY * nY;
    float rX = b->velX + 2 * nX * dot * 0.2;
    float rY = b->velY + 2 * nY * dot * 0.2;
    b->velX = rX;
    b->velY = rY;*/
}

static void onPaddleCollide (ball *b) {
    float halfway = getPaddleX (b->p) + getPaddleWidth () / 2;
    // left = pos; right = neg
    float paddleBallDx = halfway - b->x;
    float perc = (1.0f / (getPaddleWidth () / 2)) * paddleBallDx;

    float vX = -sin (perc) * 0.2;
    float vY = -cos (perc) * 0.2;
    printf ("collision; dx=%.2f, perc=%.2f, vX=%.2f, vY=%.2f\n",
        paddleBallDx, perc, vX, vY);

    b->velX = vX;
    b->velY = vY;
}

static bool checkGridCollision (ball *b) {
    /*return checkIntersection (b->x, b->y, 1, 1,
                                b->x, b->y, BALL_DIM, BALL_DIM);*/
    //return getTileAt (b->g, (int) b->x / getTileWidth (), (int) b->y) != AIR;
        /*|| getTileAt (b->g, (int) b->x / getTileWidth () + 1, (int) b->y) != AIR
        || getTileAt (b->g, (int) b->x / getTileWidth (), (int) b->y + 1) != AIR
        || getTileAt (b->g, (int) b->x / getTileWidth () + 1, (int) b->y + 1) != AIR;*/
    return getTileAtWorld (b->g, (int) b->x, (int) b->y) != AIR;
}

static bool checkPaddleCollision (ball *b) {
    return checkIntersection (getPaddleX (b->p), getPaddleY (b->p),
                            getPaddleWidth (b->p), getPaddleHeight (b->p),
                            b->x, b->y,
                            BALL_DIM, BALL_DIM);
    /*return b->x >= getPaddleX (b->p)
        && b->x <= getPaddleX (b->p) + getPaddleWidth ()
        && b->y >= getPaddleY (b->p)
        && b->y <= getPaddleY (b->p) + getPaddleHeight ();*/
}

void tickBall (ball *b) {
    move (b);
    if (checkGridCollision (b)) {
        printf ("wall collision; (%.2f,%.2f) & (%d,%d) | vX:%.2f, vY:%.2f\n", b->x, b->y, (int) b->x, (int) b->y, b->velX, b->velY);

        onGridCollide (b, b->x, b->y);
    }
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
    tickBall (b);
    assert (getBallX (b) == 10);
    assert (getBallY (b) == 4.5f);
    assert (getBallVelX (b) == 0);
    assert (getBallVelY (b) == -0.5f);

    succeed ("Ball module OK");
    return 0;
}