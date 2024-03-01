 #ifndef MAZE_STRUCTS
 #define MAZE_STRUCTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define the range of the length of the maze
#define maxLength 100
#define minLength 5

//struct to contain the dimensions of the maze and player cordinates
typedef struct{
    char **mazeLayout;
    int mazeWidth, mazeHeight;
    int playerX, playerY;
} Maze;

#endif