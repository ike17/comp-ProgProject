#!/bin/bash

#compile the game
gcc mazeGame.c -o maze

fileName=$1

#check if filename was passed as argument
if [ -z $fileName ];
then
    echo "File not specified"
    exit 1
fi


echo -e "Tests"

#check if file is present
echo -n "Testing if file is present - "
if [ -e $fileName ];
then
    echo "File Exists"
else
    echo "No File Found"
fi

#check is file is readable
echo -n "Testing if file is accessible - "
if [ -r $fileName ];
then
    echo "File can be read"
else
    echo "file cannot be read"
fi

#check for incorrect filenames
echo -n "Testing bad filename - "
./maze badMaze.txt > tmp
if grep -q "Error: Bad filename" tmp;
then
    echo "Pass"
else
    echo "Fail"
fi

#check for invalid file formats
echo -n "Testing for invalid file format - "
./maze invalidFormat.docx > tmp
if grep -q "Error: invalid file format" tmp;
then
    echo "Pass"
else
    echo "Fail"
fi

#check if the dimensions of the maze are correct
echo -n "Testing if maze is less than the minimum dimensions required - "
./maze $fileName > tmp
if grep -q "Error: Invalid Maze Dimensions" tmp;
then
    echo "Pass"
else
    echo "Fail"
fi

#check if there is no start or end in the maze
echo -n "Testing if maze does not contains a start or and end point - "
./maze $fileName > tmp
if grep -q "Error: No Start or End Point Detected" tmp;
then
    echo "Pass"
else
    echo "Fail"
fi

#check for multiple start or end points
echo -n "Testing if maze contains multiple start points - "
./maze $fileName > tmp
if grep -q "Error: Multiple Start Points Detected" tmp;
then
    echo "Pass"
else
    echo "Fail"
fi

#check if the position the player starts is from the S
echo -n "Testing if player is not at the start in the beginning - "
./maze $fileName > tmp
if grep -q "Error: Player Not At Start" tmp;
then
    echo "Pass"
else
    echo "Fail"
fi

#checking movement
echo -n "Testing if movements are functional - "
echo "W" | ./maze $fileName > tmp
if grep -q "Moved Up" tmp; 
then
    echo "Pass"
else
    echo "Fail"
fi

#check for invalid input
echo -n "Testing for valid input - "
validInput=("W" "A" "S" "D")
fail=0
for input in "${validInput[@]}"
do
    echo "$input" | ./maze $fileName > tmp;
    if grep -q "Error: Invalid input"; 
    then
        echo "Fail"
        fail=1
        break
    fi
done
if [ $fail -eq 0 ];
then
    echo "pass"
fi

#check for no input
echo -n "Testing for no input - "
echo "" | ./maze $fileName > tmp;
if grep -q "Error: Invalid input"; 
then
    echo "Pass"
else
    echo "Fail"
fi

#check for multiple character inputs
echo -n "Testing for multiple input - "
echo "AS" | ./maze $fileName > tmp;
if grep -q "Error: Invalid input"; 
then
    echo "Pass"
else
    echo "Fail"
fi

#check interaction with walls
echo -n "Testing interaction with walls - "
./maze $fileName > tmp
if grep -q "You Have Hit A Wall" tmp;
then
    echo "Pass"
else
    echo "Fail"
fi

#check for out of bound conditions
echo -n "Testing for out of bounds - "
./maze $fileName > tmp
if grep -q "Out Of Bounds" tmp;
then
    echo "Pass"
else
    echo "Fail"
fi

#check win condition
echo -n "Testing when player reaches the end - "
./maze $fileName > tmp
if grep -q "Congratulations!" tmp;
then
    echo "Pass"
else
    echo "Fail"
fi


rm -f tmp

echo -e "Tests Completed"
