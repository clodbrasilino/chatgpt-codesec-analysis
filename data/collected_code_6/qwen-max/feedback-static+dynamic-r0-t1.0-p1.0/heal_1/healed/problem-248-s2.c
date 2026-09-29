#include <stdio.h>
#include <limits.h>

double harmonic_sum(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; ++i) {
        sum += 1.0 / i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > INT_MAX) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    double result = harmonic_sum(n);
    printf("Harmonic sum of 1 to %d is: %f\n", n, result);

    return 0;
}