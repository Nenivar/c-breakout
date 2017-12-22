#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "ball.h"

/*
 *  STRUCTURES
 */
const int BALL_DIM = 1;

struct ball {
    float x, y,
        prevX, prevY,
        velX, velY,
        speed;
    grid *g;
    paddle *p;
};

/*
 *  ACCESS
 */

ball *newBall (grid *g, paddle *p) {
    srand (time (NULL));

    ball *b = malloc (sizeof (ball));
    b->x = (getGridWidth (g) * getTileWidth () - BALL_DIM) / 2;
    b->y = getGridHeight (g) / 2;
    b->speed = 0.6f;
    b->velX = ((rand () % 200) - 100) / 100.0f * b->speed;
    b->velY = b->speed;
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
    b->prevX = b->x;
    b->prevY = b->y;
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
    /*if (b->prevX < x || b->prevX > x + 1) {
        printf ("coll LR!\n");
        v = true;
        b->velX = -b->velX;
    }
    // bottom & top
    else if (b->prevY > y + 1 || b->prevY < y) {
        printf ("coll TB!\n");
        h = true;
        b->velY = -b->velY;
    }*/
    float nextX = b->x + b->velX, nextY = b->y + b->velY;
    if (getTileAtWorld (b->g, nextX, nextY) != WALL);// setTileAtWorld (b->g, AIR, nextX, nextY);
    // l & r
    if (b->x < x || b-x > x + 1) {
        printf ("coll LR!\n");
        b->velX = -b->velX;
    }
    // t & b
    else if (b->y < y || b->y > y + 1) {
        printf ("coll TB!\n");
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
    float paddleBallDx = halfway - (b->x - (BALL_DIM * 0.5f));
    float perc = (1.0f / (getPaddleWidth () / 2)) * paddleBallDx;

    float vX = -sin (perc) * getBallSpeed (b);
    float vY = -cos (perc) * getBallSpeed (b);
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
    //return getTileAtWorld (b->g, (int) b->x, (int) b->y) != AIR;

    int nextX = b->x + b->velX, nextY = b->y + b->velY;
    return (getTileAtWorld (b->g, nextX, nextY) != AIR);
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
    float left = b->x, right = b->x + BALL_DIM,
        top = b->y, bottom = b->y + BALL_DIM,
        nextLeft = left + b->velX, nextRight = right + b->velX,
        nextTop = top + b->velY, nextBottom = bottom + b->velY;
    float nextX = b->x + b->velX, nextY = b->y + b->velY;

    if (getTileAtWorld (b->g, nextX, b->y) != AIR) {
        b->velX *= -1;
        //if (getTileAtWorld (b->g, nextX, b->y) != WALL) setTileAtWorld (b->g, AIR, nextX, b->y);
        if (getTileAtWorld (b->g, nextX, b->y) != WALL) setTileAtWorld (b->g, AIR, (int) nextX, (int) b->y);
    }
    if (getTileAtWorld (b->g, b->x, nextY) != AIR) {
        b->velY *= -1;
        printf ("deleting %d %d\n", b->x, nextY);
        if (getTileAtWorld (b->g, b->x, nextY) != WALL) setTileAtWorld (b->g, AIR, (int) b->x, (int) nextY);
    }

    //if (isWithinGrid (b->g, b->x, nextTop) && getTileAtWorld (b->g, nextLeft, nextTop) != AIR) b->velX *= -1;
    //if (getTileAtWorld (b->g, nextRight , nextTop) != AIR) b->velX *= -1;
    //if (isWithinGridWorld (b->g, nextLeft, nextTop) && getTileAtWorld (b->g, nextLeft, nextTop) != AIR) b->velY *= -1;
    //if (isWithinGridWorld (b->g, nextLeft, nextBottom) && getTileAtWorld (b->g, nextLeft, nextBottom) != AIR) b->velY *= -1;


    /*if (checkGridCollision (b)) {
        printf ("wall collision; (%.2f,%.2f) & (%d,%d) | vX:%.2f, vY:%.2f\n", b->x, b->y, (int) b->x, (int) b->y, b->velX, b->velY);
        onGridCollide (b, b->x, b->y);
    }*/

    if (checkPaddleCollision (b)) onPaddleCollide (b);

    move (b);
}


/*
 *  TESTING
 */
int ballMain () {
    grid *g = newGrid (20, 10);
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