#include <stdio.h>
#include <stdlib.h>

unsigned long long binomialCoefficient(int n, int k) {
    unsigned long long result = 1;
    if (k > n - k) {
        k = n - k;
    }
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

unsigned long long sumOfSquaresOfBinomialCoefficients(int n) {
    unsigned long long sum = 0;
    for (int k = 0; k <= n; k++) {
        unsigned long long coeff = binomialCoefficient(n, k);
        sum += coeff * coeff;
    }
    return sum;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%llu\n", sumOfSquaresOfBinomialCoefficients(n));
    return EXIT_SUCCESS;
}