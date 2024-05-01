#ifndef MAZE_STRUCTS
#define MAZE_STRUCTS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_MAZE_LENGTH 100
#define MIN_MAZE_LENGTH 5

#define WALL_CHAR '#'
#define START_CHAR 'S'
#define END_CHAR 'E'
#define EMPTY_CHAR ' '

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    char **mazeLayout;
    int width;
    int height;
    Position startPos;
    Position endPos;
    Position playerPos;
    bool gameOver;
} Maze;

#endif