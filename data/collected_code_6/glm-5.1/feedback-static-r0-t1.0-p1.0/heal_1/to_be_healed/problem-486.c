#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

double compute_combinations(int n, int k) {
    if (k < 0 || k > n) return 0.0;
    if (k == 0 || k == n) return 1.0;
    if (k > n - k) k = n - k;
    double res = 1.0;
    for (int i = 1; i <= k; i++) {
        res *= (n - i + 1);
        res /= i;
    }
    return res;
}

double binomial_probability(int n, int k, double p) {
    if (n < 0 || k < 0 || k > n || p < 0.0 || p > 1.0) {
        /* Possible weaknesses found:
         *  'EINVAL' undeclared (first use in this function)
         *  'errno' undeclared (first use in this function)
         *  use of undeclared identifier 'errno'
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'EINVAL'
         */
        errno = EINVAL;
        return NAN;
    }
    double comb = compute_combinations(n, k);
    return comb * pow(p, k) * pow(1.0 - p, n - k);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <n> <k> <p>\n", argv[0]);
        /* Possible weaknesses found:
         *  'EINVAL' undeclared (first use in this function)
         *  use of undeclared identifier 'EINVAL'
         */
        return EINVAL;
    }
    char *endptr_n, *endptr_k, *endptr_p;
    long n_val = strtol(argv[1], &endptr_n, 10);
    long k_val = strtol(argv[2], &endptr_k, 10);
    double p_val = strtod(argv[3], &endptr_p);
    if (*endptr_n != '\0' || *endptr_k != '\0' || *endptr_p != '\0' || n_val < 0 || k_val < 0 || p_val < 0.0 || p_val > 1.0) {
        fprintf(stderr, "Invalid input. Ensure n >= 0, k >= 0, 0 <= p <= 1\n");
        /* Possible weaknesses found:
         *  use of undeclared identifier 'EINVAL'
         */
        return EINVAL;
    }
    double prob = binomial_probability((int)n_val, (int)k_val, p_val);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'errno'
     *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
     *  use of undeclared identifier 'EINVAL'
     *  'errno' undeclared (first use in this function)
     */
    if (errno == EINVAL || isnan(prob)) {
        fprintf(stderr, "Computation error: Invalid parameters for binomial probability.\n");
        /* Possible weaknesses found:
         *  use of undeclared identifier 'EINVAL'
         */
        return EINVAL;
    }
    printf("%.15e\n", prob);
    return 0;
}