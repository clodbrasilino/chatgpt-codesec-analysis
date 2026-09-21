#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

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
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    for (cursor = input; *cursor != '\0' && *cursor != '\n'; ++cursor) {
    }

    if (*cursor == '\n') {
        *cursor = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }
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

    if (printf("%d\n", remainder) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}