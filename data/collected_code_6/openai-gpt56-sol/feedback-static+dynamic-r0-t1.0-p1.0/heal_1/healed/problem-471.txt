#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    do {
        ch = getchar();
        if (ch == EOF) {
            return -1;
        }
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    do {
        if (length + 1 >= size) {
            do {
                ch = getchar();
            } while (ch != EOF && ch != ' ' && ch != '\t' &&
                     ch != '\n' && ch != '\r' && ch != '\f' &&
                     ch != '\v');
            return -1;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && ch != ' ' && ch != '\t' &&
             ch != '\n' && ch != '\r' && ch != '\f' &&
             ch != '\v');

    buffer[length] = '\0';
    return 0;
}

static int read_uintmax(uintmax_t *value)
{
    char token[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(token, sizeof(token)) != 0 ||
        token[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0') {
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
        parsed > UINT64_MAX) {
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

    if (printf("%" PRIu64 "\n", remainder) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}