#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

static uint64_t sum_of_fourth_power_even(unsigned int n)
{
    uint64_t sum = 0ULL;
    uint64_t base;
    unsigned int i;
    uint64_t term;

    if (n == 0U) {
        return 0ULL;
    }

    if (n > 92681U) {
        errno = ERANGE;
        return UINT64_MAX;
    }

    for (i = 1U; i <= n; ++i) {
        base = (uint64_t)i * 2U;
        
        if (base > UINT64_MAX / base) {
            errno = ERANGE;
            return UINT64_MAX;
        }
        uint64_t square = base * base;

        if (square > UINT64_MAX / square) {
            errno = ERANGE;
            return UINT64_MAX;
        }
        term = square * square;

        if (sum > UINT64_MAX - term) {
            errno = ERANGE;
            return UINT64_MAX;
        }
        sum += term;
    }

    return sum;
}

int main(int argc, char **argv)
{
    unsigned int n;
    char *endptr;
    long val;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE || val < 0 || val > UINT_MAX || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: must be a non-negative integer within range.\n");
        return EXIT_FAILURE;
    }

    n = (unsigned int)val;
    errno = 0;
    result = sum_of_fourth_power_even(n);

    if (errno == ERANGE) {
        fprintf(stderr, "Result overflow, n is too large.\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", (unsigned long long)result);
    return EXIT_SUCCESS;
}