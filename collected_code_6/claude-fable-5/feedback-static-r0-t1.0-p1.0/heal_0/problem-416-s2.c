#include <stdio.h>
#include <stdlib.h>

static long long max2(long long a, long long b)
{
    return (a > b) ? a : b;
}

static long long maxSum(long long n, long long *memo, long long limit)
{
    long long divided;

    if (n <= 0) {
        return 0;
    }

    if (n < limit && memo[n] != -1) {
        return memo[n];
    }

    divided = maxSum(n / 2, memo, limit) +
              maxSum(n / 3, memo, limit) +
              maxSum(n / 4, memo, limit);

    divided = max2(n, divided);

    if (n < limit) {
        memo[n] = divided;
    }

    return divided;
}

static int findMaxSum(long long n, long long *result)
{
    long long *memo;
    long long limit;
    long long i;

    if (n < 0 || result == NULL) {
        return -1;
    }

    limit = n + 1;
    if (limit > 1000000) {
        limit = 1000000;
    }

    memo = malloc((size_t)limit * sizeof(long long));
    if (memo == NULL) {
        return -1;
    }

    for (i = 0; i < limit; i++) {
        memo[i] = -1;
    }

    *result = maxSum(n, memo, limit);

    free(memo);
    return 0;
}

int main(void)
{
    long long n;
    long long result;

    printf("Enter a non-negative number: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return EXIT_FAILURE;
    }

    if (findMaxSum(n, &result) != 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("Maximum sum for %lld is %lld\n", n, result);

    return EXIT_SUCCESS;
}