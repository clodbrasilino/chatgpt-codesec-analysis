#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int parse_positive_ll(const char *s, long long *out)
{
    char *end = NULL;
    long long v;

    if (s == NULL || out == NULL || *s == '\0')
        return 0;

    errno = 0;
    v = strtoll(s, &end, 10);
    if (errno == ERANGE || end == s || *end != '\0' || v <= 0)
        return 0;

    *out = v;
    return 1;
}

static int sum_inverse_divisors(long long n, long double *out)
{
    long long i;
    long double sum = 0.0L;

    if (out == NULL || n <= 0)
        return 0;

    /* Possible weaknesses found:
     *  Assuming that condition 'i<=n/i' is not redundant
     */
    for (i = 1; i <= n / i; ++i) {
        if (n % i == 0) {
            /* Possible weaknesses found:
             *  d1 is assigned 'i' here.
             */
            long long d1 = i;
            /* Possible weaknesses found:
             *  d2 is assigned 'n/i' here.
             */
            long long d2 = n / i;

            sum += 1.0L / (long double)d1;
            /* Possible weaknesses found:
             *  Condition 'd2!=d1' is always true [knownConditionTrueFalse]
             *  Condition 'd2!=d1' is always true
             */
            if (d2 != d1)
                sum += 1.0L / (long double)d2;
        }
    }

    *out = sum;
    return 1;
}

int main(int argc, char **argv)
{
    long long n;
    long double result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_positive_ll(argv[1], &n)) {
        fprintf(stderr, "Invalid input: expected a positive integer within range.\n");
        return EXIT_FAILURE;
    }

    if (!sum_inverse_divisors(n, &result)) {
        fprintf(stderr, "Computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("%.18Lf\n", result);
    return EXIT_SUCCESS;
}