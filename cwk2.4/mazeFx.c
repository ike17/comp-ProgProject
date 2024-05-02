#include "mazeFx.h"




bool loadMaze(const char *filename, Maze *maze) {
    FILE *mazeFile; 
    mazeFile = fopen(filename, "r");
    if (mazeFile == NULL){
        return false;
    }

    if (!mazeDimensions(mazeFile, maze)) {
        fclose(mazeFile);
        return false;
    }

    if (!mazeData(mazeFile, maze)) {
        fclose(mazeFile);
        return false;
    }

    fclose(mazeFile);
    return true;
}


bool mazeDimensions(FILE *file, Maze *maze) {
    char line[1024];
    int lineCount = 0;
    size_t width = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline character if present
        size_t currentLength = strlen(line);
        if (line[currentLength-1] == '\n') {
            line[currentLength-1] = '\0';
            currentLength--;
        }

        // Check if line is empty after removing newline, ignore it if so
        if (currentLength == 0 && feof(file)) {
            continue;
        }

        // Set width from the first non-empty line
        if (lineCount == 0) {
            width = currentLength;
        } else {
            // Check subsequent lines for consistent width
            if (currentLength != width) {
                return false;
            }
        }
        lineCount++;
    }

    // Set the maze dimensions
    maze->width = width;
    maze->height = lineCount;
    rewind(file);  // Rewind file for subsequent reading in mazeData
    return true;
}


bool mazeData(FILE *file, Maze *maze) {
    maze->mazeLayout = (char **)malloc(maze->height * sizeof(char *));
    if (maze->mazeLayout == NULL) {
        return false;
    }

    char lineBuffer[MAX_MAZE_LENGTH + 2];
    for (int i = 0; i < maze->height; i++) {
        if (fgets(lineBuffer, sizeof(lineBuffer), file) == NULL || lineBuffer[0] == '\n') {
            while (i-- > 0) free(maze->mazeLayout[i]);
            free(maze->mazeLayout);
            return false;
        }
        maze->mazeLayout[i] = strdup(lineBuffer);
        if (maze->mazeLayout[i] == NULL) {
            while (i-- > 0) free(maze->mazeLayout[i]);
            free(maze->mazeLayout);
            return false;
        }

        size_t len = strlen(maze->mazeLayout[i]);
        if (maze->mazeLayout[i][len - 1] == '\n') {
            maze->mazeLayout[i][len - 1] = '\0';
        }
    }
    return true;
}


bool validateMaze(Maze *maze) {
    if (maze->width < MIN_MAZE_LENGTH || maze->width > MAX_MAZE_LENGTH ||
        maze->height < MIN_MAZE_LENGTH || maze->height > MAX_MAZE_LENGTH) {
        return false;
    }

    int startCount = 0, endCount = 0;
    size_t expectedLength = strlen(maze->mazeLayout[0]);

    for (int i = 0; i < maze->height; i++) {
        size_t currentLength = strlen(maze->mazeLayout[i]);
        if (currentLength != expectedLength) {
            return false;
        }

        for (int j = 0; j < currentLength; j++) {
            char cell = maze->mazeLayout[i][j];
            switch (cell) {
                case START_CHAR:
                    if (++startCount > 1) {
                        return false;
                    }
                    maze->startPos = (Position){j, i};
                    break;
                case END_CHAR:
                    if (++endCount > 1) {
                        return false;
                    }
                    maze->endPos = (Position){j, i};
                    break;
                case WALL_CHAR:
                case EMPTY_CHAR:
                    break;
                default:
                    return false;
            }
        }
    }

    if (startCount != 1 || endCount != 1) {
        return false;
    }

    return true;
    // check if maze.width and maze.height out of bounds
    // check for presence of S and E
    // check if S and E are repeated in the code
}


bool playerMovement(Maze *maze, char move) {
    Position newPos = maze->playerPos;
    
    switch (move) {
        case 'W':
        case 'w':
            newPos.y--;
            break;
        case 'A':
        case 'a':
            newPos.x--;
            break;
        case 'S':
        case 's':
            newPos.y++;
            break;
        case 'D':
        case 'd':
            newPos.x++;
            break;
        case 'M':
        case 'm':
            displayMaze(maze);
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
    printf("\n");
    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            
            if (maze->playerPos.x == j && maze->playerPos.y == i) {
                printf("X");
            } else {
                printf("%c", maze->mazeLayout[i][j]);
            }
        }
        printf("\n");
    }
)




void freeMaze(Maze *maze) {
    for (int i = 0; i < maze->height; i++) {
        free(maze->mazeLayout[i]);
    }
    free(maze->mazeLayout);
}