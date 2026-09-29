#include <stdio.h>

double harmonic_sum(int n) {
    if (n <= 0) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) == 1 && n > 0) {
        double result = harmonic_sum(n - 1);
        printf("The harmonic sum of %d-1 is: %f\n", n, result);
    } else {
        printf("Invalid input. Please enter a positive integer.\n");
    }
    return 0;
}