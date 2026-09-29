#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MAX_TOKEN_LENGTH = 1024
};

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

static int array_product_remainder(const uint64_t *values, size_t count,
                                   uint64_t modulus, uint64_t *remainder)
{
    uint64_t result;

    if (remainder == NULL || modulus == 0 ||
        (values == NULL && count != 0)) {
        return -1;
    }

    result = UINT64_C(1) % modulus;

    for (size_t i = 0; i < count; ++i) {
        result = multiply_mod(result, values[i], modulus);
    }

    *remainder = result;
    return 0;
}

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || capacity < 2) {
        return -1;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    while (ch != EOF &&
           ch != ' ' && ch != '\t' && ch != '\n' &&
           ch != '\r' && ch != '\f' && ch != '\v') {
        if (length + 1 >= capacity) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF &&
                     ch != ' ' && ch != '\t' && ch != '\n' &&
                     ch != '\r' && ch != '\f' && ch != '\v');

            return -1;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    buffer[length] = '\0';
    return 0;
}

static int read_uintmax(uintmax_t *value)
{
    char token[MAX_TOKEN_LENGTH + 1];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(token, sizeof(token)) != 0) {
        return -1;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || end == NULL || *end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL || read_uintmax(&parsed) != 0 ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL || read_uintmax(&parsed) != 0 ||
        parsed > (uintmax_t)UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    size_t count;
    uint64_t modulus;
    uint64_t remainder;
    uint64_t *values = NULL;

    if (read_size(&count) != 0 ||
        read_uint64(&modulus) != 0 ||
        modulus == 0) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_uint64(&values[i]) != 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (array_product_remainder(values, count, modulus, &remainder) != 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);

    if (printf("%" PRIu64 "\n", remainder) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}