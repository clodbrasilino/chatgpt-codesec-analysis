#include <stdio.h>
#include <stdlib.h>

static unsigned long long count_ways(int n)
{
    unsigned long long a;
    unsigned long long b;
    unsigned long long current;
    int i;

    if (n < 0) {
        return 0ULL;
    }
    if ((n % 2) != 0) {
        return 0ULL;
    }
    if (n == 0) {
        return 1ULL;
    }

    a = 1ULL;
    b = 3ULL;

    if (n == 2) {
        return b;
    }

    current = b;
    for (i = 4; i <= n; i += 2) {
        current = (4ULL * b) - a;
        a = b;
        b = current;
    }

    return current;
}

int main(void)
{
    int n;
    int result;
    unsigned long long ways;

    printf("Enter the value of n for a 3 x n board: ");
    result = scanf("%d", &n);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative.\n");
        return EXIT_FAILURE;
    }

    if (n > 60) {
        fprintf(stderr, "Error: n too large, result would overflow.\n");
        return EXIT_FAILURE;
    }

    ways = count_ways(n);
    printf("Number of ways to fill a 3 x %d board: %llu\n", n, ways);

    return EXIT_SUCCESS;
}