#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stddef.h>

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
                   uint64_t *value)
{
    uint64_t *numerators;
    uint64_t result;

    if (value == NULL || modulus == 0) {
        return 0;
    }

    if (modulus == 1 || r > n) {
        *value = 0;
        return 1;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r == 0) {
        *value = 1 % modulus;
        return 1;
    }

    if (r > (uint64_t)(SIZE_MAX / sizeof(*numerators))) {
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

        for (uint64_t i = 0; i < r && remaining > 1; ++i) {
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

        if (denominator == UINT64_MAX) {
            break;
        }
    }

    result = 1 % modulus;

    for (uint64_t i = 0; i < r; ++i) {
        result = multiply_mod(result, numerators[i] % modulus, modulus);
    }

    free(numerators);
    *value = result;
    return 1;
}

static int parse_u64(const char **cursor, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    if (**cursor == '\0' || **cursor == '-' || **cursor == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (uint64_t)parsed;
    return 1;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *replacement;

    if (buffer == NULL || capacity == NULL || required == 0) {
        return 0;
    }

    if (*capacity >= required) {
        return 1;
    }

    new_capacity = *capacity == 0 ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    replacement = realloc(*buffer, new_capacity);
    if (replacement == NULL) {
        return 0;
    }

    *buffer = replacement;
    *capacity = new_capacity;
    return 1;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return 0;
        }

        if (!grow_buffer(&buffer, &capacity, length + 2)) {
            free(buffer);
            return 0;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (!grow_buffer(&buffer, &capacity, length + 1)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    const char *cursor;
    uint64_t n;
    uint64_t r;
    uint64_t modulus;
    uint64_t result;

    if (!read_line(stdin, &input)) {
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_u64(&cursor, &n) ||
        !parse_u64(&cursor, &r) ||
        !parse_u64(&cursor, &modulus)) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || modulus == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (!ncr_mod(n, r, modulus, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}