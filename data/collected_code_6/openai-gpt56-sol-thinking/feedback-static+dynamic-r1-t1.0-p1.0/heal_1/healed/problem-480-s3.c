#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool find_max_occurring_character(const char *string,
                                  unsigned char *character,
                                  size_t *occurrences)
{
    size_t frequencies[UCHAR_MAX + 1U] = {0};
    size_t maximum = 0;
    const unsigned char *current;

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

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > maximum) {
            maximum = frequencies[i];
        }
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        if (frequencies[*current] == maximum) {
            *character = *current;
            *occurrences = maximum;
            return true;
        }

        ++current;
    }

    return false;
}

int main(int argc, char *const argv[])
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

    if (printf("%c\n", (int)character) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}