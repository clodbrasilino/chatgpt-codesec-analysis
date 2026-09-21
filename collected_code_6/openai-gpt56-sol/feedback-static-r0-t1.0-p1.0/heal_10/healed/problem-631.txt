#include <ctype.h>
#include <stdint.h>
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
        } else if (isspace(*current)) {
            *current = (unsigned char)'_';
        }
    }

    return 0;
}

int main(void)
{
    char *input;
    size_t capacity = 128;
    size_t length = 0;
    int ch;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length >= SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = length + 2;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(input);
                return EXIT_FAILURE;
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

    if (ferror(stdin)) {
        perror("stdin");
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (replace_whitespace_and_underscores(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        perror("stdout");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}