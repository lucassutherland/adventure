#include <stdio.h>
#include <stdlib.h>

#define BOARD_ROWS 25
#define BOARD_COLS 32

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

// includes color mapping
enum terrain {
    VOID = DEFAULT,
    GRASS = LIGHT_GREEN,
    SAND = LIGHT_YELLOW,
    WATER = LIGHT_CYAN,
    MOUNTAIN = DARK_GRAY,
    FOREST = GREEN,
    OCEAN = LIGHT_BLUE,
};

enum entity {
    NONE,
    PLAYER,
};

struct tile {
    enum terrain terrain;
    enum entity entity;
};

void color_print(char *text, enum color color);
void print_board(struct tile board[BOARD_ROWS][BOARD_COLS]);
void generate_terrain(struct tile board[BOARD_ROWS][BOARD_COLS]);
void print_tile(struct tile tile);
void tile_terrain_decision(int row, int col, 
    struct tile board[BOARD_ROWS][BOARD_COLS]);
void generate_entities(struct tile board[BOARD_ROWS][BOARD_COLS]);


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

        if (move == 'w') player_row--;
        else if (move == 'a') player_col--;
        else if (move =='s') player_row++;
        else if (move == 'd') player_col++;

        board[player_row][player_col].entity = PLAYER;

        printf("\033[1;1H\033[2J");
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

void print_board(struct tile board[BOARD_ROWS][BOARD_COLS]) {
    for(int row = 0; row < BOARD_ROWS; row++) {
        for(int col = 0; col < BOARD_COLS; col++) {
            print_tile(board[row][col]);
        }
        printf("\n");
    }
}

void print_tile(struct tile tile) {
    if (tile.entity == PLAYER) {
        color_print("\u3000", RED); // regular spaces don't work, ideographic space does
    } else {
        color_print("\u3000", tile.terrain); // regular spaces don't work, ideographic space does
    }
}

void color_print(char *text, enum color color) {
    // see ansi color codes for fun
    printf("\033[7m");          // makes fore/background reverse, bit scuffed w whitespace
    printf("\033[%dm%s\033[0m", color, text); // sets color, prints text, reverts to default style
}