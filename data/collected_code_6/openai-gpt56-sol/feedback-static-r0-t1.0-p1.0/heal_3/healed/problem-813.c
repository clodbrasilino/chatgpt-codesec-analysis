#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t string_length(const char *str)
{
    const char *current;

    if (str == NULL) {
        return 0;
    }

    current = str;

    while (*current != '\0') {
        ++current;
    }

    return (size_t)(current - str);
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    for (;;) {
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity <= SIZE_MAX / 2) {
                new_capacity = capacity * 2;
            } else {
                new_capacity = SIZE_MAX;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length] = (char)ch;
        ++length;
    }

    if (ch == EOF && ferror(stdin)) {
        perror("Failed to read input");
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

    printf("%zu\n", string_length(input));

    free(input);
    return EXIT_SUCCESS;
}