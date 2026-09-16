#include <stdio.h>
#include <stdlib.h>

long long find_max_periodic(long long n, long long k);

long long find_max_periodic(long long n, long long k)
{
    long long quotient;

    if (k <= 0LL || n < 0LL) {
        return -1LL;
    }

    quotient = n / k;

    if (quotient < (k - 1LL)) {
        return quotient;
    }

    return k - 1LL;
}

int main(void)
{
    long long n;
    long long k;
    long long result;

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    printf("Enter k: ");
    if (scanf("%lld", &k) != 1) {
        fprintf(stderr, "Invalid input for k\n");
        return EXIT_FAILURE;
    }

    result = find_max_periodic(n, k);

    if (result < 0LL) {
        fprintf(stderr, "Invalid arguments: n must be >= 0 and k must be > 0\n");
        return EXIT_FAILURE;
    }

    printf("Maximum value of f(x) = (x / k) %% k for x in [0, %lld] is: %lld\n", n, result);

    return EXIT_SUCCESS;
}