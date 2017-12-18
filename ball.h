struct ball;
typedef struct ball ball;

ball *newBall (grid *g, paddle *p);

uint8_t getBallX (ball *b);
uint8_t getBallY (ball *b);

uint8_t getBallVelX (ball *b);
uint8_t getBallVelY (ball *b);

void tick ();