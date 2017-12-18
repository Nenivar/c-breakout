/*
 *  BREAKOUT
 */
#include <stdlib.h>
#include <stdio.h>

#include "display.h"
//#include "grid.h"
#include "grid.c"
#include "paddle.c"
#include "state.c"

/*
 *  ERROR HANDLING
 */
void fail (char *message) {
    fprintf (stderr, "%s\n", message);
    exit (1);
}

/*
 *  TESTING
 */
void test () {
    testGrid ();
    grid *g = newGrid (25, 20);
    testPaddle (g);
}

/*
 *  MAIN
 */
int main (int n, char *args [n]) {
    
    grid *g = newGrid (25, 20);
    state *s = newState (g);

    freeState (s);

    test ();
    //display ();

    return 1;
}