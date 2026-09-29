#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    if (a >= modulus - b) {
        return a - (modulus - b);
    }

    return a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = UINT64_C(0);

    a %= modulus;

    while (b != UINT64_C(0)) {
        if ((b & UINT64_C(1)) != UINT64_C(0)) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1U;

        if (b != UINT64_C(0)) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = UINT64_C(1);

    base %= modulus;

    while (exponent != UINT64_C(0)) {
        if ((exponent & UINT64_C(1)) != UINT64_C(0)) {
            result = multiply_mod(result, base, modulus);
        }

        exponent >>= 1U;

        if (exponent != UINT64_C(0)) {
            base = multiply_mod(base, base, modulus);
        }
    }

    return result;
}

static bool passes_witness(uint64_t value, uint64_t d,
                           unsigned int power, uint64_t witness)
{
    const uint64_t base = witness % value;
    uint64_t x;
    unsigned int round;

    if (base == UINT64_C(0)) {
        return true;
    }

    x = power_mod(base, d, value);

    if (x == UINT64_C(1) || x == value - UINT64_C(1)) {
        return true;
    }

    for (round = 1U; round < power; ++round) {
        x = multiply_mod(x, x, value);

        if (x == value - UINT64_C(1)) {
            return true;
        }

        if (x == UINT64_C(1)) {
            return false;
        }
    }

    return false;
}

static bool is_prime(uint64_t value)
{
    uint64_t divisor;
    uint64_t d;
    unsigned int power = 0U;

    if (value < UINT64_C(2)) {
        return false;
    }

    if ((value & UINT64_C(1)) == UINT64_C(0)) {
        return value == UINT64_C(2);
    }

    for (divisor = UINT64_C(3);
         divisor <= UINT64_C(37);
         divisor += UINT64_C(2)) {
        if (value == divisor) {
            return true;
        }

        if (value % divisor == UINT64_C(0)) {
            return false;
        }
    }

    d = value - UINT64_C(1);

    while ((d & UINT64_C(1)) == UINT64_C(0)) {
        d >>= 1U;
        ++power;
    }

    return passes_witness(value, d, power, UINT64_C(2)) &&
           passes_witness(value, d, power, UINT64_C(325)) &&
           passes_witness(value, d, power, UINT64_C(9375)) &&
           passes_witness(value, d, power, UINT64_C(28178)) &&
           passes_witness(value, d, power, UINT64_C(450775)) &&
           passes_witness(value, d, power, UINT64_C(9780504)) &&
           passes_witness(value, d, power, UINT64_C(1795265022));
}

static bool find_nth_newman_shanks_williams_prime(uintmax_t n,
                                                  uint64_t *result)
{
    uint64_t previous = UINT64_C(1);
    uint64_t current = UINT64_C(1);
    uintmax_t found = UINTMAX_C(0);
    unsigned int index = 1U;

    if (n == UINTMAX_C(0) || result == NULL) {
        return false;
    }

    for (;;) {
        uint64_t next;

        if (current > (UINT64_MAX - previous) / UINT64_C(2)) {
            return false;
        }

        next = UINT64_C(2) * current + previous;
        previous = current;
        current = next;
        ++index;

        if ((index & 1U) != 0U && is_prime(current)) {
            ++found;

            if (found == n) {
                *result = current;
                return true;
            }
        }
    }
}

int main(int argc, char **argv)
{
    const char *argument;
    const char *cursor;
    char *end;
    uintmax_t n;
    uint64_t prime;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fputs("Usage: nsw_prime <positive integer>\n", stderr);
        return EXIT_FAILURE;
    }

    argument = argv[1];
    cursor = argument;

    if (*cursor == '\0') {
        fputs("Invalid positive integer\n", stderr);
        return EXIT_FAILURE;
    }

    while (*cursor != '\0') {
        if (*cursor < '0' || *cursor > '9') {
            fputs("Invalid positive integer\n", stderr);
            return EXIT_FAILURE;
        }

        ++cursor;
    }

    errno = 0;
    end = NULL;
    n = strtoumax(argument, &end, 10);

    if (errno == ERANGE || end == argument || end == NULL ||
        *end != '\0' || n == UINTMAX_C(0)) {
        fputs("Invalid positive integer\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_nth_newman_shanks_williams_prime(n, &prime)) {
        fputs("The requested prime exceeds the supported 64-bit range\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", prime) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}