#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int binomial_probability(unsigned long long n,
                                unsigned long long k,
                                double p,
                                double *result)
{
    long double log_probability;
    long double probability;

    if (result == NULL || k > n || !isfinite(p) || p < 0.0 || p > 1.0) {
        return -1;
    }

    if (p == 0.0) {
        *result = (k == 0ULL) ? 1.0 : 0.0;
        return 0;
    }

    if (p == 1.0) {
        *result = (k == n) ? 1.0 : 0.0;
        return 0;
    }

    log_probability =
        lgammal((long double)n + 1.0L) -
        lgammal((long double)k + 1.0L) -
        lgammal((long double)(n - k) + 1.0L) +
        (long double)k * logl((long double)p) +
        (long double)(n - k) * log1pl(-(long double)p);

    probability = expl(log_probability);

    if (!isfinite(probability) ||
        probability < 0.0L ||
        probability > 1.0L) {
        return -1;
    }

    *result = (double)probability;
    return 0;
}

static int parse_unsigned_long_long(const char *text,
                                    unsigned long long *value)
{
    char *end = NULL;
    unsigned long long parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno == ERANGE ||
        end == text ||
        *end != '\0' ||
        !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(int argc, char *const argv[const])
{
    unsigned long long n;
    unsigned long long k;
    double p;
    double probability;

    if (argc != 4) {
        fprintf(stderr,
                "Usage: %s <trials> <successes> <probability>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_unsigned_long_long(argv[1], &n) != 0 ||
        parse_unsigned_long_long(argv[2], &k) != 0 ||
        parse_double(argv[3], &p) != 0) {
        fprintf(stderr, "Invalid argument.\n");
        return EXIT_FAILURE;
    }

    if (binomial_probability(n, k, p, &probability) != 0) {
        fprintf(stderr, "Unable to compute binomial probability.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", probability) < 0) {
        fprintf(stderr, "Output error.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}