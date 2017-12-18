#include "display.h"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;

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

void display () {
    notNeg (SDL_Init (SDL_INIT_VIDEO));

    SDL_Window *window = notNull (SDL_CreateWindow ("Breakout", 
                                    100, 100, WIDTH, HEIGHT, 0));

    SDL_Surface *surface = notNull (SDL_GetWindowSurface (window));
    Uint32 skyBlue = SDL_MapRGB (surface->format, 100, 149, 237);
    notNeg (SDL_FillRect (surface, NULL, skyBlue));
    notNeg (SDL_UpdateWindowSurface (window));
    SDL_Delay (10000);

    SDL_Quit ();
}