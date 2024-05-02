#include <stdio.h>
#include <stdlib.h>
#include "mazeFx.h"

#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3
#define EXIT_OTHER_ERROR 100

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_ARG_ERROR;
    }

    Maze maze;
    if (!loadMaze(&maze, argv[1])) {
        return EXIT_FILE_ERROR;
    }

    if (!mazeDimensions(&maze) || !validateMaze(&maze)) {
        freeMaze(&maze);
        return EXIT_MAZE_ERROR;
    }

    if (!mazeData(&maze)) {
        freeMaze(&maze);
        return EXIT_OTHER_ERROR;
    }

    maze.playerPos = maze.startPos;
    maze.playerWin = false;

    char move;
    while (!maze.playerWin) {
        printf("Enter your move (w/a/s/d) or 'm' to display the maze: ");
        scanf(" %c", &move);

        switch (move) {
            case 'w':
            case 'a':
            case 's':
            case 'd':
                if (!playerMovement(&maze, move)) {
                    printf("Invalid move! Try again.\n");
                } else if (maze.playerPos.x == maze.endPos.x && maze.playerPos.y == maze.endPos.y) {
                    maze.playerWin = true;
                }
                break;
            case 'm':
            case 'M':
                displayMaze(&maze);
                break;
            default:
                printf("Invalid input! Try again.\n");
                break;
        }
    }

    printf("Congratulations! You've completed the maze!\n");
    freeMaze(&maze);

    return EXIT_SUCCESS;
}