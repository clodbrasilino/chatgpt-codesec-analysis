#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_space(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
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

static int product_remainder(const uint64_t *values, size_t count,
                             uint64_t modulus, uint64_t *remainder)
{
    uint64_t result;

    if (remainder == NULL || modulus == 0 ||
        (count != 0 && values == NULL)) {
        return -1;
    }

    result = UINT64_C(1) % modulus;

    for (size_t i = 0; i < count; ++i) {
        result = multiply_mod(result, values[i], modulus);
    }

    *remainder = result;
    return 0;
}

static int read_uintmax_value(uintmax_t maximum, uintmax_t *value)
{
    char buffer[256];
    uintmax_t result = 0;
    size_t length = 0;
    int ch;
    int overflow = 0;

    if (value == NULL) {
        return -1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && is_space(ch));

    if (ch == EOF) {
        return -1;
    }

    while (ch != EOF && !is_space(ch)) {
        if (length + 1 < sizeof(buffer)) {
            buffer[length++] = (char)ch;
        } else {
            overflow = 1;
        }

        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    if (overflow || length == 0) {
        return -1;
    }

    buffer[length] = '\0';

    for (size_t i = 0; i < length; ++i) {
        unsigned int digit;

        if (buffer[i] < '0' || buffer[i] > '9') {
            return -1;
        }

        digit = (unsigned int)(buffer[i] - '0');

        if (result > (maximum - digit) / UINTMAX_C(10)) {
            return -1;
        }

        result = result * UINTMAX_C(10) + digit;
    }

    *value = result;
    return 0;
}

int main(void)
{
    uint64_t modulus;
    uint64_t remainder;
    uint64_t *values = NULL;
    size_t count;
    uintmax_t input;
    int status = EXIT_FAILURE;

    if (read_uintmax_value((uintmax_t)SIZE_MAX, &input) != 0) {
        goto cleanup;
    }

    count = (size_t)input;

    if (read_uintmax_value(UINT64_MAX, &input) != 0 || input == 0) {
        goto cleanup;
    }

    modulus = (uint64_t)input;

    if (count > SIZE_MAX / sizeof(*values)) {
        goto cleanup;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_uintmax_value(UINT64_MAX, &input) != 0) {
            goto cleanup;
        }

        values[i] = (uint64_t)input;
    }

    if (product_remainder(values, count, modulus, &remainder) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", remainder) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    return status;
}