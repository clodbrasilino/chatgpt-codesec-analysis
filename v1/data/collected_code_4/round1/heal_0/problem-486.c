#include <stdio.h>

long long int factorial(int num) {
    long long int fact = 1;
    for(int i = 2; i <= num; ++i) {
        fact *= i;
    }
    return fact;
}

double binomialProbability(int n, int k, double p) {
    double result;
    long long int n_fact = factorial(n);
    long long int k_fact = factorial(k);
    long long int nk_fact = factorial(n-k);

    double term1 = (double)n_fact/(k_fact * nk_fact);
    double term2 = 1;
    for(int i = 0; i < k; i++){
        term2 *= p;
    }
    double term3 = 1;
    for(int i = 0; i < n-k; i++){
        term3 *= (1-p);
    }
    result = term1 * term2 * term3;
    return result;
}

int main() {
    int n = 5;
    int k = 3;
    double p = 0.5;

    double result = binomialProbability(n, k, p);
    printf("The binomial probability is: %.3f\n", result);
    return 0;
}