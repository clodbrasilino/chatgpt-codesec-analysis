#include <stdio.h>

long long int binomialCoefficient(int n, int k) {
    long long int res = 1;
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

long long int sumEvenIndexBinomialCoefficients(int n) {
    long long int sum = 0;
    for (int i = 0; i <= n; i += 2) {
        sum += binomialCoefficient(n, i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a value for n: ");
    scanf("%d", &n);
    long long int result = sumEvenIndexBinomialCoefficients(n);
    printf("Sum of even index binomial coefficients: %lld", result);
    return 0;
}