#include <stdio.h>
#include <stdlib.h>

double sum_of_inverse_divisors(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            sum += 1.0 / i;
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    double result = sum_of_inverse_divisors(n);
    printf("The sum of the inverse of divisors of %d is: %.2f\n", n, result);

    return EXIT_SUCCESS;
}