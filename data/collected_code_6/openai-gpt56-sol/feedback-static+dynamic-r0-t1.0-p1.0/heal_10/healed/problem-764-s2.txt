#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_numeric_values(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isdigit((unsigned char)*str) != 0) {
            ++count;
        }
        ++str;
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 2 > capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) != 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (printf("%zu\n", count_numeric_values(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}