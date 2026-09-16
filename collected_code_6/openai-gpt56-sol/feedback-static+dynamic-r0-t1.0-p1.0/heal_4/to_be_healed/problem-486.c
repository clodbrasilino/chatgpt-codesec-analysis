#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int binomial_probability(unsigned int n, unsigned int k, double p,
                                double *result)
{
    unsigned int i;
    long double probability;

    if (result == NULL || !isfinite(p) || p < 0.0 || p > 1.0 || k > n) {
        return -1;
    }

    if (p == 0.0) {
        *result = (k == 0U) ? 1.0 : 0.0;
        return 0;
    }

    if (p == 1.0) {
        *result = (k == n) ? 1.0 : 0.0;
        return 0;
    }

    if (k > n - k) {
        k = n - k;
        p = 1.0 - p;
    }

    probability = powl(1.0L - (long double)p, (long double)n);

    for (i = 1U; i <= k; ++i) {
        probability *=
            ((long double)(n - k + i) / (long double)i) *
            ((long double)p / (1.0L - (long double)p));
    }

    if (!isfinite(probability) || probability < 0.0L || probability > 1.0L) {
        return -1;
    }

    *result = (double)probability;
    return 0;
}

static int parse_unsigned(const char *text, unsigned int *value)
{
    char *end;
    unsigned long parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoul(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0' || parsed > UINT_MAX) {
        return -1;
    }

    *value = (unsigned int)parsed;
    return 0;
}

static int parse_probability(const char *text, double *value)
{
    char *end;
    double parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0' ||
        !isfinite(parsed) || parsed < 0.0 || parsed > 1.0) {
        return -1;
    }

    *value = parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned int n;
    unsigned int k;
    double p;
    double result;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <n> <k> <p>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_unsigned(argv[1], &n) != 0 ||
        parse_unsigned(argv[2], &k) != 0 ||
        parse_probability(argv[3], &p) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (binomial_probability(n, k, p, &result) != 0) {
        fputs("Unable to compute binomial probability\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}