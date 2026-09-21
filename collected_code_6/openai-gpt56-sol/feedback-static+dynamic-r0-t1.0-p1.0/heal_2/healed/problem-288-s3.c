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

static int read_token(char *buffer, size_t size)
{
    int c;
    size_t length = 0;
    int overflow = 0;

    if (buffer == NULL || size == 0) {
        return 0;
    }

    do {
        c = getchar();
    } while (c != EOF && is_space(c));

    if (c == EOF) {
        return 0;
    }

    while (c != EOF && !is_space(c)) {
        if (length < size - 1) {
            buffer[length++] = (char)c;
        } else {
            overflow = 1;
        }
        c = getchar();
    }

    buffer[length] = '\0';
    return !overflow;
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
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int is_prime(uint64_t value)
{
    uint64_t divisor;

    if (value < UINT64_C(2)) {
        return 0;
    }

    if (value % UINT64_C(2) == 0) {
        return value == UINT64_C(2);
    }

    for (divisor = UINT64_C(3);
         divisor <= value / divisor;
         divisor += UINT64_C(2)) {
        if (value % divisor == 0) {
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

    magnitude = (uint64_t)(-(value + 1)) + UINT64_C(1);
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
    char *token;
    size_t token_size = 128;
    size_t length;
    uint64_t modulus;
    int64_t *array = NULL;
    size_t count;
    size_t i;
    int status = EXIT_FAILURE;

    token = malloc(token_size);
    if (token == NULL) {
        return EXIT_FAILURE;
    }

    if (!read_token(token, token_size) ||
        !parse_size(token, &length) ||
        !read_token(token, token_size) ||
        !parse_uint64(token, &modulus)) {
        goto cleanup;
    }

    if (!is_prime(modulus) ||
        length > SIZE_MAX / sizeof *array) {
        goto cleanup;
    }

    if (length > 0) {
        array = malloc(length * sizeof *array);
        if (array == NULL) {
            goto cleanup;
        }
    }

    for (i = 0; i < length; ++i) {
        if (!read_token(token, token_size) ||
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