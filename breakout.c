#include <stdlib.h>
#include <stdio.h>

#include "display.h"
//#include "grid.h"
#include "grid.c"

void fail (char *message) {
    fprintf (stderr, "%s\n", message);
    exit (1);
}

void test () {
    testGrid ();
}

int main (int n, char *args [n]) {
    //display ();
    test ();

    return 1;
}