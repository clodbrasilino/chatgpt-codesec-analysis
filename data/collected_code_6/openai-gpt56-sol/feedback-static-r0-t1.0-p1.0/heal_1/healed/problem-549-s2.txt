#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int checked_multiply_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || (a != 0 && b > UINT64_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int sum_fifth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t i = 0; i < n; ++i) {
        uint64_t odd;
        uint64_t square;
        uint64_t fourth;
        uint64_t fifth;

        if (i > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
            return 0;
        }

        odd = UINT64_C(2) * i + UINT64_C(1);

        if (!checked_multiply_u64(odd, odd, &square) ||
            !checked_multiply_u64(square, square, &fourth) ||
            !checked_multiply_u64(fourth, odd, &fifth)) {
            return 0;
        }

        if (fifth > UINT64_MAX - sum) {
            return 0;
        }

        sum += fifth;
    }

    *result = sum;
    return 1;
}

int main(void)
{
    char input[128];
    char trailing;
    uint64_t n;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(input, " %" SCNu64 " %c", &n, &trailing) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_fifth_powers_of_odds(n, &sum)) {
        fputs("Result exceeds the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}