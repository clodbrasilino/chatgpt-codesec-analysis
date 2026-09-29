#include <stdio.h>
#include <stdlib.h>

int ascii_value(unsigned char character)
{
    return (int)character;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int input = getchar();

    if (input == EOF) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    printf("%d\n", ascii_value((unsigned char)input));

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}