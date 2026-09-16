#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long count_cubes(long long n, long long k);

long long count_cubes(long long n, long long k)
{
    long long side;
    long long result;

    if (n <= 0 || k <= 0 || k > n) {
        return -1;
    }

    side = n - k + 1;

    if (side > 2097151) {
        return -1;
    }

    result = side * side * side;
    return result;
}

int main(void)
{
    long long n;
    long long k;
    long long result;
    int ret;

    printf("Enter cube size n: ");
    ret = scanf("%lld", &n);
    if (ret != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    printf("Enter sub-cube size k: ");
    ret = scanf("%lld", &k);
    if (ret != 1) {
        fprintf(stderr, "Invalid input for k\n");
        return EXIT_FAILURE;
    }

    result = count_cubes(n, k);
    if (result < 0) {
        fprintf(stderr, "Invalid parameters: require 0 < k <= n and result within range\n");
        return EXIT_FAILURE;
    }

    printf("Number of cubes of size %lld in a cube of size %lld: %lld\n", k, n, result);

    return EXIT_SUCCESS;
}