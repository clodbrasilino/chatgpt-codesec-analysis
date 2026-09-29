#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

unsigned long long calculate_combinations(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n / 2) {
        k = n - k;
    }
    
    unsigned long long c = 1;
    for (int i = 1; i <= k; i++) {
        c = c * (n - i + 1);
        c = c / i;
    }
    return c;
}

double compute_binomial_probability(int n, int k, double p) {
    if (n < 0 || k < 0 || k > n || p < 0.0 || p > 1.0) {
        return -1.0;
    }
    
    unsigned long long combinations = calculate_combinations(n, k);
    double probability = (double)combinations * pow(p, k) * pow(1.0 - p, n - k);
    
    return probability;
}

int main(void) {
    int n, k;
    double p, result;
    
    if (scanf("%d %d %lf", &n, &k, &p) != 3) {
        fprintf(stderr, "Invalid input format.\n");
        return EXIT_FAILURE;
    }
    
    result = compute_binomial_probability(n, k, p);
    
    if (result < 0.0) {
        fprintf(stderr, "Invalid parameters for binomial probability.\n");
        return EXIT_FAILURE;
    }
    
    printf("%.6f\n", result);
    
    return EXIT_SUCCESS;
}