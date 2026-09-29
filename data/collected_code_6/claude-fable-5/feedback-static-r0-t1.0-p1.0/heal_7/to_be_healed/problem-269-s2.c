#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

int get_ascii_value(char c)
{
    return (int)(unsigned char)c;
}

static void flush_stdin(void)
{
    int extra;
    unsigned long guard = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        extra = getchar();
        guard++;
    } while (extra != '\n' && extra != EOF && guard < ULONG_MAX);
}

int main(void)
{
    int input;

    printf("Enter a character: ");
    fflush(stdout);

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    input = getchar();
    if (input == EOF) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    if (input < 0 || input > UCHAR_MAX) {
        fprintf(stderr, "Error: input out of valid character range\n");
        return EXIT_FAILURE;
    }

    if (input != '\n') {
        flush_stdin();
    }

    if (isprint((unsigned char)input)) {
        printf("The ASCII value of '%c' is %d\n", (char)input, get_ascii_value((char)input));
    } else {
        printf("The ASCII value of the entered character is %d\n", get_ascii_value((char)input));
    }

    return EXIT_SUCCESS;
}