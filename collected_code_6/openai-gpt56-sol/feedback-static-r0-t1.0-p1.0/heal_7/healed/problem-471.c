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

static int is_space_char(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int discard_token(int ch)
{
    while (ch != EOF && !is_space_char(ch)) {
        ch = getchar();
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_uint64(uint64_t *value)
{
    uint64_t result = 0;
    int ch;
    int saw_digit = 0;
    int overflow = 0;

    if (value == NULL) {
        return -1;
    }

    do {
        ch = getchar();
        if (ch == EOF) {
            return -1;
        }
    } while (is_space_char(ch));

    if (ch == '+' || ch == '-') {
        (void)discard_token(ch);
        return -1;
    }

    while (ch != EOF && !is_space_char(ch)) {
        uint64_t digit;

        if (ch < '0' || ch > '9') {
            (void)discard_token(ch);
            return -1;
        }

        saw_digit = 1;
        digit = (uint64_t)(ch - '0');

        if (!overflow) {
            if (result > UINT64_MAX / UINT64_C(10) ||
                (result == UINT64_MAX / UINT64_C(10) &&
                 digit > UINT64_MAX % UINT64_C(10))) {
                overflow = 1;
            } else {
                result = result * UINT64_C(10) + digit;
            }
        }

        ch = getchar();
    }

    if (ferror(stdin) || !saw_digit || overflow) {
        return -1;
    }

    *value = result;
    return 0;
}

int main(void)
{
    uint64_t count_input;
    uint64_t modulus;
    uint64_t remainder;
    uint64_t *values = NULL;
    size_t count;

    if (read_uint64(&count_input) != 0 ||
        count_input > (uint64_t)SIZE_MAX ||
        read_uint64(&modulus) != 0 ||
        modulus == 0) {
        return EXIT_FAILURE;
    }

    count = (size_t)count_input;

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