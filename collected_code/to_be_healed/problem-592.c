#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
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
    int n;
    printf("Enter n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    int result = sumOfProductOfBinomialCoefficients(n);
    printf("Sum of product of binomial coefficients: %d\n", result);
    
    return 0;
}