#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != UINT64_C(0)) {
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
    uint64_t result = UINT64_C(0);

    a %= modulus;
    b %= modulus;

    while (b != UINT64_C(0)) {
        if ((b & UINT64_C(1)) != UINT64_C(0)) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1U;

        if (b != UINT64_C(0)) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static int ncr_mod(uint64_t n, uint64_t r, uint64_t modulus,
                   uint64_t *result)
{
    uint64_t value = UINT64_C(1);

    if (result == NULL || modulus == UINT64_C(0) ||
        n > (uint64_t)INT64_MAX) {
        return 0;
    }

    if (r > n) {
        *result = UINT64_C(0);
        return 1;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (uint64_t i = UINT64_C(1); i <= r; ++i) {
        uint64_t numerator = n - r + i;
        uint64_t denominator = i;
        uint64_t divisor;
        uint64_t candidate;

        divisor = gcd_u64(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        divisor = gcd_u64(value, denominator);
        value /= divisor;
        denominator /= divisor;

        candidate = numerator;

        while (denominator != UINT64_C(1)) {
            if (candidate > UINT64_MAX - numerator) {
                return 0;
            }

            candidate += numerator;
            divisor = gcd_u64(candidate, denominator);
            candidate /= divisor;
            denominator /= divisor;
        }

        value = multiply_mod(value, candidate % modulus, modulus);
    }

    *result = value % modulus;
    return 1;
}

static int parse_u64(const char **cursor, uint64_t *value)
{
    const char *p = *cursor;
    char *end;

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '\0' || *p == '-' || *p == '+') {
        return 0;
    }

    errno = 0;
    uintmax_t parsed = strtoumax(p, &end, 10);

    if (errno == ERANGE || end == p || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;
    const char *cursor;
    uint64_t n;
    uint64_t r;
    uint64_t modulus;
    uint64_t result;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;
            char *replacement;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX - 1U) {
                free(input);
                fputs("Invalid input\n", stderr);
                return 1;
            }

            replacement = realloc(input, new_capacity);
            if (replacement == NULL) {
                free(input);
                fputs("Invalid input\n", stderr);
                return 1;
            }

            input = replacement;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        free(input);
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (length == capacity) {
        char *replacement = realloc(input, length + 1U);

        if (replacement == NULL) {
            free(input);
            fputs("Invalid input\n", stderr);
            return 1;
        }

        input = replacement;
    }

    input[length] = '\0';
    cursor = input;

    if (!parse_u64(&cursor, &n) ||
        !parse_u64(&cursor, &r) ||
        !parse_u64(&cursor, &modulus)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return 1;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return 1;
    }

    free(input);

    if (!ncr_mod(n, r, modulus, &result)) {
        fputs("Computation failed\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}