#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_max_occurring_character(const size_t frequencies[UCHAR_MAX + 1],
                                 unsigned char *result)
{
    size_t max_count = 0;
    unsigned int max_character = 0;

    if (frequencies == NULL || result == NULL) {
        return 0;
    }

    for (unsigned int i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            max_character = i;
        }
    }

    if (max_count == 0) {
        return 0;
    }

    *result = (unsigned char)max_character;
    return 1;
}

int main(void)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    unsigned char buffer[4096];
    unsigned char result;
    int finished = 0;

    while (!finished) {
        const size_t count = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

        if (count == 0) {
            if (ferror(stdin)) {
                perror("Failed to read input");
                return EXIT_FAILURE;
            }
            break;
        }

        const unsigned char *const newline = memchr(buffer, '\n', count);
        const size_t usable = newline != NULL
                                ? (size_t)(newline - buffer)
                                : count;

        if (newline != NULL) {
            finished = 1;
        }

        for (size_t i = 0; i < usable; ++i) {
            if (frequencies[buffer[i]] == SIZE_MAX) {
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }
            ++frequencies[buffer[i]];
        }
    }

    if (!find_max_occurring_character(frequencies, &result)) {
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}