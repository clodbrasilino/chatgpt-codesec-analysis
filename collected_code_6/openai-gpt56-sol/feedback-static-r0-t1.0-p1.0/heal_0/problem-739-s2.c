#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int smallest_triangular_index(unsigned int digits, unsigned long long *index)
{
    long double threshold;
    long double estimate;
    unsigned long long k;

    if (index == NULL || digits == 0U || digits > 38U) {
        return -1;
    }

    threshold = powl(10.0L, (long double)(digits - 1U));
    if (!isfinite(threshold)) {
        return -1;
    }

    estimate = ceill((sqrtl(1.0L + 8.0L * threshold) - 1.0L) / 2.0L);
    if (!isfinite(estimate) || estimate < 1.0L ||
        estimate > (long double)ULLONG_MAX) {
        return -1;
    }

    k = (unsigned long long)estimate;

    while ((long double)k * ((long double)k + 1.0L) / 2.0L < threshold) {
        if (k == ULLONG_MAX) {
            return -1;
        }
        ++k;
    }

    while (k > 1ULL &&
           (long double)(k - 1ULL) * (long double)k / 2.0L >= threshold) {
        --k;
    }

    *index = k;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end;
    unsigned long value;
    unsigned long long index;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number-of-digits>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        value == 0UL || value > 38UL) {
        fprintf(stderr, "Invalid number of digits\n");
        return EXIT_FAILURE;
    }

    if (smallest_triangular_index((unsigned int)value, &index) != 0) {
        fprintf(stderr, "Unable to compute the index\n");
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", index) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}