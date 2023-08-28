#include<stdio.h>

long long int binomialCoeff(int n, int k) {
    long long int res = 1;

    // Calculate value of [n*(n-1)*(n-2)*...*(n-k+1)] / [k*(k-1)*(k-2)*...*1]
    for (int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
}

long long int sumOfBinomialCoeffSquares(int n) {
    long long int sum = 0;

    // Calculate square of binomial coefficients and add them to the sum
    for (int k = 0; k <= n; k++) {
        long long int coeff = binomialCoeff(n, k);
        sum += (coeff * coeff);
    }

    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    long long int sum = sumOfBinomialCoeffSquares(n);
    printf("Sum of squares of binomial coefficients for n=%d is %lld", n, sum);

    return 0;
}