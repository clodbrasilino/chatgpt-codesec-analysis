#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return (a >= modulus - b) ? a - (modulus - b) : a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0;

    a %= modulus;

    while (b != 0) {
        if ((b & UINT64_C(1)) != 0) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1;

        if (b != 0) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t modulus)
{
    uint64_t *numerators;
    uint64_t result;

    if (modulus == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r == 0) {
        return 1 % modulus;
    }

    if (r > SIZE_MAX / sizeof(*numerators)) {
        return 0;
    }

    numerators = malloc((size_t)r * sizeof(*numerators));
    if (numerators == NULL) {
        return 0;
    }

    for (uint64_t i = 0; i < r; ++i) {
        numerators[i] = n - r + 1 + i;
    }

    for (uint64_t denominator = 2; denominator <= r; ++denominator) {
        uint64_t remaining = denominator;

        for (uint64_t i = 0; i < r && remaining != 1; ++i) {
            uint64_t divisor = gcd_u64(numerators[i], remaining);

            if (divisor > 1) {
                numerators[i] /= divisor;
                remaining /= divisor;
            }
        }

        if (remaining != 1) {
            free(numerators);
            return 0;
        }
    }

    result = 1 % modulus;

    for (uint64_t i = 0; i < r; ++i) {
        result = multiply_mod(result, numerators[i] % modulus, modulus);
    }

    free(numerators);
    return result;
}

static int parse_u64(const char **cursor, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    if (**cursor == '\0' || **cursor == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 1;
}

int main(void)
{
    char input[256];
    const char *cursor;
    uint64_t n;
    uint64_t r;
    uint64_t modulus;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_u64(&cursor, &n) ||
        !parse_u64(&cursor, &r) ||
        !parse_u64(&cursor, &modulus)) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || modulus == 0) {
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", ncr_mod(n, r, modulus));
    return EXIT_SUCCESS;
}