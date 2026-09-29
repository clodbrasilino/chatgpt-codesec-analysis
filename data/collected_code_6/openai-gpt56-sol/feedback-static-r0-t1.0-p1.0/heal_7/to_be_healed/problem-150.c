#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_in_sequence(unsigned long long number)
{
    return number != 0ULL && (number & (number - 1ULL)) == 0ULL;
}

int main(void)
{
    unsigned long long number;
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return EXIT_FAILURE;
    }

    if (ungetc(ch, stdin) == EOF) {
        return EXIT_FAILURE;
    }

    errno = 0;

    if (scanf("%llu", &number) != 1 || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch != EOF) {
        return EXIT_FAILURE;
    }

    puts(is_in_sequence(number) ? "Present" : "Not present");

    return EXIT_SUCCESS;
}