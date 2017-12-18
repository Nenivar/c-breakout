#include <stdint.h>

struct paddle;
typedef struct paddle paddle;

paddle *newPaddle (grid *g);
void freePaddle ();

void movePaddle (paddle *p, uint8_t dx);
uint8_t getPaddleX (paddle *p);

void testPaddle (grid *g);