#include <stdio.h>
#include <stdlib.h>

long sum_of_squares_even(long n) {
    long sum = 0;
    for (long i = 1; i <= n; ++i) {
        sum += (2 * i) * (2 * i);
    }
    return sum;
}

int main() {
    long n;
    printf("Enter the number of first even natural numbers: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number must be a non-negative integer\n");
        return EXIT_FAILURE;
    }

    long result = sum_of_squares_even(n);
    printf("Sum of squares of first %ld even natural numbers: %ld\n", n, result);
    return EXIT_SUCCESS;
}