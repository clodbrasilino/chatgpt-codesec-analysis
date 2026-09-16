#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int sum_of_squares_even(unsigned int n, unsigned long long *result)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    for (i = 1U; i <= n; i++) {
        unsigned long long term = (unsigned long long)(2U * i);

        if (term > ULLONG_MAX / term) {
            return -1;
        }
        term = term * term;

        if (sum > ULLONG_MAX - term) {
            return -1;
        }
        sum += term;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned long long result = 0ULL;
    int scan_status;

    printf("Enter the value of n: ");

    scan_status = scanf("%u", &n);
    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (sum_of_squares_even(n, &result) != 0) {
        fprintf(stderr, "Error: computation failed or overflow occurred.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of squares of first %u even natural numbers: %llu\n", n, result);

    return EXIT_SUCCESS;
}