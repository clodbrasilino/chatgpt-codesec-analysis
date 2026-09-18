#include <stdio.h>

unsigned long factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

unsigned long binomialCoeff(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

unsigned long sumEvenBinomialCoeff(int n) {
    unsigned long sum = 0;
    for (int k = 0; k <= n; k += 2)
        sum += binomialCoeff(n, k);
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Number cannot be negative!\n");
        return 1;
    }
    printf("Sum of even index binomial coefficients: %lu\n", sumEvenBinomialCoeff(n));
    return 0;
}