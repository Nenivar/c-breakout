enum key {
    LEFT='<', RIGHT='>', ESCAPE='X'
};
typedef enum key key;

struct display;
typedef struct display display;

struct col;
typedef struct col col;

display *newDisplay (int width, int height);
void freeDisplay (display *d);

void setDrawColour (display *d, col *c);
col *newColour (int r, int g, int b);

void drawFrame (display *d);
void drawBox (display *d, int x, int y, int w, int h);

key getKey (display *d);
void pause (int ms);