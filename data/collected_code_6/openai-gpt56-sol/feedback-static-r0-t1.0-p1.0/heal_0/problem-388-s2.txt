#include <stdio.h>
#include <stdlib.h>

static unsigned long long highest_power_of_two(unsigned long long n)
{
    unsigned long long result = 1;

    if (n == 0) {
        return 0;
    }

    while (result <= n / 2) {
        result *= 2;
    }

    return result;
}

int main(void)
{
    unsigned long long n;
    unsigned long long result;

    if (scanf("%llu", &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    result = highest_power_of_two(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}