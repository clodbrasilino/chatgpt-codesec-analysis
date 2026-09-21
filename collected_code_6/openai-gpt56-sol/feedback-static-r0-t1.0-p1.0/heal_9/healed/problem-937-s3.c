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
        unsigned char value = data[i];

        if (frequencies[value] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[value];
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
    size_t frequencies[UCHAR_MAX + 1U] = {0};
    size_t length = 0;
    size_t max_count = 0;
    unsigned char most_common = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        unsigned char value = (unsigned char)ch;

        if (length == SIZE_MAX || frequencies[value] == SIZE_MAX) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        ++frequencies[value];
        ++length;
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
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

    if (printf("Most common character: '%c'\nCount: %zu\n",
               (int)most_common, max_count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}