.PHONY: base grid
GCC = gcc -std=c99 -O3 -pedantic -Wall -o breakout

base:
		$(GCC) -DbaseMain=main base.c
		./breakout
grid:
		$(GCC) -DgridMain=main grid.c base.c
		./breakout