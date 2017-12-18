/*
 *  BREAKOUT
 */
#include <stdlib.h>
#include <stdio.h>

#include "display.h"
#include "grid.c"
#include "paddle.c"
#include "state.c"
#include "ball.c"

/*
 *  TESTING
 */
void test () {
    testGrid ();
    grid *g = newGrid (25, 20);
    testPaddle (g);
    testBall ();
}

/*
 *  MAIN
 */
void newGame () {
    grid *g = newGrid (25, 20);
    paddle *p = newPaddle (g);
    ball *b = newBall (g, p);
    state *s = newState (g, p, b);

    // tick game

    freeState (s);

    //display ();
}

int main (int n, char *args [n]) {    
    test ();
    newGame ();

    return 1;
}