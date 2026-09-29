#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const unsigned char *str, size_t length,
                            size_t *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t total = 0;

    if (result == NULL || (str == NULL && length != 0)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = frequencies[str[i]];

        if (frequency == SIZE_MAX || total > SIZE_MAX - frequency - 1) {
            return -1;
        }

        frequencies[str[i]] = frequency + 1;
        total += frequency + 1;
    }

    *result = total;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    size_t count;
    int ch = EOF;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_input;

            if (capacity == 0) {
                new_capacity = 256;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too long.\n", stderr);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Unable to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length] = (unsigned char)ch;
        ++length;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_substrings(input, length, &count) != 0) {
        free(input);
        fputs("Unable to count substrings.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}