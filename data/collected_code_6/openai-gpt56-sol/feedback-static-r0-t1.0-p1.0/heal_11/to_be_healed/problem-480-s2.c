#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_max_occurring_character(
    const size_t frequencies[UCHAR_MAX + 1],
    unsigned char *result)
{
    size_t max_count = 0;

    if (frequencies == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            *result = (unsigned char)i;
        }
    }

    return max_count != 0;
}

int main(void)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    unsigned char result;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; input[i] != '\0' && input[i] != '\n'; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (frequencies[current] == SIZE_MAX) {
            return EXIT_FAILURE;
        }

        ++frequencies[current];
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(frequencies, &result)) {
        return EXIT_FAILURE;
    }

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}