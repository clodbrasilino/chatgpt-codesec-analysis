#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int factorial_digit_count(unsigned long long n,
                                 unsigned long long *count)
{
    long double logarithm;
    long double log10_value;

    if (count == NULL) {
        return -1;
    }

    if (n < 2ULL) {
        *count = 1ULL;
        return 0;
    }

    errno = 0;
    log10_value = logl(10.0L);

    if (errno != 0 || !isfinite(log10_value) || log10_value <= 0.0L) {
        return -1;
    }

    errno = 0;
    logarithm = lgammal((long double)n + 1.0L) / log10_value;

    if (errno != 0 || !isfinite(logarithm) || logarithm < 0.0L ||
        logarithm > (long double)ULLONG_MAX - 1.0L) {
        return -1;
    }

    *count = (unsigned long long)floorl(logarithm) + 1ULL;
    return 0;
}

static int read_number(unsigned long long *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (value == NULL) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    if (input[0] == '\0') {
        return -1;
    }

    for (end = input; *end != '\0' && *end != '\n'; ++end) {
    }

    if (*end == '\n') {
        *end = '\0';
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
            return -1;
        }
    }

    end = input;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '-' || *end == '\0') {
        return -1;
    }

    errno = 0;
    {
        char *parse_end;
        unsigned long long result = strtoull(end, &parse_end, 10);

        if (errno == ERANGE || parse_end == end) {
            return -1;
        }

        while (isspace((unsigned char)*parse_end)) {
            ++parse_end;
        }

        if (*parse_end != '\0') {
            return -1;
        }

        *value = result;
    }

    return 0;
}

int main(void)
{
    unsigned long long n;
    unsigned long long digits;

    if (read_number(&n) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (factorial_digit_count(n, &digits) != 0) {
        fputs("Unable to calculate digit count\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", digits) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}