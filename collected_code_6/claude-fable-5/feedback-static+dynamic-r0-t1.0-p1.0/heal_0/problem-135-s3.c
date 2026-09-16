#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long hexagonal_number(int n)
{
    if (n < 1) {
        return -1;
    }
    if ((long long)n > (LLONG_MAX / 2) / n) {
        return -1;
    }
    return (long long)n * (2LL * (long long)n - 1LL);
}

int main(void)
{
    int n = 0;
    long long result = 0;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = hexagonal_number(n);
    if (result < 0) {
        fprintf(stderr, "Invalid value of n or overflow\n");
        return EXIT_FAILURE;
    }

    printf("The %d-th hexagonal number is %lld\n", n, result);
    return EXIT_SUCCESS;
}