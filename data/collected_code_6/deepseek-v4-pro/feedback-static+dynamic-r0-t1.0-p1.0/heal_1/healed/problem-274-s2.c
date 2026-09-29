#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long long sum_even_binomial_coefficients(int n) {
    if (n < 0 || n > 62) {
        return -1;
    }

    unsigned long long total = 1ULL << n;
    unsigned long long sum_even = (total + ((n % 2 == 0) ? 1 : 0)) / 2;
    return (long long)sum_even;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }

    if (n > 62) {
        fprintf(stderr, "n must be at most 62 to avoid overflow\n");
        return EXIT_FAILURE;
    }

    long long result = sum_even_binomial_coefficients(n);
    if (result == -1) {
        fprintf(stderr, "Error computing sum\n");
        return EXIT_FAILURE;
    }

    printf("Sum of even-indexed binomial coefficients: %lld\n", result);
    return EXIT_SUCCESS;
}