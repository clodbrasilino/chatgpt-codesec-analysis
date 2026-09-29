#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int sum_of_squares(unsigned int n, unsigned long long *result)
{
    unsigned long long sum = 0ULL;
    unsigned long long i;

    if (result == NULL) {
        return -1;
    }

    for (i = 1ULL; i <= (unsigned long long)n; i++) {
        unsigned long long square;

        if (i > ULLONG_MAX / i) {
            return -1;
        }
        square = i * i;
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
    unsigned int n;
    unsigned long long result;
    int scan_status;

    printf("Enter n: ");

    scan_status = scanf("%u", &n);
    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (sum_of_squares(n, &result) != 0) {
        fprintf(stderr, "Error: computation failed or overflow occurred.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of series up to %u^2 is %llu\n", n, result);

    return EXIT_SUCCESS;
}