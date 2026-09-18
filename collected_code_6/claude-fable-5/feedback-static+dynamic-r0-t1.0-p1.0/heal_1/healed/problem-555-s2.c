#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long difference_cubes_sum(long long n)
{
    long long sum_n = (n * (n + 1)) / 2;

    if (sum_n != 0 && sum_n > LLONG_MAX / sum_n) {
        fprintf(stderr, "Error: computation would overflow.\n");
        exit(EXIT_FAILURE);
    }

    long long sum_cubes = sum_n * sum_n;
    return sum_cubes - sum_n;
}

int main(void)
{
    long long n = 0;

    printf("Enter a natural number n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 1) {
        fprintf(stderr, "Error: n must be a natural number (n >= 1).\n");
        return EXIT_FAILURE;
    }

    if (n > 77935LL) {
        fprintf(stderr, "Error: n is too large and would cause overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Difference: %lld\n", difference_cubes_sum(n));

    return EXIT_SUCCESS;
}