#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int nonagonal(long long n, long long *result)
{
    if (n < 1 || result == NULL) {
        return -1;
    }

    if (n > 1000000000LL) {
        return -1;
    }

    *result = n * (7LL * n - 5LL) / 2LL;
    return 0;
}

int main(void)
{
    long long n = 10;
    long long value = 0;

    if (nonagonal(n, &value) != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("The %lld-th nonagonal number is %lld\n", n, value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}