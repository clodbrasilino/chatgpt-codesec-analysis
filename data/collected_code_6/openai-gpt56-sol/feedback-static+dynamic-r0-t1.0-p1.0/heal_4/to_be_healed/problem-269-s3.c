#include <stdio.h>
#include <stdlib.h>

static int ascii_value(unsigned char character)
{
    return (int)character;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int character = getchar();

    if (character == EOF) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("%u\n", (unsigned int)ascii_value((unsigned char)character)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}