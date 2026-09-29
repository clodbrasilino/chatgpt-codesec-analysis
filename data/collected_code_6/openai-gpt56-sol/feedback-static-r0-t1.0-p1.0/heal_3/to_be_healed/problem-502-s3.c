#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

static int find_remainder(int dividend, int divisor, int *remainder)
{
    if (remainder == NULL || divisor == 0) {
        return -1;
    }

    if (dividend == INT_MIN && divisor == -1) {
        *remainder = 0;
        return 0;
    }

    *remainder = dividend % divisor;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *cursor;
    char *end;
    long dividend;
    long divisor;
    int remainder;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    dividend = strtol(cursor, &end, 10);

    if (cursor == end || errno == ERANGE ||
        dividend < INT_MIN || dividend > INT_MAX) {
        fputs("Invalid dividend.\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = end;
    errno = 0;
    divisor = strtol(cursor, &end, 10);

    if (cursor == end || errno == ERANGE ||
        divisor < INT_MIN || divisor > INT_MAX) {
        fputs("Invalid divisor.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Unexpected input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_remainder((int)dividend, (int)divisor, &remainder) != 0) {
        fputs("Divisor must not be zero.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", remainder);
    return EXIT_SUCCESS;
}