#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    fputs(prompt, stdout);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtol(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
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

    printf("Remainder: %d\n", remainder);
    return EXIT_SUCCESS;
}