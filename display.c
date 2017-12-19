// https://csijh.gitlab.io/COMS10008/c/modules/display.c
// was used for a lot of reference code :)

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "display.h"

const int WIDTH = 640;
const int HEIGHT = 480;

/*
 *  STRUCTURES
 */
struct display {
    int width, height;
    SDL_Window *window;
    SDL_Surface *surface;
};

/*
 *  ERROR HANDLING
 */

void sdlFail () {
    fprintf (stderr, "%s\n", SDL_GetError ());
    SDL_Quit ();
    exit (1);
}

int notNeg (int n) {
    if (n < 0) sdlFail ();
    return n;
}

void *notNull (void *p) {
    if (p == NULL) sdlFail ();
    return p;
}

/*
 *  DISPLAY
 */

display *newDisplay (int width, int height) {
    display *d = malloc (sizeof (display));
    d->width = width;
    d->height = height;
    notNeg (SDL_Init (SDL_INIT_VIDEO));
    d->window = notNull (SDL_CreateWindow ("Breakout", 100, 100, d->width, d->height, 0));
    d->surface = notNull (SDL_GetWindowSurface (d->window));
    
    return d;
}

void drawFrame (display *d) {
    notNeg (SDL_UpdateWindowSurface (d->window));
    SDL_Delay (20);
}

/*void display () {
    notNeg (SDL_Init (SDL_INIT_VIDEO));

    SDL_Window *window = notNull (SDL_CreateWindow ("Breakout", 
                                    100, 100, WIDTH, HEIGHT, 0));

    SDL_Surface *surface = notNull (SDL_GetWindowSurface (window));
    Uint32 skyBlue = SDL_MapRGB (surface->format, 100, 149, 237);
    notNeg (SDL_FillRect (surface, NULL, skyBlue));
    notNeg (SDL_UpdateWindowSurface (window));
    SDL_Delay (10000);

    SDL_Quit ();
}*/

void pause (int ms) {
    SDL_Delay (ms);
}

/*
 *  TESTING
 */

int displayMain () {
    display *d = newDisplay (WIDTH, HEIGHT);
    drawFrame (d);
    pause (10000);

    return 0;
}