#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int factorial_digit_count(unsigned long long n, unsigned long long *count)
{
    long double logarithm;

    if (count == NULL) {
        return -1;
    }

    if (n < 2) {
        *count = 1;
        return 0;
    }

    errno = 0;
    logarithm = lgammal((long double)n + 1.0L) / logl(10.0L);

    if (errno != 0 || !isfinite(logarithm) ||
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'ULLONG_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'ULLONG_MAX'
         */
        logarithm > (long double)ULLONG_MAX - 1.0L) {
        return -1;
    }

    *count = (unsigned long long)floorl(logarithm) + 1ULL;
    return 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    unsigned long long n;
    unsigned long long digits;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (factorial_digit_count(n, &digits) != 0) {
        fputs("Unable to calculate digit count\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%llu\n", digits);
    return EXIT_SUCCESS;
}