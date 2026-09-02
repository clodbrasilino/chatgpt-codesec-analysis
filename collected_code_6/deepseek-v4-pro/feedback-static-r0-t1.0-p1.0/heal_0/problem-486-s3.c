#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double compute_binomial_probability(int n, int k, double p) {
    if (n < 0 || k < 0 || k > n || p < 0.0 || p > 1.0) {
        return -1.0L;
    }

    long double log_result = 0.0L;
    int i;

    for (i = 1; i <= k; i++) {
        log_result += logl((long double)(n - k + i) / (long double)i);
    }

    if (k > 0) {
        log_result += (long double)k * logl((long double)p);
    }

    if (n - k > 0) {
        log_result += (long double)(n - k) * logl((long double)(1.0L - p));
    }

    if (fabsl(log_result) > 745.0L) {
        if (log_result > 0.0L) {
            return INFINITY;
        } else {
            return 0.0L;
        }
    }

    return expl(log_result);
}

int main(void) {
    int n = 10;
    int k = 3;
    double p = 0.5;
    long double probability;

    probability = compute_binomial_probability(n, k, p);

    if (probability < 0.0L) {
        fprintf(stderr, "Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    printf("Binomial probability P(X=%d) for n=%d, p=%.2f: %.12Lf\n",
           k, n, p, probability);

    return EXIT_SUCCESS;
}