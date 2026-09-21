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
        const size_t index = (size_t)*current;

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
            free(frequencies);
            return true;
        }

        ++current;
    }

    free(frequencies);
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
        if (fputs("Usage: program <string>\n", stderr) == EOF) {
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

    if (fwrite(&character, sizeof(character), 1U, stdout) != 1U) {
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}