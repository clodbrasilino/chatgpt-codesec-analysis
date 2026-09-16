#include <stdio.h>
#include <stdlib.h>

long long max_sum(long long n, long long *memo, long long limit)
{
    long long divided;

    if (n <= 0) {
        return 0;
    }

    if (n < limit && memo[n] != -1) {
        return memo[n];
    }

    divided = max_sum(n / 2, memo, limit) +
              max_sum(n / 3, memo, limit) +
              max_sum(n / 4, memo, limit);

    if (divided < n) {
        divided = n;
    }

    if (n < limit) {
        memo[n] = divided;
    }

    return divided;
}

long long find_max_sum(long long n)
{
    long long result;
    long long limit;
    long long i;
    long long *memo;

    if (n <= 0) {
        return 0;
    }

    limit = (n < 1000000) ? (n + 1) : 1000000;

    memo = malloc((size_t)limit * sizeof(*memo));
    if (memo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < limit; i++) {
        memo[i] = -1;
    }

    result = max_sum(n, memo, limit);

    free(memo);

    return result;
}

int main(void)
{
    long long n;

    printf("Enter a non-negative number: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("Maximum sum: %lld\n", find_max_sum(n));

    return EXIT_SUCCESS;
}