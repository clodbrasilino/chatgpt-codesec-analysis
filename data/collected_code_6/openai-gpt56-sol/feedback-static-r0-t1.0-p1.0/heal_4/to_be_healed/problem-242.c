#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    size_t count = 0;
    int character;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (count == SIZE_MAX) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        ++count;
    }

    if (character == EOF && count == 0) {
        return EXIT_SUCCESS;
    }

    if (printf("%zu\n", count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}