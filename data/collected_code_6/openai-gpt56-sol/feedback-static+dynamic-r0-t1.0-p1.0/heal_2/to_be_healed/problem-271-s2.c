#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int checked_mul_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || (a != 0 && b > UINT64_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int sum_fifth_powers_even(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t value;
        uint64_t square;
        uint64_t fourth;
        uint64_t fifth;

        if (!checked_mul_u64(i, UINT64_C(2), &value) ||
            !checked_mul_u64(value, value, &square) ||
            !checked_mul_u64(square, square, &fourth) ||
            !checked_mul_u64(fourth, value, &fifth) ||
            sum > UINT64_MAX - fifth) {
            return 0;
        }

        sum += fifth;
    }

    *result = sum;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char extra;
    char *end;
    uintmax_t parsed;
    uint64_t n;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    parsed = strtoumax(input, &end, 10);

    if (end == input || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || sscanf(input, " %*" SCNu64 " %c", &extra) == 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (uint64_t)parsed;

    if (!sum_fifth_powers_even(n, &result)) {
        fputs("Arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}