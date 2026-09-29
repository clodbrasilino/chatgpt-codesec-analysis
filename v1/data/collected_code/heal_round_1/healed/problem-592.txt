#include <stdio.h>

int factorial(int n) {
    return (n == 0 || n == 1) ? 1 : (n * factorial(n - 1));
}

int binomialCoefficient(int n, int k) {
    int numerator = factorial(n);
    int denominator = factorial(k) * factorial(n - k);
    return numerator / denominator;
}

int sumOfProductOfBinomialCoefficients(int n) {
    int sum = 0;
    for (int k = 0; k <= n; k++) {
        int coefficient = binomialCoefficient(n, k);
        sum += coefficient * coefficient;
    }
    return sum;
}

int main() {
    int n = 0;
    printf("Enter n: ");
    scanf("%d", &n);
    
    int result = sumOfProductOfBinomialCoefficients(n);
    printf("Sum of product of binomial coefficients: %d\n", result);
    
    return 0;
}