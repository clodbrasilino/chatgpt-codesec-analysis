#include <stdio.h>
#include <stdlib.h>

double sum_of_inverse_divisors(int n) {
    if (n <= 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            sum += 1.0 / i;
        }
    }
    return sum;
}

int main(void) {
    int number;
    printf("Enter a positive integer: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    double result = sum_of_inverse_divisors(number);
    printf("Sum of inverse of divisors: %.6f\n", result);

    return EXIT_SUCCESS;
}