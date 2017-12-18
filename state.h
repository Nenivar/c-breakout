#include "paddle.h"
#include "grid.h"
#include "ball.h"

struct state;
typedef struct state state;

state *newState (grid *g, paddle *p, ball *b);
void freeState ();

grid *getGrid (state *s);
paddle *getPaddle (state *s);
ball *getBall (state *s);