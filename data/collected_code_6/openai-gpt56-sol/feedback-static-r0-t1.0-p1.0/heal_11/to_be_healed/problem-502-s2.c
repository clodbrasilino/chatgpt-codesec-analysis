#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

static int find_remainder(int dividend, int divisor, int *remainder)
{
    if (remainder == NULL || divisor == 0) {
        return 0;
    }

    if (dividend == INT_MIN && divisor == -1) {
        *remainder = 0;
        return 1;
    }

    *remainder = dividend % divisor;
    return 1;
}

static int read_int(const char *prompt, int *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    long parsed;
    size_t length;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    length = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'length<sizeof(buffer)' is not redundant
     */
    while (length < sizeof buffer && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == sizeof buffer || buffer[length] != '\n') {
        /* Possible weaknesses found:
         *  The scope of the variable 'ch' can be reduced. [variableScope]
         */
        int ch;

        /* Possible weaknesses found:
         *  Array index out of bounds
         *  Either the condition 'length<sizeof(buffer)' is redundant or the array 'buffer[128]' is accessed at index 128, which is out of bounds. [arrayIndexOutOfBoundsCond]
         */
        if (length == 0 || buffer[length] != '\0' || !feof(stdin)) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stdin)) {
                return 0;
            }

            return 0;
        }
    } else {
        buffer[length] = '\0';
    }

    errno = 0;
    parsed = strtol(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int main(void)
{
    int dividend;
    int divisor;
    int remainder;

    if (!read_int("Enter the dividend: ", &dividend) ||
        !read_int("Enter the divisor: ", &divisor)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_remainder(dividend, divisor, &remainder)) {
        fputs("The divisor must not be zero.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Remainder: %d\n", remainder) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}