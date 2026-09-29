#include <stdio.h>

double harmonic_sum(int n) {
    if (n <= 1) return 1.0;
    return 1.0 / n + harmonic_sum(n - 1);
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n > 0) {
        double result = harmonic_sum(n);
        printf("Harmonic sum of %d-1 is: %f\n", n, result);
    } else {
        printf("Please enter a positive integer.\n");
    }

    return 0;
}