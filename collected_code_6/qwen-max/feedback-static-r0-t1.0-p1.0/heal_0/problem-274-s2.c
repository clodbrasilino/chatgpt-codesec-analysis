#include <stdio.h>
#include <stdlib.h>

long long binomialCoefficient(int n, int k) {
    long long res = 1;
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

long long sumEvenIndexBinomialCoefficients(int n) {
    long long sum = 0;
    for (int i = 0; i <= n; i += 2) {
        sum += binomialCoefficient(n, i);
    }
    return sum;
}

int main() {
    int n = 8;
    printf("Sum of even index binomial coefficients: %lld\n", sumEvenIndexBinomialCoefficients(n));
    return 0;
}