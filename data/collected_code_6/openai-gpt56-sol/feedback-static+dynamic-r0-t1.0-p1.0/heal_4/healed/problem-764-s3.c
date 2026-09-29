#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_numeric_values(const char *text)
{
    size_t count = 0;
    int in_number = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isdigit((unsigned char)*text)) {
            if (!in_number) {
                ++count;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
        ++text;
    }

    return count;
}

int main(void)
{
    char *input;
    size_t length;
    size_t capacity;
    int ch;

    capacity = 128;
    length = 0;
    input = malloc(capacity);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1) {
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

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (printf("%zu\n", count_numeric_values(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}