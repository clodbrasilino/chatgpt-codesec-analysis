#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
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

static int ncr_mod(uint64_t n, uint64_t r, uint64_t modulus,
                   uint64_t *result)
{
    uint64_t value = 1 % modulus;

    if (result == NULL || modulus == 0) {
        return 0;
    }

    if (r > n) {
        *result = 0;
        return 1;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (uint64_t i = 1; i <= r; ++i) {
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

        while (denominator != 1) {
            uint64_t quotient;
            uint64_t limit;

            divisor = gcd_u64(candidate, denominator);
            candidate /= divisor;
            denominator /= divisor;

            if (denominator == 1) {
                break;
            }

            quotient = candidate / numerator;
            limit = UINT64_MAX / numerator;

            if (quotient >= limit) {
                return 0;
            }

            candidate += numerator;
        }

        value = multiply_mod(value, candidate % modulus, modulus);
    }

    *result = value;
    return 1;
}

static int read_line(char *buffer, size_t size)
{
    size_t length;

    if (buffer == NULL || size < 2 || fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }
    }

    return 0;
}

static int parse_u64(const char **cursor, uint64_t *value)
{
    const unsigned char *p;
    uint64_t result = 0;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    p = (const unsigned char *)*cursor;

    while (isspace(*p)) {
        ++p;
    }

    if (*p == '+') {
        ++p;
    } else if (*p == '-') {
        return 0;
    }

    if (!isdigit(*p)) {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

        if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        result = result * UINT64_C(10) + digit;
        ++p;
    } while (isdigit(*p));

    if (*p != '\0' && !isspace(*p)) {
        return 0;
    }

    *cursor = (const char *)p;
    *value = result;
    return 1;
}

static int parse_input(const char *input, uint64_t *n, uint64_t *r,
                       uint64_t *modulus)
{
    const char *cursor = input;
    const unsigned char *p;

    if (!parse_u64(&cursor, n) ||
        !parse_u64(&cursor, r) ||
        !parse_u64(&cursor, modulus)) {
        return 0;
    }

    p = (const unsigned char *)cursor;

    while (isspace(*p)) {
        ++p;
    }

    return *p == '\0';
}

int main(void)
{
    char input[4096];
    uint64_t n;
    uint64_t r;
    uint64_t modulus;
    uint64_t result;

    if (!read_line(input, sizeof input) ||
        !parse_input(input, &n, &r, &modulus)) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!ncr_mod(n, r, modulus, &result)) {
        fputs("Computation failed\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}