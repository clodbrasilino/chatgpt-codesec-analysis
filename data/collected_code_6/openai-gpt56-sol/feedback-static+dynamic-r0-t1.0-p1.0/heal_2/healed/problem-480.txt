#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_occurring_character(const unsigned char *data, size_t length,
                                  unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;

    if (data == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == SIZE_MAX) {
            return 0;
        }
        ++frequencies[data[i]];
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            *result = (unsigned char)i;
        }
    }

    return 1;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too long.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof *input) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            unsigned char *new_input =
                realloc(input, new_capacity * sizeof *input);

            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        free(input);
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    unsigned char result;

    if (!find_max_occurring_character(input, length, &result)) {
        free(input);
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (putchar(result) == EOF || putchar('\n') == EOF) {
        free(input);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}