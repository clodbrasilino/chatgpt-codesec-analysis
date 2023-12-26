#include <stdio.h>

// Function to calculate the factorial
int factorial(int num) {
    int fact = 1;
    for (int i = 1; i <= num; i++) {
        fact = fact * i;
    }
    return fact;
}

// Function to calculate the entringer number e(n, k)
int findEntringerNumber(int n, int k) {
    // Calculate the numerator and denominator
    int numerator = factorial(n + k - 1);
    int denominator = factorial(n) * factorial(k - 1);

    // Calculate and return the entringer number
    return numerator / denominator;
}

// Main function
int main() {
    int n, k;
    printf("Enter the values of n and k: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'k' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d %d", &n, &k);
    printf("Entringer number e(%d, %d) = %d\n", n, k, findEntringerNumber(n, k));
    
    return 0;
}