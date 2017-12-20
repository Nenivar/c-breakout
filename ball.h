#include <stdint.h>

#include "paddle.h"

// ball structure with movement variables
struct ball;
typedef struct ball ball;

// creates a new ball in the center of the grid
ball *newBall (grid *g, paddle *p);
// safely removes a ball
void freeBall (ball *b);

// returns the x pos. of the ball
float getBallX (ball *b);
// returns the y pos. of the ball
float getBallY (ball *b);

// returns the horiz. vel of the ball
float getBallVelX (ball *b);
// returns the vert. vel. of the ball
float getBallVelY (ball *b);

// changes the pos. of the ball
// according to it's velocity & collisions
void tickBall (ball *b);