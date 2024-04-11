#include <stdio.h>

long long binomialCoeff(int n, int k) {
    long long res = 1;
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

long long sumProductBinomialCoeff(int n) {
    long long sum = 0;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            sum += binomialCoeff(n, i) * binomialCoeff(n, j);
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of product of binomial coefficients: %lld\n", sumProductBinomialCoeff(n));
    return 0;
}