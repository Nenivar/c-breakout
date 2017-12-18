#include <stdlib.h>
#include <stdio.h>

#include "display.h"

void fail (char *message) {
    fprintf (stderr, "%s\n", message);
    exit (1);
}

int main (int n, char *args [n]) {
    display ();

    return 1;
}