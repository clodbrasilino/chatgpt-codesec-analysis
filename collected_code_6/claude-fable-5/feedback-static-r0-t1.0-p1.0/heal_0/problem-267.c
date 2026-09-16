#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int sum_of_squares_of_odds(unsigned int n, unsigned long long *result)
{
    unsigned long long sum = 0;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        unsigned long long odd = 2ULL * (unsigned long long)i + 1ULL;
        unsigned long long square;

        if (odd > ULLONG_MAX / odd) {
            return -1;
        }
        square = odd * odd;

        if (sum > ULLONG_MAX - square) {
            return -1;
        }
        sum += square;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    unsigned int n = 0;
    unsigned long long result = 0;
    int scan_status;

    printf("Enter n: ");
    scan_status = scanf("%u", &n);
    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (sum_of_squares_of_odds(n, &result) != 0) {
        fprintf(stderr, "Error: computation failed or overflow occurred\n");
        return EXIT_FAILURE;
    }

    printf("Sum of squares of first %u odd natural numbers: %llu\n", n, result);
    return EXIT_SUCCESS;
}