#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t length = 0;
    unsigned char result;
    unsigned char buffer[4096];
    int finished = 0;

    while (!finished) {
        size_t count = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

        if (count == 0) {
            if (ferror(stdin)) {
                perror("Failed to read input");
                return EXIT_FAILURE;
            }
            break;
        }

        size_t usable = count;
        unsigned char *newline = memchr(buffer, '\n', count);

        if (newline != NULL) {
            usable = (size_t)(newline - buffer);
            finished = 1;
        }

        if (usable > SIZE_MAX - length) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < usable; ++i) {
            if (frequencies[buffer[i]] == SIZE_MAX) {
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }
            ++frequencies[buffer[i]];
        }

        length += usable;

        if (!finished && count < sizeof buffer) {
            if (ferror(stdin)) {
                perror("Failed to read input");
                return EXIT_FAILURE;
            }
            break;
        }
    }

    if (length == 0) {
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t max_count = 0;
    unsigned int max_character = 0;

    for (unsigned int i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            max_character = i;
        }
    }

    result = (unsigned char)max_character;

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}