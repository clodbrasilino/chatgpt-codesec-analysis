#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int binomial_probability(unsigned int n, unsigned int k, double p,
                                double *result)
{
    double log_probability;

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

    errno = 0;
    log_probability = lgamma((double)n + 1.0)
                    - lgamma((double)k + 1.0)
                    - lgamma((double)(n - k) + 1.0)
                    + (double)k * log(p)
                    + (double)(n - k) * log1p(-p);

    if (errno != 0 || !isfinite(log_probability)) {
        return -1;
    }

    errno = 0;
    *result = exp(log_probability);

    if (errno == ERANGE && *result == 0.0) {
        errno = 0;
        return 0;
    }

    if (errno != 0 || !isfinite(*result)) {
        return -1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long n_value;
    unsigned long k_value;
    double p;
    double probability;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <n> <k> <p>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n_value = strtoul(argv[1], &end, 10);
    if (errno != 0 || end == argv[1] || *end != '\0' ||
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'UINT_MAX'
         *  'UINT_MAX' undeclared (first use in this function)
         */
        n_value > (unsigned long)UINT_MAX) {
        fprintf(stderr, "Invalid n\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    k_value = strtoul(argv[2], &end, 10);
    if (errno != 0 || end == argv[2] || *end != '\0' ||
        /* Possible weaknesses found:
         *  use of undeclared identifier 'UINT_MAX'
         */
        k_value > (unsigned long)UINT_MAX) {
        fprintf(stderr, "Invalid k\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    p = strtod(argv[3], &end);
    if (errno != 0 || end == argv[3] || *end != '\0' || !isfinite(p)) {
        fprintf(stderr, "Invalid probability\n");
        return EXIT_FAILURE;
    }

    if (binomial_probability((unsigned int)n_value, (unsigned int)k_value,
                             p, &probability) != 0) {
        fprintf(stderr, "Unable to compute binomial probability\n");
        return EXIT_FAILURE;
    }

    printf("%.17g\n", probability);
    return EXIT_SUCCESS;
}