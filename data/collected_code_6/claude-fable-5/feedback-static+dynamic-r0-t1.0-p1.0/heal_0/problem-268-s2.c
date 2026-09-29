#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long star_number(long long n)
{
    if (n < 1) {
        return -1;
    }
    if (n > 1000000000LL) {
        return -1;
    }
    return 6LL * n * (n - 1LL) + 1LL;
}

int main(void)
{
    long long n = 0;
    long long result = 0;

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = star_number(n);
    if (result < 0) {
        fprintf(stderr, "n must be between 1 and 1000000000\n");
        return EXIT_FAILURE;
    }

    printf("The %lld'th star number is %lld\n", n, result);
    return EXIT_SUCCESS;
}