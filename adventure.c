#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "noise.h"
#include "game.h"
#include "graphics.h"

void generate_terrain(struct tile board[BOARD_ROWS][BOARD_COLS]);
void generate_entities(struct tile board[BOARD_ROWS][BOARD_COLS]);
bool in_board(int row, int col);

int main(void) {

    struct tile board[BOARD_ROWS][BOARD_COLS];

    generate_terrain(board);

    generate_entities(board);

    char move;
    int player_row = 3;
    int player_col = 3;
    board[player_row][player_col].entity = PLAYER;
    clear_screen();
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
    double noise[BOARD_ROWS][BOARD_COLS] = {0};

    for(int i = 0; i < BOARD_ROWS; i++) {
        for(int j = 0; j < BOARD_COLS; j++) {
            noise[i][j] = 1;
        }
    }

    int seed;
    // printf("enter seed number: ");
    // scanf(" %d", &seed);
    time_t t;
    srand((unsigned) time(&t));

    int frequencies[10] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    int amplitudes[10] = {10, 20, 10, 20, 10, 20, 10, 20, 10, 20};

    for(int i = 0; i < 10; i++) {
        add_octave(BOARD_ROWS, BOARD_COLS, noise, 
                rand() % BOARD_COLS, 
                rand() % BOARD_ROWS,
                (BOARD_COLS + BOARD_ROWS) / 2 / frequencies[i], amplitudes[i]);
    }
    


    
    for(int row = 0; row < BOARD_ROWS; row++) {
        for(int col = 0; col < BOARD_COLS; col++) {
            
            enum terrain terrain;
            if (noise[row][col] > 95) terrain = MOUNTAIN;
            else if (noise[row][col] > 80) terrain = FOREST;
            else if (noise[row][col] > 70) terrain = GRASS;
            else if (noise[row][col] > 50) terrain = SAND;
            else if (noise[row][col] > 25) terrain = WATER;
            else if (noise[row][col] > -1) terrain = OCEAN; // -1 for double leniency
            else terrain = VOID;

            board[row][col].terrain = terrain;
        }
    }
}

bool in_board(int row, int col) {
    return row >= 0 && row < BOARD_ROWS && col >= 0 && col < BOARD_COLS;
}
