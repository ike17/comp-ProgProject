#include "mazeFx.h"



bool loadMaze(const char *filename, Maze *maze) {
    File *file; 
    file = fopen(filename, "r");
    if (mazeFile == NULL){
        return 1;
    }else{
        return 0;
    }

    if (!mazeDimensions(file ,maze))(
        fclose(file);
        return 1;
    )

    if (!mazeData(file ,maze))(
        fclose(file);
        return 1;
    )

    fclose(file);
    return 0;
}


bool mazeDimensions(FILE *file, Maze *maze) {
    int lineCount = 1;
    char c;
    char line[1024];
    linecontent[1024];

    do(
        c = fgetc(file);
        if (c== '\n') lineCount++;
    )while (c!=EOF);

    // if last line is an empty trailing new line omit and decrement lineCount
    
    if (fgets(line, 1024, file) != NULL) {
        strcpy(lineContent ,line);
    } else {
        return 1;
    }
    
    maze->width = sizeof(lineContent);
    maze->height = lineCount;
    // maze.width = sizeof(lineContent)
    // maze.height = lineCount

   
}

bool mazeWidth(FILE *file, Maze *maze){
    int line = 0;

    while(!feof(file) && ferror(file)){
        if {fegts(data[line] , 1024, file) != NULL)
        line++;
        }
    }

    for (x=1; x<line; x++){
        if  (izeof(line) != sizeof(line[0])){
            return false;
        }else{
            return true;
        }

    }
    // for loop starting from lineCount 2
        // compare sizeof each line to maze.width
            // if != then return 1

}


bool mazeData(FILE *file, Maze *maze) {

    maze->mazeLayout = (char **)malloc(maze->height * sizeof(char *));
    if (maze->mazeLayout == NULL) {
        return false;
    }

    char lineBuffer[MAX_MAZE_LENGTH + 2]; // +2 for possible newline and null terminator
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
    // for loop to go through each line of code
    // malloc based on the size of line content in each line
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