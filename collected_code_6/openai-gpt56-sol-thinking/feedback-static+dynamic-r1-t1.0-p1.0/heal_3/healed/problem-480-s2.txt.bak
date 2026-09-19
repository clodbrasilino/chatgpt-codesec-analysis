#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool find_max_occurring_character(const char *string,
                                   unsigned char *character,
                                   size_t *occurrences)
{
    size_t frequencies[(size_t)UCHAR_MAX + 1U] = {0};
    const unsigned char *current;
    unsigned char maximum;

    if (string == NULL || character == NULL || occurrences == NULL) {
        return false;
    }

    current = (const unsigned char *)string;

    if (*current == '\0') {
        return false;
    }

    while (*current != '\0') {
        ++frequencies[*current];
        ++current;
    }

    current = (const unsigned char *)string;
    maximum = *current;

    while (*current != '\0') {
        if (frequencies[*current] > frequencies[maximum]) {
            maximum = *current;
        }

        ++current;
    }

    *character = maximum;
    *occurrences = frequencies[maximum];

    return true;
}

int main(int argc, char *argv[const])
{
    unsigned char character;
    size_t occurrences;
    const char *program_name = "program";

    if (argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(argv[1], &character, &occurrences)) {
        if (fputs("The string must not be empty.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (printf("Maximum occurring character: %c (%zu occurrences)\n",
               (int)character, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}