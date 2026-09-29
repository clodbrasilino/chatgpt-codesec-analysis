#include <stdio.h>

// Function to find the factorial of a number
unsigned long long factorial(unsigned int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

// Function to calculate the nth Catalan number
unsigned long long catalanNumber(unsigned int n) {
    // Calculate the numerator and denominator
    unsigned long long numerator = factorial(2 * n);
    unsigned long long denominator = factorial(n + 1) * factorial(n);

    // Return the nth catalan number
    return numerator / denominator;
}

int main() {
    unsigned int n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%u", &n);

    // Calculate and print the nth catalan number
    printf("The %uth Catalan number is: %llu", n, catalanNumber(n));

    return 0;
}