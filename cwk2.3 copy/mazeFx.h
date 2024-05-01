#ifndef MAZE_FX
#define MAZE_FX

#include "maze.h"

bool loadMaze(Maze *maze, const char *fileName);
bool mazeDimensions(FILE *file, Maze *maze);
bool mazeWidth(FILE *file, Maze *maze);
bool mazeData(FILE *file, Maze *maze) ;
bool validateMaze(Maze *maze);
bool playerMovement(Maze *maze, char move);
void displayMaze(Maze *maze);
void freeMaze(Maze *maze);

#endif