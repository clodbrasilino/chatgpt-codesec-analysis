#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || capacity < 2) {
        return -1;
    }

    do {
        ch = getchar();
    } while (ch != EOF &&
             (ch == ' ' || ch == '\t' || ch == '\n' ||
              ch == '\r' || ch == '\f' || ch == '\v'));

    if (ch == EOF) {
        return -1;
    }

    while (ch != EOF &&
           ch != ' ' && ch != '\t' && ch != '\n' &&
           ch != '\r' && ch != '\f' && ch != '\v') {
        if (length + 1 >= capacity) {
            do {
                ch = getchar();
            } while (ch != EOF &&
                     ch != ' ' && ch != '\t' && ch != '\n' &&
                     ch != '\r' && ch != '\f' && ch != '\v');
            return -1;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    buffer[length] = '\0';
    return 0;
}

static int read_uintmax_value(uintmax_t maximum, uintmax_t *value)
{
    char token[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(token, sizeof(token)) != 0 ||
        token[0] == '-' || token[0] == '+') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > maximum) {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(void)
{
    uint64_t modulus;
    uint64_t remainder;
    uint64_t *values = NULL;
    size_t count;
    uintmax_t input;

    if (read_uintmax_value((uintmax_t)SIZE_MAX, &input) != 0) {
        return EXIT_FAILURE;
    }
    count = (size_t)input;

    if (read_uintmax_value(UINT64_MAX, &input) != 0 || input == 0) {
        return EXIT_FAILURE;
    }
    modulus = (uint64_t)input;

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
        if (read_uintmax_value(UINT64_MAX, &input) != 0) {
            free(values);
            return EXIT_FAILURE;
        }
        values[i] = (uint64_t)input;
    }

    if (product_remainder(values, count, modulus, &remainder) != 0) {
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