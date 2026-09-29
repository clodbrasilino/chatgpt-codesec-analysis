#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int replace_whitespace_and_underscores(char *string)
{
    unsigned char *current;

    if (string == NULL) {
        return -1;
    }

    for (current = (unsigned char *)string; *current != '\0'; ++current) {
        if (*current == (unsigned char)'_') {
            *current = (unsigned char)' ';
        } else if (isspace((int)*current)) {
            *current = (unsigned char)'_';
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        perror("getchar");
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *new_input;

        if (capacity == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        new_input = realloc(input, capacity + 1);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        capacity++;
    }

    input[length] = '\0';

    if (replace_whitespace_and_underscores(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        perror("puts");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}