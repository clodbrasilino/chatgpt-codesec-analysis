#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_squares_of_even(unsigned int n) {
    if (n == 0) {
        return 0;
    }

    if (n > 4294967295U / 4) {
        fprintf(stderr, "Error: Input exceeds calculation limits.\n");
        exit(EXIT_FAILURE);
    }

    unsigned long long sum = 0;
    unsigned int i;

    for (i = 1; i <= n; i++) {
        unsigned long long term = 2ULL * i;
        sum += term * term;
    }

    return sum;
}

int main(void) {
    unsigned int n;
    int ret;

    printf("Enter n: ");
    ret = scanf("%u", &n);

    if (ret != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_of_squares_of_even(n);
    printf("Sum of squares of first %u even natural numbers: %llu\n", n, result);

    return EXIT_SUCCESS;
}