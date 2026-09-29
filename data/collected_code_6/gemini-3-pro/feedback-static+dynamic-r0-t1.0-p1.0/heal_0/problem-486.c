#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double compute_combinations(int n, int k) {
    if (k < 0 || k > n) {
        return 0.0;
    }
    if (k == 0 || k == n) {
        return 1.0;
    }
    if (k > n / 2) {
        k = n - k;
    }
    double c = 1.0;
    for (int i = 1; i <= k; ++i) {
        c = c * (n - i + 1) / i;
    }
    return c;
}

double binomial_probability(int n, int k, double p) {
    if (n < 0 || k < 0 || k > n || p < 0.0 || p > 1.0) {
        return -1.0;
    }
    double combinations = compute_combinations(n, k);
    double probability = combinations * pow(p, k) * pow(1.0 - p, n - k);
    return probability;
}

int main(void) {
    int n, k;
    double p;

    if (scanf("%d %d %lf", &n, &k, &p) != 3) {
        return EXIT_FAILURE;
    }

    double result = binomial_probability(n, k, p);
    if (result < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%.6f\n", result);

    return EXIT_SUCCESS;
}