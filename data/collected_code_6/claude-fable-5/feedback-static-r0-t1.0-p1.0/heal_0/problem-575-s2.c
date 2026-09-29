#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long find_nth_non_multiple(long long n, long long divisor)
{
    if (n < 1 || divisor < 2) {
        return -1;
    }
    if (n > (LLONG_MAX - ((n - 1) / (divisor - 1)))) {
        return -1;
    }
    return n + ((n - 1) / (divisor - 1));
}

int main(void)
{
    long long n = 0;
    long long divisor = 0;
    long long result = 0;

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    printf("Enter divisor: ");
    if (scanf("%lld", &divisor) != 1) {
        fprintf(stderr, "Invalid input for divisor\n");
        return EXIT_FAILURE;
    }

    result = find_nth_non_multiple(n, divisor);
    if (result < 0) {
        fprintf(stderr, "Invalid arguments: n must be >= 1 and divisor must be >= 2, within representable range\n");
        return EXIT_FAILURE;
    }

    printf("The %lld-th number not a multiple of %lld is %lld\n", n, divisor, result);
    return EXIT_SUCCESS;
}