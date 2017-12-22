// https://csijh.gitlab.io/COMS10008/c/modules/display.c
// was used for a lot of reference code :)

#include <stdbool.h>
#include <stdint.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "display.h"

const int WIDTH = 640;
const int HEIGHT = 480;

const int KEY_NO = 3;

/*
 *  STRUCTURES
 */
struct display {
    int width, height;
    SDL_Window *window;
    //SDL_Surface *surface;
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
    /*SDL_Event eventStructure;
    SDL_Event *event = &eventStructure;

    while (true) {
        notNeg (SDL_PollEvent (event));
        if (event->type == SDL_QUIT) {
            SDL_Quit ();
            exit (0);
        } else if (event->type == SDL_KEYUP) {
            int sym = event->key.keysym.sym;
            if (sym == SDLK_LEFT) return LEFT;
            if (sym == SDLK_RIGHT) return RIGHT;
            if (sym == SDLK_ESCAPE) return ESCAPE;
        }
    }*/
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
        } else if (event.type == SDL_KEYUP) {
            int sym = event.key.keysym.sym;
            if (sym == SDLK_LEFT) keysDown [LEFT] = false;
            if (sym == SDLK_RIGHT) keysDown [RIGHT] = false;
            if (sym == SDLK_ESCAPE) keysDown [ESCAPE] = false;
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
    d->window = notNull (SDL_CreateWindow ("Breakout", 100, 100, d->width, d->height, 0));
    d->renderer = notNull (SDL_CreateRenderer (d->window, -1, SDL_RENDERER_ACCELERATED));
    //d->surface = notNull (SDL_GetWindowSurface (d->window));
    //SDL_SetRenderDrawColor (d->renderer, 255, 255, 255, 255);
    //SDL_RenderClear (d->renderer);
    //SDL_RenderPresent (d->renderer);
    
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
    //SDL_Rect box = {0, 0, 0, 0} // x, y, width, height
    //SDL_FillRect (d->surface, );
    
    //SDL_RenderDrawRect ()

    SDL_Rect b;
    b.x = x; b.y = y;
    b.w = w; b.h = h;

    SDL_RenderFillRect (d->renderer, &b);
}

void drawFrame (display *d) {
    //notNeg (SDL_UpdateWindowSurface (d->window));
    SDL_RenderPresent (d->renderer);

    SDL_SetRenderDrawColor (d->renderer, 0, 0, 0, 255);
    SDL_RenderClear (d->renderer);

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
    drawBox (d, 10, 10, 45, 25);
    drawFrame (d);
    pause (5000);
    freeDisplay (d);

    return 0;
}