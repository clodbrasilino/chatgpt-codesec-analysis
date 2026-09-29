#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_occurring_character(
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

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        unsigned char current = (unsigned char)ch;

        if (frequencies[current] == SIZE_MAX) {
            return EXIT_FAILURE;
        }

        ++frequencies[current];
    }

    if (!find_max_occurring_character(frequencies, &result)) {
        return EXIT_FAILURE;
    }

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}