#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int first_factorial_digit(unsigned long long n)
{
    if (n < 2ULL) {
        return 1;
    }

    double logarithm = lgamma((double)n + 1.0) / log(10.0);

    if (!isfinite(logarithm)) {
        return -1;
    }

    double fractional_part = logarithm - floor(logarithm);
    int digit = (int)floor(pow(10.0, fractional_part) + 1e-12);

    return digit > 9 ? 9 : digit;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    char *end = NULL;
    errno = 0;
    unsigned long long n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    int digit = first_factorial_digit(n);

    if (digit < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}