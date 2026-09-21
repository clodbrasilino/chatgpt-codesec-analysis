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

static int is_space_character(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_uintmax_value(uintmax_t maximum, uintmax_t *value)
{
    uintmax_t result = 0;
    int ch;
    int have_digit = 0;
    int overflow = 0;
    int malformed = 0;

    if (value == NULL) {
        return -1;
    }

    do {
        ch = fgetc(stdin);

        if (ch == EOF) {
            return -1;
        }
    } while (is_space_character(ch));

    do {
        if (ch >= '0' && ch <= '9') {
            unsigned int digit = (unsigned int)(ch - '0');

            have_digit = 1;

            if (!overflow) {
                if (result > maximum / UINTMAX_C(10) ||
                    (result == maximum / UINTMAX_C(10) &&
                     (uintmax_t)digit > maximum % UINTMAX_C(10))) {
                    overflow = 1;
                } else {
                    result = result * UINTMAX_C(10) + (uintmax_t)digit;
                }
            }
        } else {
            malformed = 1;
        }

        ch = fgetc(stdin);
    } while (ch != EOF && !is_space_character(ch));

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    if (!have_digit || overflow || malformed) {
        return -1;
    }

    *value = result;
    return 0;
}

int main(void)
{
    uint64_t modulus;
    uint64_t result;
    uintmax_t input;
    size_t count;

    if (read_uintmax_value((uintmax_t)SIZE_MAX, &input) != 0) {
        return EXIT_FAILURE;
    }

    count = (size_t)input;

    if (read_uintmax_value(UINT64_MAX, &input) != 0 || input == 0) {
        return EXIT_FAILURE;
    }

    modulus = (uint64_t)input;
    result = UINT64_C(1) % modulus;

    for (size_t i = 0; i < count; ++i) {
        if (read_uintmax_value(UINT64_MAX, &input) != 0) {
            return EXIT_FAILURE;
        }

        result = multiply_mod(result, (uint64_t)input, modulus);
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}