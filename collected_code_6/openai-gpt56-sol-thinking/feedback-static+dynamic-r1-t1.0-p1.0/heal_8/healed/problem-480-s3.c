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
    size_t *frequencies;
    size_t frequency_count;
    size_t maximum = 0;
    const unsigned char *current;

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
        ++frequencies[*current];
        ++current;
    }

    for (size_t i = 0; i < frequency_count; ++i) {
        if (frequencies[i] > maximum) {
            maximum = frequencies[i];
        }
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        if (frequencies[*current] == maximum) {
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
    const char *program_name = "program";

    if (argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        if (fputs("The string must not be empty.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(argv[1], &character, &occurrences)) {
        if (fputs("Unable to process the string.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (printf("%c\n", (int)character) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}