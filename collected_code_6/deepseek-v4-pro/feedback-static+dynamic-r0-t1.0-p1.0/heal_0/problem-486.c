#include <stdio.h>
#include <stdlib.h>

double binomial_coefficient(int n, int k) {
    if (k < 0 || n < 0 || k > n) {
        return 0.0;
    }
    if (k == 0 || k == n) {
        return 1.0;
    }
    if (k > n - k) {
        k = n - k;
    }
    double result = 1.0;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

double binomial_probability(int n, int k, double p) {
    if (n < 0 || k < 0 || k > n || p < 0.0 || p > 1.0) {
        return -1.0;
    }
    double coeff = binomial_coefficient(n, k);
    double prob = 1.0;
    for (int i = 0; i < k; ++i) {
        prob *= p;
    }
    for (int i = 0; i < n - k; ++i) {
        prob *= (1.0 - p);
    }
    return coeff * prob;
}

int main(void) {
    int n = 10;
    int k = 3;
    double p = 0.5;
    
    double result = binomial_probability(n, k, p);
    if (result < 0.0) {
        fprintf(stderr, "Invalid input parameters\n");
        return EXIT_FAILURE;
    }
    
    printf("P(X = %d) = %f\n", k, result);
    return EXIT_SUCCESS;
}