#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_space(int c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

static int read_token(char **buffer, size_t *capacity)
{
    int c;
    size_t length = 0;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*buffer == NULL || *capacity < 2) {
        char *new_buffer = malloc(128);

        if (new_buffer == NULL) {
            return 0;
        }

        free(*buffer);
        *buffer = new_buffer;
        *capacity = 128;
    }

    do {
        c = fgetc(stdin);
    } while (c != EOF && is_space(c));

    if (c == EOF) {
        return 0;
    }

    while (c != EOF && !is_space(c)) {
        if (length == SIZE_MAX - 1) {
            return 0;
        }

        if (length + 1 >= *capacity) {
            size_t required = length + 2;
            size_t new_capacity = *capacity;
            char *new_buffer;

            if (required < length) {
                return 0;
            }

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            new_buffer = realloc(*buffer, new_capacity);
            if (new_buffer == NULL) {
                return 0;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[length++] = (char)(unsigned char)c;
        c = fgetc(stdin);
    }

    if (c == EOF && ferror(stdin)) {
        return 0;
    }

    (*buffer)[length] = '\0';
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN ||
        parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return a >= modulus - b ? a - (modulus - b) : a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0;

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

static uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = UINT64_C(1);

    base %= modulus;

    while (exponent != 0) {
        if ((exponent & UINT64_C(1)) != 0) {
            result = multiply_mod(result, base, modulus);
        }

        exponent >>= 1;

        if (exponent != 0) {
            base = multiply_mod(base, base, modulus);
        }
    }

    return result;
}

static int is_prime(uint64_t value)
{
    static const uint64_t small_primes[] = {
        UINT64_C(2), UINT64_C(3), UINT64_C(5), UINT64_C(7),
        UINT64_C(11), UINT64_C(13), UINT64_C(17), UINT64_C(19),
        UINT64_C(23), UINT64_C(29), UINT64_C(31), UINT64_C(37)
    };
    static const uint64_t witnesses[] = {
        UINT64_C(2), UINT64_C(325), UINT64_C(9375),
        UINT64_C(28178), UINT64_C(450775),
        UINT64_C(9780504), UINT64_C(1795265022)
    };
    uint64_t d;
    unsigned int shift = 0;
    size_t i;

    if (value < UINT64_C(2)) {
        return 0;
    }

    for (i = 0; i < sizeof small_primes / sizeof small_primes[0]; ++i) {
        if (value == small_primes[i]) {
            return 1;
        }

        if (value % small_primes[i] == 0) {
            return 0;
        }
    }

    d = value - UINT64_C(1);

    while ((d & UINT64_C(1)) == 0) {
        d >>= 1;
        ++shift;
    }

    for (i = 0; i < sizeof witnesses / sizeof witnesses[0]; ++i) {
        uint64_t witness = witnesses[i] % value;
        uint64_t x;
        unsigned int r;

        if (witness == 0) {
            continue;
        }

        x = power_mod(witness, d, value);

        if (x == UINT64_C(1) || x == value - UINT64_C(1)) {
            continue;
        }

        for (r = 1; r < shift; ++r) {
            x = multiply_mod(x, x, value);

            if (x == value - UINT64_C(1)) {
                break;
            }
        }

        if (r == shift) {
            return 0;
        }
    }

    return 1;
}

static uint64_t normalize_modulo(int64_t value, uint64_t modulus)
{
    uint64_t magnitude;
    uint64_t remainder;

    if (value >= 0) {
        return (uint64_t)value % modulus;
    }

    magnitude = (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
    remainder = magnitude % modulus;

    return remainder == 0 ? 0 : modulus - remainder;
}

static size_t count_self_inverse_elements(const int64_t *array,
                                          size_t length,
                                          uint64_t modulus)
{
    size_t count = 0;
    size_t i;

    for (i = 0; i < length; ++i) {
        uint64_t residue = normalize_modulo(array[i], modulus);

        if (residue == UINT64_C(1) ||
            residue == modulus - UINT64_C(1)) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char *token = NULL;
    int64_t *array = NULL;
    size_t token_capacity = 0;
    size_t length;
    uint64_t modulus;
    size_t count;
    size_t i;
    int status = EXIT_FAILURE;

    if (!read_token(&token, &token_capacity) ||
        !parse_size(token, &length) ||
        !read_token(&token, &token_capacity) ||
        !parse_uint64(token, &modulus)) {
        goto cleanup;
    }

    if (!is_prime(modulus) || length > SIZE_MAX / sizeof *array) {
        goto cleanup;
    }

    if (length != 0) {
        array = malloc(length * sizeof *array);
        if (array == NULL) {
            goto cleanup;
        }
    }

    for (i = 0; i < length; ++i) {
        if (!read_token(&token, &token_capacity) ||
            !parse_int64(token, &array[i])) {
            goto cleanup;
        }
    }

    count = count_self_inverse_elements(array, length, modulus);

    if (printf("%zu\n", count) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(array);
    free(token);
    return status;
}