#include <stdio.h>
#include <math.h>

double factorial(int n) {
    double result = 1.0;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double binomial_coefficient(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

double binomial_probability(int n, int k, double p) {
    if (p < 0.0 || p > 1.0) {
        return -1.0;
    }
    double q = 1.0 - p;
    double coefficient = binomial_coefficient(n, k);
    return coefficient * pow(p, k) * pow(q, n - k);
}

int main() {
    int n = 10;
    int k = 3;
    double p = 0.5;

    double probability = binomial_probability(n, k, p);

    if (probability >= 0.0) {
        printf("Binomial Probability: %.8f\n", probability);
    } else {
        fprintf(stderr, "Invalid probability value.\n");
    }

    return 0;
}