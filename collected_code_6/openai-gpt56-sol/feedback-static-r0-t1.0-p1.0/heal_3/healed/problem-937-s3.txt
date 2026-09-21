#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int most_common_character(const unsigned char *data,
                          size_t length,
                          unsigned char *character,
                          size_t *count)
{
    size_t frequencies[256] = {0};
    size_t max_count = 0;
    unsigned char most_common = 0;

    if (data == NULL || character == NULL || count == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == SIZE_MAX) {
            return -1;
        }
        ++frequencies[data[i]];
    }

    for (size_t i = 0; i < 256; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            most_common = (unsigned char)i;
        }
    }

    *character = most_common;
    *count = max_count;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char character;
    size_t count;
    char buffer[4096];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t chunk_length = 0;

        while (chunk_length < sizeof buffer &&
               buffer[chunk_length] != '\0' &&
               buffer[chunk_length] != '\n') {
            ++chunk_length;
        }

        if (chunk_length > 0) {
            unsigned char *new_input;
            size_t required_capacity;

            if (length > SIZE_MAX - chunk_length) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            required_capacity = length + chunk_length;

            if (required_capacity > capacity) {
                size_t new_capacity = capacity == 0 ? 128 : capacity;

                while (new_capacity < required_capacity) {
                    if (new_capacity > SIZE_MAX / 2) {
                        new_capacity = required_capacity;
                        break;
                    }
                    new_capacity *= 2;
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

            for (size_t i = 0; i < chunk_length; ++i) {
                input[length + i] = (unsigned char)buffer[i];
            }
            length += chunk_length;
        }

        if (chunk_length < sizeof buffer && buffer[chunk_length] == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (most_common_character(input, length, &character, &count) != 0) {
        free(input);
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Most common character: '%c'\nCount: %zu\n",
           (int)character, count);

    free(input);
    return EXIT_SUCCESS;
}