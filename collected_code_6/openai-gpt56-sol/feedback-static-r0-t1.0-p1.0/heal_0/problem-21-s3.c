#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int print_multiples(long long n, size_t m)
{
    if (n != 0 && m > (size_t)(LLONG_MAX / n)) {
        return -1;
    }

    for (size_t i = 1; i <= m; ++i) {
        printf("%lld%s", n * (long long)i, i == m ? "\n" : " ");
    }

    return 0;
}

int main(void)
{
    long long n;
    unsigned long long input_m;

    if (scanf("%lld %llu", &n, &input_m) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (n <= 0 || input_m > SIZE_MAX) {
        fputs("Input out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_multiples(n, (size_t)input_m) != 0) {
        fputs("Multiplication overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}