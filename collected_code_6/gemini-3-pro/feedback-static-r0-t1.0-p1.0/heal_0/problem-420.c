#include <stdio.h>
#include <stdlib.h>

unsigned long long cube_sum_even_numbers(unsigned int n);

unsigned long long cube_sum_even_numbers(unsigned int n) {
    unsigned long long sum = 0;
    unsigned int i;
    unsigned long long max_ull = ~0ULL;

    for (i = 1; i <= n; i++) {
        unsigned long long even = (unsigned long long)i * 2ULL;
        unsigned long long cube;

        if (even > 2642245ULL) {
            return 0;
        }

        cube = even * even * even;

        if (max_ull - sum < cube) {
            return 0;
        }

        sum += cube;
    }

    return sum;
}

int main(void) {
    unsigned int n;
    unsigned long long result;

    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }

    result = cube_sum_even_numbers(n);

    if (result == 0 && n != 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}