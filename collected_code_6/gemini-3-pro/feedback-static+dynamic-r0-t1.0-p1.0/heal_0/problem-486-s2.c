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
    
    double result = 1.0;
    for (int i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }
    
    return result;
}

double compute_binomial_probability(int n, int k, double p) {
    if (n < 0 || k < 0 || k > n || p < 0.0 || p > 1.0) {
        return -1.0;
    }
    
    double combinations = compute_combinations(n, k);
    double probability = combinations * pow(p, k) * pow(1.0 - p, n - k);
    
    return probability;
}

int main() {
    int n = 10;
    int k = 5;
    double p = 0.5;
    
    double result = compute_binomial_probability(n, k, p);
    
    if (result >= 0.0) {
        printf("Binomial probability for n=%d, k=%d, p=%.2f is: %.6f\n", n, k, p, result);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Invalid input parameters for binomial probability computation.\n");
        return EXIT_FAILURE;
    }
}