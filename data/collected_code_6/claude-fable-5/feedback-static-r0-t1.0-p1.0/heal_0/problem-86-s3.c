#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int centered_hexagonal(unsigned int n, unsigned long long *result)
{
    unsigned long long ull_n;

    if (result == NULL) {
        return -1;
    }

    if (n == 0U) {
        return -1;
    }

    ull_n = (unsigned long long)n;

    if (ull_n > 2500000000ULL) {
        return -1;
    }

    *result = 3ULL * ull_n * (ull_n - 1ULL) + 1ULL;
    return 0;
}

int main(void)
{
    unsigned int n = 10U;
    unsigned long long value = 0ULL;

    if (centered_hexagonal(n, &value) != 0) {
        (void)fprintf(stderr, "Error: invalid input %u\n", n);
        return EXIT_FAILURE;
    }

    if (printf("The %uth centered hexagonal number is %llu\n", n, value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}