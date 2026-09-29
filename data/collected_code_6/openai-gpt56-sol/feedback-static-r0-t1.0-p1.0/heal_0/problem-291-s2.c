#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int multiply_checked(unsigned long long a,
                            unsigned long long b,
                            unsigned long long *result)
{
    if (result == NULL || (b != 0ULL && a > ULLONG_MAX / b)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int add_checked(unsigned long long a,
                       unsigned long long b,
                       unsigned long long *result)
{
    if (result == NULL || a > ULLONG_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int count_painting_ways(unsigned int n,
                               unsigned int k,
                               unsigned long long *ways)
{
    unsigned long long same;
    unsigned long long different;
    unsigned long long total;
    unsigned int i;

    if (ways == NULL) {
        return 0;
    }

    if (n == 0U) {
        *ways = 1ULL;
        return 1;
    }

    if (k == 0U) {
        *ways = 0ULL;
        return 1;
    }

    if (n == 1U) {
        *ways = (unsigned long long)k;
        return 1;
    }

    same = (unsigned long long)k;

    if (!multiply_checked((unsigned long long)k,
                          (unsigned long long)(k - 1U),
                          &different)) {
        return 0;
    }

    for (i = 3U; i <= n; ++i) {
        unsigned long long next_same = different;
        unsigned long long next_different;

        if (!add_checked(same, different, &total) ||
            !multiply_checked(total,
                              (unsigned long long)(k - 1U),
                              &next_different)) {
            return 0;
        }

        same = next_same;
        different = next_different;
    }

    return add_checked(same, different, ways);
}

int main(void)
{
    unsigned int n;
    unsigned int k;
    unsigned long long ways;
    int result;

    errno = 0;
    result = scanf("%u %u", &n, &k);

    if (result != 2 || errno != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!count_painting_ways(n, k, &ways)) {
        fprintf(stderr, "Result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", ways);
    return EXIT_SUCCESS;
}