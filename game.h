#ifndef GAME_H
#define GAME_H

#define BOARD_ROWS 20
#define BOARD_COLS 35

// includes color mapping
enum terrain {
    VOID,
    GRASS,
    SAND,
    WATER,
    MOUNTAIN,
    FOREST,
    OCEAN,
};

enum entity {
    NONE,
    PLAYER,
};

struct tile {
    enum terrain terrain;
    enum entity entity;
};


#endif