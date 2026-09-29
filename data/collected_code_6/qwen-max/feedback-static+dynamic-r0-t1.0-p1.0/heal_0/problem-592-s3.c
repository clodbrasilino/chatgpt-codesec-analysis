#include <stdio.h>

long long binomialCoefficient(int n, int k) {
    long long C[n + 1][k + 1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= k && j <= i; ++j) {
            if (j == 0 || j == i)
                C[i][j] = 1;
            else
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    return C[n][k];
}

long long sumOfBinomialProduct(int n, int m) {
    long long sum = 0;
    for (int k = 0; k <= n; ++k) {
        sum += binomialCoefficient(n, k) * binomialCoefficient(m, k);
    }
    return sum;
}

int main() {
    int n = 5;
    int m = 3;
    long long result = sumOfBinomialProduct(n, m);
    printf("Sum of product of binomial coefficients: %lld\n", result);
    return 0;
}