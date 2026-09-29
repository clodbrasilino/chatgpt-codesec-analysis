#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) return 0.0;
    if (k == 0 || k == n) return 1.0;
    
    k = (k > n - k) ? n - k : k;
    
    double result = 1.0;
    for (int i = 0; i < k; i++) {
        result *= (double)(n - i) / (double)(i + 1);
    }
    
    return result;
}

double binomial_probability(int n, int k, double p) {
    if (p < 0.0 || p > 1.0) {
        fprintf(stderr, "Error: probability must be between 0 and 1\n");
        exit(EXIT_FAILURE);
    }
    
    if (n < 0) {
        fprintf(stderr, "Error: number of trials must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    
    if (k < 0 || k > n) {
        return 0.0;
    }
    
    double coeff = binomial_coefficient(n, k);
    double prob = coeff * pow(p, k) * pow(1.0 - p, n - k);
    
    return prob;
}

int main(void) {
    int n = 10;
    int k = 3;
    double p = 0.5;
    
    double result = binomial_probability(n, k, p);
    printf("Binomial probability P(X = %d) for n = %d, p = %.2f: %.6f\n", k, n, p, result);
    
    n = 20;
    k = 7;
    p = 0.3;
    result = binomial_probability(n, k, p);
    printf("Binomial probability P(X = %d) for n = %d, p = %.2f: %.6f\n", k, n, p, result);
    
    n = 5;
    k = 5;
    p = 0.8;
    result = binomial_probability(n, k, p);
    printf("Binomial probability P(X = %d) for n = %d, p = %.2f: %.6f\n", k, n, p, result);
    
    return 0;
}