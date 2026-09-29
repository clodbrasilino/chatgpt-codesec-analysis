#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long nth_rectangular(long long n, int *error)
{
    *error = 0;
    if (n < 1) {
        *error = 1;
        return 0;
    }
    if (n > 3037000499LL) {
        *error = 1;
        return 0;
    }
    return n * (n + 1);
}

int main(void)
{
    long long n;
    int error;
    long long result;

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = nth_rectangular(n, &error);
    if (error != 0) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }

    printf("The %lld-th rectangular number is %lld\n", n, result);
    return EXIT_SUCCESS;
}