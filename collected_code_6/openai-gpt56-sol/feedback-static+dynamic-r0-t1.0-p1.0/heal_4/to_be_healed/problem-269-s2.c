#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int ascii_value(unsigned char character)
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
            fprintf(stderr, "Failed to read input.\n");
        } else {
            fprintf(stderr, "No character provided.\n");
        }
        return EXIT_FAILURE;
    }

    if (input < 0 || input > UCHAR_MAX) {
        fprintf(stderr, "Invalid input value.\n");
        return EXIT_FAILURE;
    }

    if (printf("%d\n", ascii_value((unsigned char)input)) < 0) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}