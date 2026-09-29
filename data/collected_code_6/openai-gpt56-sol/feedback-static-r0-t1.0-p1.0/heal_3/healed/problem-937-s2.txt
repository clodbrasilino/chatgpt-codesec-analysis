#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int most_common_character(const unsigned char *data, size_t length,
                          unsigned char *result, size_t *count)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t highest = 0;
    unsigned char most_common = 0;

    if (data == NULL || result == NULL || count == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = data[i];

        if (frequencies[character] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[character];

        if (frequencies[character] > highest) {
            highest = frequencies[character];
            most_common = character;
        }
    }

    *result = most_common;
    *count = highest;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char character;
    size_t count;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return 1;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 256;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too long.\n", stderr);
                    return 1;
                }
                new_capacity = capacity * 2;
            }

            unsigned char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (ch == '\n' && length > 0 && input[length - 1] == '\r') {
        --length;
    }

    if (most_common_character(input, length, &character, &count) != 0) {
        free(input);
        fputs("Input must not be empty.\n", stderr);
        return 1;
    }

    free(input);

    if (printf("%c %zu\n", (int)character, count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    return 0;
}