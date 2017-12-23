#include "number.h"

extern const float PADDLE_WIDTH;
extern const float PADDLE_HEIGHT;
extern const float PADDLE_Y;

// paddle which user controls to hit the ball
// has a fixed position near the bottom of the grid
struct paddle;
typedef struct paddle paddle;

// creates a new paddle in the middle of the grid
paddle *newPaddle (grid *g);
// safely removes the paddle
void freePaddle ();

// moves the paddle by dx horizontally
void movePaddle (paddle *p, float dx);
// returns the x pos. of the paddle
float getPaddleX (paddle *p);
//returns the y pos. of the paddle
float getPaddleY (paddle *p);

// returns the width of the paddle
float getPaddleWidth ();
// returns the height of the paddle
float getPaddleHeight ();