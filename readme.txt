------------
- BREAKOUT -
------------
This is a recreation of the arcade game breakout.
The finished program is late, sorry. There's an earlier version I sent before the deadline if you want to mark that instead (completing this was satisfying anyway).

Hierarchy:
(Base -> Grid -> Number -> Paddle -> Ball) & Display -> Breakout
Each module has its own test/main function. The comments for most methods are in the header files, as not to repeat anything.

Base:
This contains a success and failure function, much like yours in the wanderer game example. At one point I also used it for some shared utility functions, which became unneeded and removed.

Grid:
Contains a tilemap structure (with a 2D array) and methods to modify it.

Number:
2D arrays for each digit are stored and used to display numbers on a grid. I could have used a truetype font instead but this method is a bit easier.

Paddle:
Structure for the paddle, which can only move between certain bounds in the horizontal direction.

Ball:
Structure for the ball. Contains the logic checking collisions between the grid/paddle, which aren't perfect but are acceptable.

Display:
Structure for the display (also a simple colour structure) using SDL2. Has functions to draw boxes (with differing colours) onto the display and then render them. Has a function to check for input on particular keys.

Breakout:
