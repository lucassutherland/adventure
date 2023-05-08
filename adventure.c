#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graphics.h"
#include "game.h"

void generate_terrain(struct tile board[BOARD_ROWS][BOARD_COLS]);
void tile_terrain_decision(int row, int col, 
    struct tile board[BOARD_ROWS][BOARD_COLS]);
void generate_entities(struct tile board[BOARD_ROWS][BOARD_COLS]);
bool in_board(int row, int col);

int main(void) {

    struct tile board[BOARD_ROWS][BOARD_COLS];

    printf("Generating terrain...   ");
    generate_terrain(board);
    printf("Terrain generated!\n");

    printf("Generating entities...  ");
    generate_entities(board);
    printf("Entities generated!\n");

    printf("Printing board...\n\n");
    printf("\033[1;1H\033[2J");
    print_board(board);

    char move;
    int player_row = 3;
    int player_col = 3;
    board[player_row][player_col].entity = PLAYER;
    printf("\033[1;1H\033[2J");
    print_board(board);
    
    while ((move = getchar()) != EOF) {

        if (move == '\n') continue;

        board[player_row][player_col].entity = NONE;

        if (move == 'w' && in_board(player_row - 1, player_col)) player_row--;
        else if (move == 'a' && in_board(player_row, player_col - 1)) player_col--;
        else if (move =='s' && in_board(player_row + 1, player_col)) player_row++;
        else if (move == 'd' && in_board(player_row, player_col + 1)) player_col++;

        board[player_row][player_col].entity = PLAYER;

        clear_screen();
        print_board(board);
    }

    printf("\nGame Over!\n");

}

void generate_entities(struct tile board[BOARD_ROWS][BOARD_COLS]) {
    for(int row = 0; row < BOARD_ROWS; row++) {
        for(int col = 0; col < BOARD_COLS; col++) {
            board[row][col].entity = NONE;
        }
    }
}

void generate_terrain(struct tile board[BOARD_ROWS][BOARD_COLS]) {
    for(int row = 0; row < BOARD_ROWS; row++) {
        for(int col = 0; col < BOARD_COLS; col++) {
            
            int r = (rand() + 1) % 6; // - seed, % num terrain types
            if (r == 0) board[row][col].terrain = GRASS;
            if (r == 1) board[row][col].terrain = FOREST;
            if (r == 2) board[row][col].terrain = SAND;
            if (r == 3) board[row][col].terrain = WATER;
            if (r == 4) board[row][col].terrain = MOUNTAIN;
            if (r == 5) board[row][col].terrain = OCEAN;


        }
    }
}

void tile_terrain_decision(int row, int col, 
                            struct tile board[BOARD_ROWS][BOARD_COLS]) {

}

bool in_board(int row, int col) {
    return row >= 0 && row < BOARD_ROWS && col >= 0 && col < BOARD_COLS;
}
