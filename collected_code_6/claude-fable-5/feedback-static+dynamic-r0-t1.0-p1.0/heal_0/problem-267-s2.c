#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_squares_of_odd(unsigned int n)
{
    unsigned long long total = 0ULL;
    unsigned int i;

    for (i = 0U; i < n; i++) {
        unsigned long long odd = 2ULL * (unsigned long long)i + 1ULL;
        total += odd * odd;
    }

    return total;
}

int main(void)
{
    unsigned int n;
    int result;

    printf("Enter n: ");
    result = scanf("%u", &n);

    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 1000000U) {
        fprintf(stderr, "Input too large\n");
        return EXIT_FAILURE;
    }

    printf("Sum of squares of first %u odd natural numbers: %llu\n",
           n, sum_of_squares_of_odd(n));

    return EXIT_SUCCESS;
}