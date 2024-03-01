#include "maze.h"
#include "mazeFx.h"

void loadMaze(Maze *maze, char *fileName){
    //open and read maze.txt file

    //error if file not found

    //close maze.txt
}

int validateMaze(Maze *maze){
    //check if the height and width of the maze is within the range

    //check if the length of each line is the same

    //check if a singular start and end position is available

    //check if there are no obstacles preventing user from going from start to end

    //form an array for each line to store the characters in the position of the map

    //store the cordinates of start and end position
}

int playerMovement(Maze *maze, char playerMove){
    //if w or s is pressed increment the user y cordinate by +1 or -1 respectively
    
    //if a or d is pressed increment the user x cordinate by -1 or +1 respectively

    //check if the move is valid or not
}

void displayMaze(Maze *maze){
    //call the stored characters of the map

    //update map with an X in the current position of player

    //print map with user positioning
}

void freeMaze(Maze *maze){
    //free memory space
}