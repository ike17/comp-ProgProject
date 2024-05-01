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

    char **lines = malloc(sizeof(char *) * MORE_LINES);
    if (lines == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    size_t total_lines = 0, total_chars = 0;
    char c;
    do {
        c = fgetc(file);
        if (ferror(file)) {
            printf("Error reading from file.\n");
            for (size_t i = 0; i < total_lines; i++) free(lines[i]);
            free(lines);
            fclose(file);
            return 1;
        }

        if (feof(file)) {
            if (total_chars != 0) {
                lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
                lines[total_lines][total_chars] = '\0';
                total_lines++;
            }
            break;
        }

        if (total_chars == 0) {
            lines[total_lines] = malloc(MORE_CHARS);
            if (lines[total_lines] == NULL) {
                printf("Memory allocation failed.\n");
                for (size_t i = 0; i < total_lines; i++) free(lines[i]);
                free(lines);
                fclose(file);
                return 1;
            }
        }

        lines[total_lines][total_chars++] = c;
        if (c == '\n') {
            lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
            lines[total_lines][total_chars - 1] = '\0';
            total_chars = 0;
            total_lines++;
            if (total_lines % MORE_LINES == 0) {
                size_t new_size = total_lines + MORE_LINES;
                lines = realloc(lines, sizeof(char *) * new_size);
            }
        } else if (total_chars % MORE_CHARS == 0) {
            size_t new_size = total_chars + MORE_CHARS;
            lines[total_lines] = realloc(lines[total_lines], new_size);
        }
    } while (true);

    lines = realloc(lines, sizeof(char *) * total_lines);

    // Check if all lines have the same number of characters
    int uniform_length = 1;
    if (total_lines > 1) {
        size_t line_length = strlen(lines[0]);
        for (size_t i = 1; i < total_lines; i++) {
            if (strlen(lines[i]) != line_length) {
                uniform_length = 0;
                break;
            }
        }
    }

    // Output each string/line in the array of strings
    for (size_t i = 0; i < total_lines; i++) {
        printf("%s", lines[i]);
    }

    // Output the result of the uniform length check
    if (uniform_length) {
        printf("All lines have the same number of characters.\n");
    } else {
        printf("Not all lines have the same number of characters.\n");
    }

    // Free the block of memory allocated for each string and the array of pointers
    for (size_t i = 0; i < total_lines; i++) {
        free(lines[i]);
    }
    free(lines);

    // Close the file
    fclose(file);

    return 0;
}
