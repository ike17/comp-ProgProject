#include "mazeFx.h"

bool loadMazeDimensions(FILE *file, Maze *maze) {
    if (fscanf(file, "%d %d", &maze->width, &maze->height) != 2) {
        fprintf(stderr, "Failed to read maze dimensions.\n");
        return false;
    }
    
    return true;
}


bool loadMazeData(FILE *file, Maze *maze) {
    // Allocate memory for maze layout
    maze->mazeLayout = (char **)malloc(maze->height * sizeof(char *));
    if (maze->mazeLayout == NULL) {
        fprintf(stderr, "Memory allocation failed for maze layout.\n");
        return false;
    }

    char lineBuffer[MAX_MAZE_LENGTH + 2]; // +2 for newline and null terminator
    for (int i = 0; i < maze->height; i++) {
        if (fgets(lineBuffer, sizeof(lineBuffer), file) == NULL) {
            fprintf(stderr, "Failed to read maze data at line %d.\n", i + 1);
            while (i-- > 0) free(maze->mazeLayout[i]);  // Free previous lines
            free(maze->mazeLayout);
            return false;
        }
        maze->mazeLayout[i] = strdup(lineBuffer);
        if (maze->mazeLayout[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for maze row.\n");
            while (i-- > 0) free(maze->mazeLayout[i]);  // Free previous lines
            free(maze->mazeLayout);
            return false;
        }
    }
    return true;
}


bool loadMaze(const char *filename, Maze *maze) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return false;
    }

    // Load maze dimensions
    if (!loadMazeDimensions(file, maze)) {
        fclose(file);
        return false;
    }

    // Load maze data
    if (!loadMazeData(file, maze)) {
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}



bool validateMaze(Maze *maze) {
    if (maze->width < MIN_MAZE_LENGTH || maze->width > MAX_MAZE_LENGTH ||
        maze->height < MIN_MAZE_LENGTH || maze->height > MAX_MAZE_LENGTH) {
        fprintf(stderr, "Maze dimensions are out of acceptable range (%d to %d).\n", MIN_MAZE_LENGTH, MAX_MAZE_LENGTH);
        return false;
    }

    int startCount = 0, endCount = 0;
    size_t expectedLength = strlen(maze->mazeLayout[0]);

    for (int i = 0; i < maze->height; i++) {
        size_t currentLength = strlen(maze->mazeLayout[i]);
        if (currentLength != expectedLength) {
            fprintf(stderr, "Line %d has a length of %zu, which differs from the expected length of %zu.\n", i + 1, currentLength, expectedLength);
            return false;
        }

        for (int j = 0; j < currentLength; j++) {
            char cell = maze->mazeLayout[i][j];
            switch (cell) {
                case START_CHAR:
                    if (++startCount > 1) {
                        fprintf(stderr, "Multiple start points detected.\n");
                        return false;
                    }
                    maze->startPos = (Position){.x = j, .y = i};
                    break;
                case END_CHAR:
                    if (++endCount > 1) {
                        fprintf(stderr, "Multiple end points detected.\n");
                        return false;
                    }
                    maze->endPos = (Position){.x = j, .y = i};
                    break;
                case WALL_CHAR:
                case EMPTY_CHAR:
                    break;
                default:
                    fprintf(stderr, "Invalid character detected at line %d, column %d: %c\n", i + 1, j + 1, cell);
                    return false;
            }
        }
    }

    if (startCount != 1 || endCount != 1) {
        fprintf(stderr, "Incorrect number of start (%d) or end (%d) points. Each should have exactly one.\n", startCount, endCount);
        return false;
    }

    return true;
}




bool hasValidPath(Maze *maze);




bool dfs(Maze *maze, int x, int y, bool **visited);




bool playerMovement(Maze *maze, char move) {
    Position newPos = maze->playerPos;

    // scanf for movement case insensitive
    
    switch (move) {
        case 'w':
            newPos.y--;
            break;
        case 'a':
            newPos.x--;
            break;
        case 's':
            newPos.y++;
            break;
        case 'd':
            newPos.x++;
            break;
        default:
            return false;
    }

    if (newPos.x < 0 || newPos.x >= maze->width || newPos.y < 0 || newPos.y >= maze->height ||
        maze->mazeLayout[newPos.y][newPos.x] == WALL_CHAR) {
        return false;
    }

    maze->playerPos = newPos;
    return true;
}




void displayMaze(Maze *maze)(
    // make sure we have a leading newline..
    printf("\n");
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            // decide whether player is on this spot or not
            if (player->x == j && player->y == i)
            {
                printf("X");
            }
            else
            {
                printf("%c", this->map[i][j]);
            }
        }
        // end each row with a newline.
        printf("\n");
    }
)




void freeMaze(Maze *maze) {
    for (int i = 0; i < maze->height; i++) {
        free(maze->mazeLayout[i]);
    }
    free(maze->mazeLayout);
}