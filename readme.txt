------------
- BREAKOUT -
------------
This is a recreation of the arcade game breakout.

The finished program is late, sorry. There's an earlier version I sent before the deadline if you want to mark that instead (completing this was satisfying anyway).

Hierarchy:
(Base -> Grid -> Number -> Paddle -> Ball) & Display -> Breakout
Each module has its own test/main function. The comments for most methods are in the header files, as not to repeat any.

Base:
This contains a success and failure function, much like yours in the wanderer game example. At one point I also used it for some shared utility functions, which became unneeded and removed.

Grid:
Contains a tilemap structure (with a 2D array) and methods to modify it.

Number:
2D arrays for each digit are stored and used to display numbers on a grid. I could have used a truetype font instead but this method is a bit easier.

Paddle:

Ball:

Display:

Breakout: