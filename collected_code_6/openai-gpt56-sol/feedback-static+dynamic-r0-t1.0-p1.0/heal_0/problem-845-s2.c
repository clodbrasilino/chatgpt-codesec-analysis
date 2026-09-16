#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int factorial_digit_count(unsigned long long n, unsigned long long *count)
{
    long double digits;

    if (count == NULL) {
        return -1;
    }

    if (n < 2ULL) {
        *count = 1ULL;
        return 0;
    }

    errno = 0;
    digits = floorl(lgammal((long double)n + 1.0L) / logl(10.0L)) + 1.0L;

    if (errno != 0 || !isfinite(digits) || digits < 1.0L ||
        digits > (long double)ULLONG_MAX) {
        return -1;
    }

    *count = (unsigned long long)digits;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long n;
    unsigned long long count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (factorial_digit_count(n, &count) != 0) {
        fprintf(stderr, "Unable to calculate digit count\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", count);
    return EXIT_SUCCESS;
}