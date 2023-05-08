#include <stdio.h>

#include "graphics.h"
#include "game.h"

#define TILE_MEM 30
#define ROW_MEM TILE_MEM * BOARD_ROWS + 1

void print_board(struct tile board[BOARD_ROWS][BOARD_COLS]) {

    for(int row = 0; row < BOARD_ROWS; row++) {

        for(int col = 0; col < BOARD_COLS; col++) {
            print_tile(board[row][col]);
        }
        printf("\n");
    }
    
}

// returns the new amount of buffer used
void print_tile(struct tile tile) {

    // color mapping
    enum color color;
    
    // entity color takes priority over terrain color
    if (tile.entity != NONE) {
        switch(tile.entity) {
            case PLAYER :
                color = RED;
                break;
        }

    } else {
        switch(tile.terrain) {
            case VOID :
                color = DEFAULT;
                break;
            case GRASS :
                color = LIGHT_GREEN;
                break;
            case SAND :
                color = LIGHT_YELLOW;
                break;
            case WATER :
                color = LIGHT_CYAN;
                break;
            case MOUNTAIN :
                color = DARK_GRAY;
                break;
            case FOREST :
                color = GREEN;
                break;
            case OCEAN :
                color = LIGHT_BLUE;
                break;
        }
    }

    // regular spaces don't work, ideographic space does
    color_print("\u3000", color); 
}


void color_print(char *text, enum color color) {
    // see ansi color codes for fun
    printf("\033[7m");          // makes fore/background reverse, bit scuffed w whitespace
    printf("\033[%dm%s\033[0m", color, text); // sets color, prints text, reverts to default style
}

void clear_screen(void) {
    printf("\033[1;1H\033[2J"); // magic
}