#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define FLUSH_LIMIT 4096UL

static int get_ascii_value(int c)
{
    return (int)(unsigned char)c;
}

static void flush_input(void)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    unsigned long count = 0;

    while (count < FLUSH_LIMIT) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        }
        count++;
    }
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

    printf("The ASCII value of '%c' is %d\n", input, get_ascii_value(input));

    return EXIT_SUCCESS;
}