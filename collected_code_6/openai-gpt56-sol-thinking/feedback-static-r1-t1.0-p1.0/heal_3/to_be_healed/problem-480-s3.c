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
        size_t index = (size_t)*current;

        ++frequencies[index];

        if (frequencies[index] > maximum) {
            maximum = frequencies[index];
        }

        ++current;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        if (frequencies[(size_t)*current] == maximum) {
            *character = *current;
            *occurrences = maximum;
            return true;
        }

        ++current;
    }

    return false;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
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