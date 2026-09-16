#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int count_cubes(long long n, long long k, long long *result)
{
    long long side;
    long long temp;

    if (result == NULL) {
        return -1;
    }

    if (n <= 0 || k <= 0 || k > n) {
        return -1;
    }

    side = n - k + 1;

    if (side > 0 && side > LLONG_MAX / side) {
        return -1;
    }

    temp = side * side;

    if (temp > 0 && temp > LLONG_MAX / side) {
        return -1;
    }

    *result = temp * side;

    return 0;
}

int main(void)
{
    long long n;
    long long k;
    long long count;

    n = 0;
    k = 0;
    count = 0;

    printf("Enter cube size n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    printf("Enter sub-cube size k: ");
    if (scanf("%lld", &k) != 1) {
        fprintf(stderr, "Invalid input for k\n");
        return EXIT_FAILURE;
    }

    if (count_cubes(n, k, &count) != 0) {
        fprintf(stderr, "Invalid parameters or overflow detected\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of cubes of size %lld in a cube of size %lld: %lld\n",
               k, n, count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}