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
const int LAYERS = 6;

/*
 *  STRUCTURES
 */
struct game {
    grid *g;
    paddle *p;
    ball *b;
    bool ballExists, won;
    int balls;
};
typedef struct game game;

/*
 *  INPUT
 */
// moves the paddle according to input
// and spawns a new ball if needed
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
// returns the (rgb) colour of a given tile
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

// draws each tile of a grid onto a display
// (apart from air)
void drawGrid (display *d, grid *g) {
    for (int y = 0; y < getGridHeight (g); y++) {
        for (int x = 0; x < getGridWidth (g); x++) {
            TILE t = getTileAt (g, x, y);

            if (t != AIR) {
                setDrawColour (d, getTileColour (t));
                drawBox (d, x * SCALE_X * getTileWidth (), y * SCALE_Y, SCALE_X * getTileWidth (), SCALE_Y);
            }
        }
    }
}

// draws the paddle onto a display
void drawPaddle (display *d, game *gm) {
    paddle *p = gm->p;
    setDrawColour (d, getTileColour (BRICK_RED));
    drawBox (d, getPaddleX (p) * SCALE_X, getPaddleY (p) * SCALE_Y,
        getPaddleWidth () * SCALE_X, getPaddleHeight () * SCALE_Y);
}

// draws the ball onto a display
void drawBall (display *d, game *gm) {
    ball *b = gm->b;
    setDrawColour (d, getTileColour (BRICK_RED));
    drawBox (d, getBallX (b) * SCALE_X, getBallY (b) * SCALE_Y,
        SCALE_X, SCALE_Y);
}

// draws all of the game's elements
void drawGame (game *gm, display *d) {
    drawGrid (d, gm->g);
    drawPaddle (d, gm);
    if (gm->ballExists) {
        drawBall (d, gm);
    }

    drawFrame (d);
}

/*
 *  MAIN
 */
// creates a new game with a grid (with breakable blocks), ball, and paddle
game *newGame () {
    game *gm = malloc (sizeof (game));

    gm->g = newGrid (GRID_W, GRID_H, LAYERS);
    gm->p = newPaddle (gm->g);
    gm->won = false;
    gm->ballExists = false;
    gm->balls = 0;

    return gm;
}

// updates the number in the top-left corner
// representing the number of balls used
void updateStats (game *gm) {
    placeNumberAt (gm->balls, gm->g, 0, 0);
}

// runs the game through one frame/cycle
// removes the ball if it goes below the paddle/grid
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

    if (getMaxBreakableBricks (gm->g) == getBricksBroken (gm->g))
        gm->won = true;
}

// prints a message in console for the user
// depending on whether they lost or won
void printEndMessage (game *gm) {
    if (gm->won) {
        printf ("You win, congratulations! It took you %d balls to break %d blocks.\n",
            gm->balls, getMaxBreakableBricks (gm->g));
    } else {
        printf ("You lose, sorry! It took you %d balls to break %d blocks.\n",
            gm->balls, getBricksBroken (gm->g));
    }
}

// safely deletes a game structure
void endGame (game *gm) {
    freeGrid (gm->g);
    freePaddle (gm->p);
    freeBall (gm->b);
}

// sets up a game
// starts the game loop
// safely stops the game when escape is pressed
int main (int n, char *args [n]) {    
    game *gm = newGame ();
    display *d = newDisplay (GRID_W * getTileWidth () * SCALE_X, GRID_H * SCALE_Y);

    bool keysDown [KEY_NO];
    for (int i = 0; i < KEY_NO; i++) keysDown [i] = false;
    while (!keysDown [ESCAPE] && !gm->won) {
        drawGame (gm, d);
        tickGame (gm);

        getKeysDown (d, keysDown);
        processInput (gm, keysDown);
    }

    printEndMessage (gm);    

    endGame (gm);
    freeDisplay (d);

    succeed ("Breakout module OK");

    return 0;
}