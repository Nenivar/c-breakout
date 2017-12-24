------------
- BREAKOUT -
------------
This is a simple recreation of the arcade game breakout, where you need to break blocks using a paddle and ball.
Controls: left-key: move paddle left; right-key: move paddle right; space: spawn new ball (if required); escape: exit game.
The number in the top-left is the number of balls used; the game exits after all bricks have been destroyed.

The finished program is late, sorry. There's an earlier version I sent before the deadline if you want to mark that instead (completing this was satisfying anyway).

----------------
MODULE HIERARCHY:
(Base -> Grid -> Number -> Paddle -> Ball) & Display -> Breakout
Each module has its own test/main function. The comments for most methods are in the header files, as not to repeat anything.

----------------
BASE:
This contains a success and failure function, much like yours in the wanderer game example. At one point I also used it for some shared utility functions, which became unneeded and removed.

GRID:
Contains a tilemap structure (with a 2D array) and methods to modify it.

NUMBER:
2D arrays for each digit are stored and used to display numbers on a grid. I could have used a truetype font instead but this method is a bit easier.

PADDLE:
Structure for the paddle, which can only move between certain bounds in the horizontal direction.

BALL:
Structure for the ball. Contains the logic checking collisions between the grid/paddle, which aren't perfect but are acceptable.

DISPLAY:
Structure for the display (also a simple colour structure) using SDL2. Has functions to draw boxes (with differing colours) onto the display and then render them. Has a function to check for input on particular keys.

BREAKOUT:
Brings together the logic and display for the game inside a loop. The game is drawn (display cleared and drawn to each frame - could be more efficient in only clearing when needed); 'ticked' (movement of ball/win condition checked); and input processed. The width/height of the grid and layers of breakable blocks can be adjusted here.