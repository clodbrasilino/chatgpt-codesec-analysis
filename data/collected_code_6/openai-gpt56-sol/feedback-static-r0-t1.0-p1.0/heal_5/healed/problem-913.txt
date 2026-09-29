#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool ends_with_number(int character)
{
    return character != EOF && isdigit((unsigned char)character) != 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            char *new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return EXIT_FAILURE;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(line);
        return EXIT_FAILURE;
    }

    while (length > 0 && line[length - 1] == '\r') {
        --length;
    }

    bool result = length > 0 &&
                  ends_with_number((unsigned char)line[length - 1]);

    free(line);

    if (puts(result ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}