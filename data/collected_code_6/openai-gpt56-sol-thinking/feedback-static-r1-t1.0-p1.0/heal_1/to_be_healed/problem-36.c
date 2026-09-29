#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t modular_add(uint64_t left, uint64_t right, uint64_t modulus)
{
    if (left >= modulus - right) {
        return left - (modulus - right);
    }

    return left + right;
}

static uint64_t modular_multiply(uint64_t left, uint64_t right, uint64_t modulus)
{
    uint64_t result = 0;

    while (right != 0) {
        if ((right & UINT64_C(1)) != 0) {
            result = modular_add(result, left, modulus);
        }

        right >>= 1;

        if (right != 0) {
            left = modular_add(left, left, modulus);
        }
    }

    return result;
}

static uint64_t modular_power(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = UINT64_C(1) % modulus;

    while (exponent != 0) {
        if ((exponent & UINT64_C(1)) != 0) {
            result = modular_multiply(result, base, modulus);
        }

        exponent >>= 1;

        if (exponent != 0) {
            base = modular_multiply(base, base, modulus);
        }
    }

    return result;
}

bool find_nth_digit(uint64_t numerator, uint64_t denominator,
                    uint64_t position, unsigned int *digit)
{
    uint64_t remainder;
    uint64_t accumulated = 0;
    unsigned int result = 0;
    unsigned int i;

    if (digit == NULL || denominator == 0 || numerator >= denominator ||
        position == 0) {
        return false;
    }

    remainder = modular_multiply(
        numerator,
        modular_power(UINT64_C(10) % denominator, position - 1, denominator),
        denominator
    );

    for (i = 0; i < 10; ++i) {
        if (accumulated >= denominator - remainder) {
            accumulated -= denominator - remainder;
            ++result;
        } else {
            accumulated += remainder;
        }
    }

    *digit = result;
    return true;
}

int main(void)
{
    int64_t numerator;
    int64_t denominator;
    int64_t position;
    unsigned int digit;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64,
              &numerator, &denominator, &position) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (numerator < 0 || denominator <= 0 || position <= 0 ||
        numerator >= denominator ||
        !find_nth_digit((uint64_t)numerator, (uint64_t)denominator,
                        (uint64_t)position, &digit)) {
        fprintf(stderr, "Invalid fraction or position\n");
        return EXIT_FAILURE;
    }

    printf("%u\n", digit);
    return EXIT_SUCCESS;
}