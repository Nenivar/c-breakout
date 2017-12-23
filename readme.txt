------------
- BREAKOUT -
------------
This is a recreation of the arcade game breakout.
It isn't fully finished, sorry. There is some structure for the logic of the game, but not much for the display.
It got quite complex with so many modules.

The finished program is a bit late, sorry. There's an earlier version I sent before the deadline if you want to mark that instead (completing this was satisfying anyway).

Hierarchy:
Base -> Grid -> Number -> Paddle -> Ball -> Breakout -> Display
Each module has its own test/main function. The comments for most methods are in the header files, as not to repeat any.

Base:
This contains a success and failure function, much like yours in the wanderer game example. At one point I also used it for some shared utility functions, which became unneeded and removed.

Number:
I could have used a truetype font for 