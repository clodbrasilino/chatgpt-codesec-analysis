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

    while ((ch = getchar()) != EOF && ch != '\n') {
        size_t required;

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        required = length + 2;

        if (capacity < required) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;
            char *new_input;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
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

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
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