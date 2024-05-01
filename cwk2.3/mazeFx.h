#ifndef MAZE_FX
#define MAZE_FX

#include "maze.h"

bool loadMaze(Maze *maze, const char *fileName);
bool validateMaze(Maze *maze);
bool hasValidPath(Maze *maze);
bool dfs(Maze *maze, int x, int y, bool **visited);
bool playerMovement(Maze *maze, char move);
void displayMaze(Maze *maze);
void freeMaze(Maze *maze);

#endif