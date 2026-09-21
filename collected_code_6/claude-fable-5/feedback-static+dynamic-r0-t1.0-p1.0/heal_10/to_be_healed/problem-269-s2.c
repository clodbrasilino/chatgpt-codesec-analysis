#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

static int get_ascii_value(char c)
{
    return (int)(unsigned char)c;
}

static void flush_input(void)
{
    int c;
    unsigned long count = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        count++;
        if (count >= ULONG_MAX) {
            break;
        }
    } while (c != '\n' && c != EOF);
}

int main(void)
{
    int input;

    printf("Enter a character: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error: failed to flush output\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    input = getchar();
    if (input == EOF) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    if (input != '\n') {
        flush_input();
    }

    if (!isprint((unsigned char)input)) {
        fprintf(stderr, "Error: input is not a printable character\n");
        return EXIT_FAILURE;
    }

    printf("The ASCII value of '%c' is %d\n", (char)input, get_ascii_value((char)input));

    return EXIT_SUCCESS;
}