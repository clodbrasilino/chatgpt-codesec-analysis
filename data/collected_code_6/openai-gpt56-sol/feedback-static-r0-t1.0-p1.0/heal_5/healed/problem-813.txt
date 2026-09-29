#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t string_length(const char *str)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[length] != '\0') {
        ++length;
    }

    return length;
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

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
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

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        perror("Failed to read input");
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';
    printf("%zu\n", string_length(input));

    free(input);
    return EXIT_SUCCESS;
}