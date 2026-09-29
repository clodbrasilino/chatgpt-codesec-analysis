#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_occurring_character(const unsigned char *data,
                                 size_t length,
                                 unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    unsigned int max_character = 0;

    if (data == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == SIZE_MAX) {
            return 0;
        }
        ++frequencies[data[i]];
    }

    for (unsigned int i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            max_character = i;
        }
    }

    *result = (unsigned char)max_character;
    return 1;
}

int main(void)
{
    size_t capacity = 256;
    size_t length = 0;
    unsigned char *input = malloc(capacity);
    unsigned char result;

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        int ch = getchar();

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                perror("Failed to read input");
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (length == SIZE_MAX) {
            fputs("Input is too long.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                if (capacity == SIZE_MAX) {
                    fputs("Input is too long.\n", stderr);
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            unsigned char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (!find_max_occurring_character(input, length, &result)) {
        fputs("Input must not be empty.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}