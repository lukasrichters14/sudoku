#ifndef SUDOKU_H
#define SUDOKU_H

#define BOARD_SIZE 81
#define X_START 2
#define Y_START 1
#define X_END 34
#define Y_END 17
#define FIXED_NUM 1
#define BOARDER 2

void draw(int* board, char* given, int y, int x);
void addstr_color(int y, int x, char* s, int color);
int  scr_to_indx(int y, int x);
void init_board(int* board, char* given);

#endif
