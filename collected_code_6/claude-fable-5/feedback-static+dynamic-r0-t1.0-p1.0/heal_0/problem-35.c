#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long nth_rectangular(long long n, int *error)
{
    if (n < 1 || n > 3037000498LL) {
        *error = 1;
        return 0;
    }
    *error = 0;
    return n * (n + 1);
}

int main(void)
{
    long long n = 0;
    int error = 0;
    long long result = 0;

    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = nth_rectangular(n, &error);
    if (error != 0) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}