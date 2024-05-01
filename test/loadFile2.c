#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for strlen()
#include <stdbool.h>

#define MORE_LINES 1024
#define MORE_CHARS 1024

int main(void) {
    // Open test.txt for reading
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int lineCount = 1;
    char c;
    do{
        c = fgetc(file);
        if (c== '\n') lineCount++;
    }while (c!=EOF);

    rewind(file);

    char line[MORE_LINES];
    if (fgets(line, MORE_LINES, file) != NULL) {
        printf("Contents of the first line: %s", line);
    } else {
        printf("Unable to read the first line.\n");
    }

    printf("%d\n", lineCount);

    fclose(file);  // Close the file
    return 0;
}
