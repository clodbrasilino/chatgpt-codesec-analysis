#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int most_common_character(const unsigned char *data,
                          size_t length,
                          unsigned char *character,
                          size_t *count)
{
    size_t frequencies[UCHAR_MAX + 1U] = {0};
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

    for (size_t i = 0; i < UCHAR_MAX + 1U; ++i) {
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
    unsigned char *data = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char most_common = 0;
    size_t max_count = 0;
    int ch;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(data);
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 256U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(data);
                    fputs("Input is too long.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length) {
                if (length == SIZE_MAX) {
                    free(data);
                    fputs("Input is too long.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = length + 1U;
            }

            unsigned char *new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[length++] = (unsigned char)ch;
    }

    if (length == 0) {
        free(data);
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (most_common_character(data, length, &most_common, &max_count) != 0) {
        free(data);
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(data);

    if (printf("Most common character: '%c'\nCount: %zu\n",
               (int)most_common, max_count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}