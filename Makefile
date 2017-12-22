.PHONY: base grid paddle ball number breakout
GCC = gcc -std=c99 -O3 -pedantic -Wall -o breakout

base:
		$(GCC) -DbaseMain=main base.c
		./breakout
grid:
		$(GCC) -DgridMain=main grid.c base.c
		./breakout
paddle:
		$(GCC) -DpaddleMain=main paddle.c grid.c base.c
		./breakout
ball:
		$(GCC) -DballMain=main ball.c paddle.c grid.c base.c -lm
		./breakout
number:
		$(GCC) -DnumberMain=main number.c ball.c paddle.c grid.c base.c -lm
		./breakout
display:
		$(GCC) -DdisplayMain=main display.c -lSDL2
		./breakout
breakout:
		$(GCC) breakout.c display.c number.c ball.c paddle.c grid.c base.c -lSDL2 -lm
		./breakout