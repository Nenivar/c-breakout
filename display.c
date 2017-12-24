// https://csijh.gitlab.io/COMS10008/c/modules/display.c
// was used for a lot of reference code :)

#include <stdbool.h>
#include <stdint.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "display.h"

const int KEY_NO = 4;

/*
 *  STRUCTURES
 */
struct display {
    int width, height;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

struct col {
    int r;
    int g;
    int b;
};

/*
 *  ERROR HANDLING
 */

// prints an error, quits SDL, and exits the program
static void sdlFail () {
    fprintf (stderr, "%s\n", SDL_GetError ());
    SDL_Quit ();
    exit (1);
}

// fails if n is negative
int notNeg (int n) {
    if (n < 0) sdlFail ();
    return n;
}

// fails if p is void
void *notNull (void *p) {
    if (p == NULL) sdlFail ();
    return p;
}

/*
 *  COLOUR
 */
col *newColour (int r, int g, int b) {
    col *c = malloc (sizeof (col));
    c->r = r; c->g = g; c->b = b;
    return c;
}

/*
 *  INPUT
 */
void getKeysDown (display *d, bool *keysDown) {
    bool quit = false;

    SDL_Event event;
    while (!quit && notNeg (SDL_PollEvent (&event))) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_KEYDOWN) {
            int sym = event.key.keysym.sym;
            if (sym == SDLK_LEFT) keysDown [LEFT] = true;
            if (sym == SDLK_RIGHT) keysDown [RIGHT] = true;
            if (sym == SDLK_ESCAPE) keysDown [ESCAPE] = true;
            if (sym == SDLK_SPACE) keysDown [BALL] = true;
        } else if (event.type == SDL_KEYUP) {
            int sym = event.key.keysym.sym;
            if (sym == SDLK_LEFT) keysDown [LEFT] = false;
            if (sym == SDLK_RIGHT) keysDown [RIGHT] = false;
            if (sym == SDLK_ESCAPE) keysDown [ESCAPE] = false;
            if (sym == SDLK_SPACE) keysDown [BALL] = false;
        }
    }
}

/*
 *  DISPLAY
 */
display *newDisplay (int width, int height) {
    display *d = malloc (sizeof (display));
    d->width = width;
    d->height = height;
    notNeg (SDL_Init (SDL_INIT_VIDEO));
    d->window = notNull (SDL_CreateWindow ("Breakout", 100, 100, width, height, 0));
    d->renderer = notNull (SDL_CreateRenderer (d->window, -1, SDL_RENDERER_ACCELERATED));
    
    return d;
}

void freeDisplay (display *d) {
    SDL_DestroyWindow (d->window);
    SDL_Quit ();
    free (d);
}

void setDrawColour (display *d, col *c) {
    SDL_SetRenderDrawColor (d->renderer, c->r, c->g, c->b, 255);
    free (c);
}

void drawBox (display *d, int x, int y, int w, int h) {
    SDL_Rect b;
    b.x = x; b.y = y;
    b.w = w; b.h = h;

    SDL_RenderFillRect (d->renderer, &b);
}

void drawFrame (display *d) {
    SDL_RenderPresent (d->renderer);

    SDL_SetRenderDrawColor (d->renderer, 0, 0, 0, 255);
    SDL_RenderClear (d->renderer);

    SDL_Delay (20);
}

void pause (int ms) {
    SDL_Delay (ms);
}

/*
 *  TESTING
 */

int displayMain () {
    display *d = newDisplay (640, 480);
    drawBox (d, 10, 10, 45, 25);
    drawFrame (d);
    pause (5000);
    freeDisplay (d);

    return 0;
}