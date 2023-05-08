#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "game.h"

enum color {
    DEFAULT = 0,
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    LIGHT_GRAY,
    DARK_GRAY = 90,
    LIGHT_RED,
    LIGHT_GREEN,
    LIGHT_YELLOW,
    LIGHT_BLUE,
    LIGHT_MAGENTA,
    LIGHT_CYAN,
    WHITE,
};


void clear_screen(void);

void print_board(struct tile board[BOARD_ROWS][BOARD_COLS]);

void print_tile(struct tile tile);

void color_print(char *text, enum color color);

#endif