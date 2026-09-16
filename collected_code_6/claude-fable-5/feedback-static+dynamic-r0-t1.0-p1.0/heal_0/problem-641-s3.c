#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long nonagonal(int n)
{
    long long ln;

    if (n < 1) {
        return -1LL;
    }

    ln = (long long)n;

    if (ln > (LLONG_MAX - 5LL) / 7LL) {
        return -1LL;
    }

    return (ln * (7LL * ln - 5LL)) / 2LL;
}

int main(void)
{
    int n;
    long long result;

    n = 10;
    result = nonagonal(n);

    if (result < 0LL) {
        if (fprintf(stderr, "Invalid input or overflow\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("The %dth nonagonal number is %lld\n", n, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}