#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long carol_number(unsigned int n, int *error)
{
    long long power;
    long long result;

    *error = 0;

    if (n == 0U || n > 31U) {
        *error = 1;
        return 0LL;
    }

    power = (1LL << n) - 1LL;
    result = power * power - 2LL;

    return result;
}

int main(void)
{
    unsigned int n;
    int scan_result;
    int error;
    long long result;

    printf("Enter n: ");
    scan_result = scanf("%u", &n);

    if (scan_result != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = carol_number(n, &error);

    if (error != 0) {
        fprintf(stderr, "n must be between 1 and 31.\n");
        return EXIT_FAILURE;
    }

    printf("Carol number %u is %lld\n", n, result);

    return EXIT_SUCCESS;
}