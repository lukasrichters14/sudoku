#include "sudoku.h"
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>


int scr_to_idx(int y, int x)
{
    return 9 * ((y - 1) / 2) + ((x - 2) / 4);
}


void addstr_color(int y, int x, char* str, int color)
{
    attron(COLOR_PAIR(color));
    mvaddstr(y, x, str);
    attroff(COLOR_PAIR(color));
}


void draw(int* board, char* given, int y, int x)
{
    int idx = 0;

    addstr_color(y, x, "+---+---+---+---+---+---+---+---+---+", BOARDER);
    y++;

    for (int row = 0; row < 9; row++)
    {
        addstr_color(y, x, "|", BOARDER);
        x++;

        for (int col = 0; col < 9; col++)
        {
            idx = 9 * row + col;
            
            if (board[idx] == 0)
            {
                mvaddstr(y, x, "  ");
            }
            else if (given[idx] != '.')
            {
                attron(COLOR_PAIR(FIXED_NUM));
                mvprintw(y, x, " %d ", board[idx]);
                attroff(COLOR_PAIR(FIXED_NUM));
            }
            else
            {
                mvprintw(y, x, " %d ", board[idx]);
            }


            x += 3;

            if ((col + 1) % 3 == 0) 
            { 
                addstr_color(y, x, "|", BOARDER); 
            }
            else 
            { 
                mvaddstr(y, x, "|"); 
            }    
            
            x++;
        }
        x = 0;
        y++;
        
        addstr_color(y, x, "+", BOARDER);        
        x++;

        if ((row + 1) % 3 == 0) { 
            addstr_color(y, x, "---+---+---+---+---+---+---+---+---+", BOARDER);
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                mvaddstr(y, x, "---+---+---");
                x += 11;
                addstr_color(y, x, "+", BOARDER);
                x++;
            }
        }
        
        y++;
        x = 0;
    }
}


void init_board(int* board, char* given)
{
    FILE* puzzles;
    char c;

    puzzles = fopen("puzzles.txt", "r");
    fgets(given, BOARD_SIZE + 1, (FILE*) puzzles);
    
    /*
    char buf[BOARD_SIZE + 1] =
        ".6..9.5..7.4.3...15.16.73....7..4.12...279...24.3..6....37.69.88...1.7.6..2.5..4.";  
    */
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            c = given[9 * row + col];
            if (c == '.')
            {
                board[9 * row + col] = 0;
            } 
            else 
            {
                board[9 * row + col] = c - '0';
            }
        }

    }

    fclose(puzzles);
}



int main()
{
    initscr();
    noecho();
    start_color();

    init_pair(FIXED_NUM, COLOR_CYAN, COLOR_BLACK);
    init_pair(BOARDER, COLOR_MAGENTA, COLOR_BLACK);

    int board[BOARD_SIZE];
    char given[BOARD_SIZE + 2];
    char ch;
    int cx, cy;

    cx = X_START;
    cy = Y_START;

    init_board(board, given);

    draw(board, given, 0, 0);
    move(cy, cx);
    refresh();

    while ((ch = getch()) != 'q')
    {
        switch (ch)
        {
            case 'h':
                cx -= 4;
                if (cx < 0) { cx = X_START; }
                break;
            case 'l':
                cx += 4;
                if (cx > X_END) { cx = X_END; }
                break;
            case 'j':
                cy -= 2;
                if (cy < 0) { cy = Y_START; }
                break;
            case 'k':
                cy += 2;
                if (cy > Y_END) { cy = Y_END; }
                break;
        }
        
        if (isdigit(ch) && given[scr_to_idx(cy, cx)] == '.')
        {
            board[scr_to_idx(cy, cx)] = ch - '0';
            draw(board, given, 0, 0);
        }
        
        move(cy, cx);
        refresh();
    }

    endwin();

    return 0;
}
