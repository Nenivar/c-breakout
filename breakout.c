/*
 *  BREAKOUT
 */
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#include "display.h"
#include "ball.h"

const float SCALE_X = 15;
const float SCALE_Y = 10;

/*
 *  STRUCTURES
 */
struct game {
    grid *g;
    paddle *p;
    ball *b;
};
typedef struct game game;

/*
 *  DISPLAY
 */

col *getTileColour (TILE t) {
    switch (t) {
        case WALL:
            return newColour (142, 142, 142);
        case BRICK_BLU:
            return newColour (66, 72, 200);
        case BRICK_GRN:
            return newColour (72, 160, 72);
        case BRICK_YLW:
            return newColour (162, 162, 42);
        case BRICK_BRN:
            return newColour (180, 122, 48);
        case BRICK_ORG:
            return newColour (198, 108, 58);
        case BRICK_RED:
            return newColour (200, 72, 72);
        default:
        return newColour (255, 255, 255);
    }
}

void drawGrid (display *d, grid *g) {
    for (int y = 0; y < getGridHeight (g); y++) {
        for (int x = 0; x < getGridWidth (g); x++) {
            TILE t = getTileAt (g, x, y);

            if (t != AIR) {
                setDrawColour (d, getTileColour (t));
                drawBox (d, x * SCALE_X, y * SCALE_Y, SCALE_X, SCALE_Y);
            }
        }
    }
}

void drawPaddle (display *d, paddle *p) {

}

void drawBall (display *d, ball *b) {

}

void drawGame (game *gm, display *d) {
    drawGrid (d, gm->g);
    drawPaddle (d, gm->p);
    drawBall (d, gm->b);
}

/*
 *  MAIN
 */
game *newGame () {
    game *gm = malloc (sizeof (game));

    gm->g = newGrid (15, 20);
    gm->p = newPaddle (gm->g);
    gm->b = newBall (gm->g, gm->p);

    return gm;
}

void tickGame (game *gm) {

}

void endGame (game *gm) {
    freeGrid (gm->g);
    freePaddle (gm->p);
    freeBall (gm->b);
}

int main (int n, char *args [n]) {    
    game *gm = newGame ();
    display *d = newDisplay (250, 250);

    tickGame (gm);
    drawGame (gm, d);
    drawFrame (d);

    pause (3000);

    freeDisplay (d);
    endGame (gm);

    succeed ("Breakout module OK");

    return 0;
}