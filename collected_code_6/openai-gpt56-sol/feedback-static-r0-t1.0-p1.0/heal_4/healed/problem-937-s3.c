#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int most_common_character(const unsigned char *data,
                          size_t length,
                          unsigned char *character,
                          size_t *count)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
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

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
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
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t length = 0;
    unsigned char most_common = 0;
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        if (bytes_read > SIZE_MAX - length) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        length += bytes_read;

        for (size_t i = 0; i < bytes_read; ++i) {
            if (buffer[i] == '\n') {
                goto input_complete;
            }

            if (frequencies[buffer[i]] == SIZE_MAX) {
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            ++frequencies[buffer[i]];
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }
    }

input_complete:
    length = 0;

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > 0) {
            if (length > SIZE_MAX - frequencies[i]) {
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }
            length += frequencies[i];
        }

        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            most_common = (unsigned char)i;
        }
    }

    if (length == 0) {
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Most common character: '%c'\nCount: %zu\n",
           (int)most_common, max_count);

    return EXIT_SUCCESS;
}