CC=gcc
CFLAGS=-lncurses -Wall -g

sudoku: sudoku.c
	$(CC) -o sudoku sudoku.c $(CFLAGS)

