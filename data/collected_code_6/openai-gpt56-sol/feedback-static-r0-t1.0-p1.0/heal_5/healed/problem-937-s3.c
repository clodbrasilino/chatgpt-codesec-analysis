#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    unsigned char buffer[4096];
    unsigned char most_common = 0;
    size_t max_count = 0;
    size_t length = 0;
    int input_complete = 0;

    while (!input_complete) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (buffer[i] == '\n') {
                input_complete = 1;
                break;
            }

            if (length == SIZE_MAX ||
                frequencies[buffer[i]] == SIZE_MAX) {
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            ++length;
            ++frequencies[buffer[i]];
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        if (bytes_read < sizeof buffer) {
            break;
        }
    }

    if (length == 0) {
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            most_common = (unsigned char)i;
        }
    }

    printf("Most common character: '%c'\nCount: %zu\n",
           (int)most_common, max_count);

    return EXIT_SUCCESS;
}