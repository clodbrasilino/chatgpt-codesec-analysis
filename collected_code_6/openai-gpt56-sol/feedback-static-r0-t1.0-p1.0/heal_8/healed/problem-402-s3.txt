#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

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
    return a >= modulus - b ? a - (modulus - b) : a + b;
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
    uint64_t *numerators = NULL;
    uint64_t value;

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

    if (r > (uint64_t)(SIZE_MAX / sizeof(*numerators))) {
        return 0;
    }

    if (r != 0) {
        numerators = malloc((size_t)r * sizeof(*numerators));
        if (numerators == NULL) {
            return 0;
        }
    }

    for (uint64_t i = 0; i < r; ++i) {
        numerators[i] = n - r + UINT64_C(1) + i;
    }

    for (uint64_t denominator = 2; denominator <= r; ++denominator) {
        uint64_t remaining = denominator;

        for (uint64_t i = 0; i < r && remaining != 1; ++i) {
            uint64_t divisor = gcd_u64(numerators[i], remaining);
            numerators[i] /= divisor;
            remaining /= divisor;
        }

        if (remaining != 1) {
            free(numerators);
            return 0;
        }
    }

    value = UINT64_C(1) % modulus;

    for (uint64_t i = 0; i < r; ++i) {
        value = multiply_mod(value, numerators[i] % modulus, modulus);
    }

    free(numerators);
    *result = value;
    return 1;
}

static int read_line(char **buffer)
{
    char *data;
    size_t capacity = 128;
    size_t length = 0;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    data = malloc(capacity);

    if (data == NULL) {
        return 0;
    }

    for (;;) {
        size_t available;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_data;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return 0;
            }

            new_capacity = capacity * 2;
            new_data = realloc(data, new_capacity);

            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        available = capacity - length;

        if (available > (size_t)INT_MAX) {
            available = (size_t)INT_MAX;
        }

        if (fgets(data + length, (int)available, stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(data);
                return 0;
            }
            break;
        }

        while (data[length] != '\0' && data[length] != '\n') {
            ++length;
        }

        if (data[length] == '\n') {
            data[length] = '\0';
            *buffer = data;
            return 1;
        }

        if (feof(stdin)) {
            break;
        }
    }

    data[length] = '\0';
    *buffer = data;
    return 1;
}

static int parse_u64(const char **cursor, uint64_t *value)
{
    const unsigned char *p;
    uint64_t parsed = 0;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    p = (const unsigned char *)*cursor;

    while (*p != '\0' && isspace(*p)) {
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

        if (parsed > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        parsed = parsed * UINT64_C(10) + digit;
        ++p;
    } while (isdigit(*p));

    if (*p != '\0' && !isspace(*p)) {
        return 0;
    }

    *cursor = (const char *)p;
    *value = parsed;
    return 1;
}

static int parse_input(const char *input, uint64_t *n, uint64_t *r,
                       uint64_t *modulus)
{
    const char *cursor;
    const unsigned char *p;

    if (input == NULL || n == NULL || r == NULL || modulus == NULL) {
        return 0;
    }

    cursor = input;

    if (!parse_u64(&cursor, n) ||
        !parse_u64(&cursor, r) ||
        !parse_u64(&cursor, modulus)) {
        return 0;
    }

    p = (const unsigned char *)cursor;

    while (*p != '\0' && isspace(*p)) {
        ++p;
    }

    return *p == '\0';
}

int main(void)
{
    char *input = NULL;
    uint64_t n;
    uint64_t r;
    uint64_t modulus;
    uint64_t result;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_input(input, &n, &r, &modulus)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!ncr_mod(n, r, modulus, &result)) {
        fputs("Computation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}