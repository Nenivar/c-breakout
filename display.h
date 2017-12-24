// potential keys which can be used
enum KEY {
    LEFT, RIGHT, BALL, ESCAPE
};
typedef enum KEY KEY;
// the number of keys which can be used
extern const int KEY_NO;

// structure for a window & renderer
struct display;
typedef struct display display;

// simple structure to represent an colour
struct col;
typedef struct col col;

// creates a new display with the specified width and height
display *newDisplay (int width, int height);
// safely removes a display
void freeDisplay (display *d);

// creates a new colour structure
col *newColour (int r, int g, int b);

// returns an array of keys which are down
// where the index corresponds to the key enum
void getKeysDown (display *d, bool *keysDown);
// pauses the display from being rendered for ms time
void pause (int ms);

// sets the colour of the next box to be drawn on a given display
void setDrawColour (display *d, col *c);
// draws one frame on the display (reflects changes)
void drawFrame (display *d);
// draws a box on the display with position (x,y) and dimensions (w,h)
void drawBox (display *d, int x, int y, int w, int h);