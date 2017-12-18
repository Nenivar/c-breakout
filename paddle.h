#include <stdint.h>

struct paddle;
typedef struct paddle paddle;

paddle *newPaddle (grid *g);
void freePaddle ();

void movePaddle (paddle *p, float dx);
float getPaddleX (paddle *p);

void testPaddle (grid *g);