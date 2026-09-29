#include <stdio.h>

long long factorial(int n) {
    long long fact = 1;
    for(int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

long long binomialCoeff(int n, int k) {
    long long res = 1;
    if (k > n - k) {
        k = n - k;
    }
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

long long sumOfSquares(int n) {
    long long sum = 0;
    for(int i = 0; i <= n; i++) {
        long long binom = binomialCoeff(n, i);
        sum += binom * binom;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of squares of binomial coefficients: %lld\n", sumOfSquares(n));
    return 0;
}