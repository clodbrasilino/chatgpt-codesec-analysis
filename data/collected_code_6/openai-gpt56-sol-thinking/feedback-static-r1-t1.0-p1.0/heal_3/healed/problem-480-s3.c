#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool find_max_occurring_character(const char *string,
                                   unsigned char *character,
                                   size_t *occurrences)
{
    const unsigned char *current;
    size_t *frequencies;
    size_t frequency_count;
    size_t maximum = 0;

    if (string == NULL || character == NULL || occurrences == NULL) {
        return false;
    }

    current = (const unsigned char *)string;

    if (*current == '\0') {
        return false;
    }

    if ((uintmax_t)UCHAR_MAX >= (uintmax_t)SIZE_MAX) {
        return false;
    }

    frequency_count = (size_t)UCHAR_MAX + 1U;

    if (frequency_count > SIZE_MAX / sizeof(*frequencies)) {
        return false;
    }

    frequencies = calloc(frequency_count, sizeof(*frequencies));

    if (frequencies == NULL) {
        return false;
    }

    while (*current != '\0') {
        size_t index = (size_t)*current;

        if (index >= frequency_count) {
            free(frequencies);
            return false;
        }

        ++frequencies[index];

        if (frequencies[index] > maximum) {
            maximum = frequencies[index];
        }

        ++current;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        size_t index = (size_t)*current;

        if (frequencies[index] == maximum) {
            *character = *current;
            *occurrences = maximum;
            free(frequencies);
            return true;
        }

        ++current;
    }

    free(frequencies);
    return false;
}

int main(int argc, char *argv[const])
{
    unsigned char character;
    size_t occurrences;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(argv[1], &character, &occurrences)) {
        if (fputs("Unable to process the supplied string.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (printf("%c\n", (int)character) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}