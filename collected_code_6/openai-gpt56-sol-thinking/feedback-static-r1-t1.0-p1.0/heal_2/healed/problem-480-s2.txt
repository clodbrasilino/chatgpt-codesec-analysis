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
    unsigned char maximum;

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
        ++frequencies[(size_t)*current];
        ++current;
    }

    current = (const unsigned char *)string;
    maximum = *current;

    while (*current != '\0') {
        if (frequencies[(size_t)*current] >
            frequencies[(size_t)maximum]) {
            maximum = *current;
        }
        ++current;
    }

    *character = maximum;
    *occurrences = frequencies[(size_t)maximum];

    free(frequencies);
    return true;
}

int main(int argc, char *argv[])
{
    unsigned char character;
    size_t occurrences;
    const char *program_name;
    const char *input;

    program_name =
        argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];

    if (*input == '\0') {
        fputs("The string must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(input, &character, &occurrences)) {
        fputs("Unable to process the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Maximum occurring character: %c (%zu occurrences)\n",
               (int)character, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}