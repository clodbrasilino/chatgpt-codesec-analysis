#include<stdio.h>

long long int binomialCoeff(int n, int k) {
    long long int res = 1;

    for (int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
}

long long int sumOfBinomialCoeffSquares(int n) {
    long long int sum = 0;

    for (int k = 0; k <= n; k++) {
        long long int coeff = binomialCoeff(n, k);
        sum += (coeff * coeff);
    }

    return sum;
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    long long int sum = sumOfBinomialCoeffSquares(n);
    printf("Sum of squares of binomial coefficients for n=%d is %lld", n, sum);

    return 0;
}