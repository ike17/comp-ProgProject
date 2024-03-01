#ifndef MAZE_FX
#define MAZE_FX

void loadMaze(Maze *maze, char *fileName);
int validateMaze(Maze *maze);
int playerMovement(Maze *maze, char playerMove);
void displayMaze(Maze *maze);
void freeMaze(Maze *maze);

#endif
