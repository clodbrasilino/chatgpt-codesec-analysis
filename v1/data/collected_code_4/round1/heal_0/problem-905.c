#include <stdio.h>

long long factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

long long binomialCoefficient(int n, int k) {
    long long res = factorial(n) / (factorial(k) * factorial(n - k));
    return res;
}

long long sumOfSquaresOfBinomialCoefficients(int n) {
    long long sum = 0;
    int i;

    for (i = 0; i <= n; i++) {
        long long bc = binomialCoefficient(n, i);
        sum += bc * bc;
    }

    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if(n < 0) {
        printf("Invalid input. Number must be non-negative.\n");
        return 1;
    }
    
    long long result = sumOfSquaresOfBinomialCoefficients(n);
    printf("Sum of squares of binomial coefficients: %lld\n", result);

    return 0;
}