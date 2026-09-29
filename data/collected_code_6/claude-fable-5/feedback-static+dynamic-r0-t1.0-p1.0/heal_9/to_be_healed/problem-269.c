#include <stdio.h>
#include <ctype.h>
#include <limits.h>

static int get_ascii_value(char c)
{
    return (int)(unsigned char)c;
}

static void flush_stdin(void)
{
    int ch;
    unsigned long guard = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < ULONG_MAX);
}

int main(void)
{
    int input;

    printf("Enter a character: ");
    if (fflush(stdout) != 0) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    input = getchar();
    if (input == EOF) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    if (input != '\n') {
        flush_stdin();
    }

    if (isprint((unsigned char)input)) {
        printf("The ASCII value of '%c' is %d\n", (char)input, get_ascii_value((char)input));
    } else {
        printf("The ASCII value of the entered character is %d\n", get_ascii_value((char)input));
    }

    return 0;
}