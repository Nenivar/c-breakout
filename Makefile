.PHONY: base grid paddle ball breakout
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
		$(GCC) -DballMain=main ball.c paddle.c grid.c base.c
		./breakout
breakout:
		$(GCC) breakout.c ball.c paddle.c grid.c base.c
		./breakout