#include <stdio.h>

unsigned long long factorial(unsigned int n) {
    unsigned long long fact = 1;
    for (unsigned int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

unsigned long long catalanNumber(unsigned int n) {
    unsigned long long numerator = factorial(2 * n);
    unsigned long long denominator = factorial(n + 1) * factorial(n);

    return numerator / denominator;
}

int main() {
    unsigned int n = 0;
    printf("Enter the value of n: ");
    scanf("%u", &n);
    printf("The %uth Catalan number is: %llu", n, catalanNumber(n));

    return 0;
}