#include <stdio.h>
#include <stdlib.h>

#include "base.h"
/*
 *  UTIL
 */
// returns the bigger of two numbers
int max (int a, int b) {
    return a > b ? a : b;
}

/*
 *  ERROR HANDLING
 */
void succeed (char *message) {
    printf ("%s\n", message);
}

void fail (char *message) {
    fprintf (stderr, "%s\n", message);
    exit (1);
}

/*
 *  MAIN
 */
int baseMain () {
    succeed ("Base module OK");
    return 0;
}