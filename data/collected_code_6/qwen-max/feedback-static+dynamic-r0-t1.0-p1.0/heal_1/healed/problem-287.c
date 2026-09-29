#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long sum_of_squares_even(long n) {
    if (n < 0 || n > INT_MAX / 2) {
        fprintf(stderr, "Input out of range\n");
        exit(EXIT_FAILURE);
    }
    long sum = 0;
    for (long i = 1; i <= n; ++i) {
        long temp = 2 * i;
        if (sum + temp * temp < sum) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
        sum += temp * temp;
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