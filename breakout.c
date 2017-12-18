/*
 *  BREAKOUT
 */
#include <stdlib.h>
#include <stdio.h>

#include "display.h"
//#include "grid.h"
#include "grid.c"
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
}

/*
 *  MAIN
 */
int main (int n, char *args [n]) {
    //display ();
    test ();

    return 1;
}