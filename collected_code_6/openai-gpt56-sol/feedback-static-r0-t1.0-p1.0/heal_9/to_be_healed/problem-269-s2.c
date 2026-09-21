#include <stdio.h>
#include <stdlib.h>

static unsigned int ascii_value(unsigned char character)
{
    return (unsigned int)character;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int character = getchar();

    if (character == EOF) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No character provided.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("%u\n", ascii_value((unsigned char)character)) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}