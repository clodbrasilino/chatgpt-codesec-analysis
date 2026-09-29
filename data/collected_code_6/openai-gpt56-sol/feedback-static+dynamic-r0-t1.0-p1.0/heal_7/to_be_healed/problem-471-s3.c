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

static int read_uintmax_value(uintmax_t maximum, uintmax_t *value)
{
    uintmax_t result = 0;
    int ch;
    int have_digit = 0;

    if (value == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    while (ch >= '0' && ch <= '9') {
        unsigned int digit = (unsigned int)(ch - '0');

        have_digit = 1;

        if (result > (maximum - digit) / UINTMAX_C(10)) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF &&
                     ch != ' ' && ch != '\t' && ch != '\n' &&
                     ch != '\r' && ch != '\f' && ch != '\v');
            return -1;
        }

        result = result * UINTMAX_C(10) + digit;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF) {
        if (ferror(stdin)) {
            return -1;
        }
    } else if (ch != ' ' && ch != '\t' && ch != '\n' &&
               ch != '\r' && ch != '\f' && ch != '\v') {
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != EOF &&
                 ch != ' ' && ch != '\t' && ch != '\n' &&
                 ch != '\r' && ch != '\f' && ch != '\v');
        return -1;
    }

    if (!have_digit) {
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