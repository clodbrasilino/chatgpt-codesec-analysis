#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double factorial(int n) {
    long double result = 1.0L;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

long double binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0.0L;
    }
    int min_k = k < (n - k) ? k : (n - k);
    long double result = 1.0L;
    for (int i = 1; i <= min_k; i++) {
        result *= (long double)(n - min_k + i) / i;
    }
    return result;
}

long double binomial_probability(int n, int k, double p) {
    if (n < 0 || k < 0 || k > n || p < 0.0 || p > 1.0) {
        return NAN;
    }
    long double coeff = binomial_coefficient(n, k);
    long double p_val = pow(p, k);
    long double q_val = pow(1.0 - p, n - k);
    return coeff * p_val * q_val;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <n> <k> <p>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_n, *endptr_k, *endptr_p;
    long n_val = strtol(argv[1], &endptr_n, 10);
    long k_val = strtol(argv[2], &endptr_k, 10);
    double p_val = strtod(argv[3], &endptr_p);

    if (*endptr_n != '\0' || *endptr_k != '\0' || *endptr_p != '\0' || n_val < 0 || k_val < 0) {
        fprintf(stderr, "Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    long double prob = binomial_probability((int)n_val, (int)k_val, p_val);
    if (isnan(prob)) {
        fprintf(stderr, "Math domain error\n");
        return EXIT_FAILURE;
    }

    printf("%.15Lf\n", prob);
    return EXIT_SUCCESS;
}