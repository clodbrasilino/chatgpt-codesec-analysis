#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool find_max_occurring_character(const char *string,
                                  unsigned char *character,
                                  size_t *occurrences)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
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

int main(int argc, char *argv[])
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
        if (fputs("The string must not be empty.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Maximum occurring character: %c (%zu occurrences)\n",
               character, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}