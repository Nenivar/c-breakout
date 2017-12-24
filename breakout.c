/*
 *  BREAKOUT
 */
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "display.h"
#include "ball.h"

const float SCALE_X = 10;
const float SCALE_Y = 10;
const int GRID_W = 10;
const int GRID_H = 35;

/*
 *  STRUCTURES
 */
struct game {
    grid *g;
    paddle *p;
    ball *b;
    bool ballExists;
    int score, balls;
};
typedef struct game game;

/*
 *  INPUT
 */
void processInput (game *gm, bool *keysDown) {
    paddle *p = gm->p;
    if (keysDown [LEFT]) movePaddle (p, -0.8f);
    if (keysDown [RIGHT]) movePaddle (p, 0.8f);

    if (keysDown [BALL] && !gm->ballExists) {
        gm->b = newBall (gm->g, gm->p);
        gm->ballExists = true;
        gm->balls += 1;
    }
}

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

void drawGrid (display *d, grid *g, int offsetY) {
    //grid *g = gm->g;
    for (int y = 0; y < getGridHeight (g); y++) {
        for (int x = 0; x < getGridWidth (g); x++) {
            TILE t = getTileAt (g, x, y);

            if (t != AIR) {
                setDrawColour (d, getTileColour (t));
                drawBox (d, x * SCALE_X * getTileWidth (), y * SCALE_Y + offsetY, SCALE_X * getTileWidth (), SCALE_Y);
            }
        }
    }
}

void drawPaddle (display *d, game *gm) {
    paddle *p = gm->p;
    setDrawColour (d, getTileColour (BRICK_RED));
    drawBox (d, getPaddleX (p) * SCALE_X, getPaddleY (p) * SCALE_Y,
        getPaddleWidth () * SCALE_X, getPaddleHeight () * SCALE_Y);
}

void drawBall (display *d, game *gm) {
    ball *b = gm->b;
    setDrawColour (d, getTileColour (BRICK_RED));
    drawBox (d, getBallX (b) * SCALE_X, getBallY (b) * SCALE_Y,
        SCALE_X, SCALE_Y);
}

void drawGame (game *gm, display *d) {
    drawGrid (d, gm->g, 7);
    drawPaddle (d, gm);
    if (gm->ballExists) {
        drawBall (d, gm);
    }

    drawFrame (d);
}

/*
 *  MAIN
 */
game *newGame () {
    game *gm = malloc (sizeof (game));

    gm->g = newGrid (GRID_W, GRID_H, 6);
    gm->p = newPaddle (gm->g);
    gm->ballExists = false;
    gm->score = 0;
    gm->balls = 0;

    return gm;
}

void updateStats (game *gm) {
    placeNumberAt (gm->balls, gm->g, 0, 0);
}

void tickGame (game *gm) {
    if (gm->ballExists) {
        ball *b = gm->b;
        tickBall (b);
        if (getBallY (b) > getGridHeight (gm->g) + 1) {
            freeBall (b);
            gm->ballExists = false;
        }
    }

    updateStats (gm);
}

void endGame (game *gm) {
    freeGrid (gm->g);
    freePaddle (gm->p);
    freeBall (gm->b);
}

int main (int n, char *args [n]) {    
    game *gm = newGame ();
    display *d = newDisplay (GRID_W * getTileWidth () * SCALE_X, GRID_H * SCALE_Y);

    bool keysDown [KEY_NO];
    for (int i = 0; i < KEY_NO; i++) keysDown [i] = false;
    while (keysDown [ESCAPE]) {
        drawGame (gm, d);
        tickGame (gm);

        getKeysDown (d, keysDown);
        processInput (gm, keysDown);
    }

    //freeDisplay (d);
    //endGame (gm);

    succeed ("Breakout module OK");

    return 0;
}