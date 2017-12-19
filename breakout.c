/*
 *  BREAKOUT
 */
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#include "display.h"
#include "ball.h"

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

/*
 *  MAIN
 */
game *newGame () {
    game *gm = malloc (sizeof (game));

    gm->g = newGrid (25, 20);
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
    tickGame (gm);
    endGame (gm);

    succeed ("Breakout module OK");

    return 0;
}