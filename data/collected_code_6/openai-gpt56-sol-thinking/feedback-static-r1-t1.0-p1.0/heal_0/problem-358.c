#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MODULO_SUCCESS = 0,
    MODULO_INVALID_ARGUMENT,
    MODULO_LENGTH_MISMATCH,
    MODULO_DIVISION_BY_ZERO,
    MODULO_ARITHMETIC_ERROR
} ModuloStatus;

static ModuloStatus modulo_lists(
    const int *dividends,
    size_t dividend_count,
    const int *divisors,
    size_t divisor_count,
    int *results,
    size_t result_count)
{
    size_t i;

    if (dividend_count != divisor_count || result_count < dividend_count) {
        return MODULO_LENGTH_MISMATCH;
    }

    if (dividend_count > 0U &&
        (dividends == NULL || divisors == NULL || results == NULL)) {
        return MODULO_INVALID_ARGUMENT;
    }

    for (i = 0U; i < dividend_count; ++i) {
        if (divisors[i] == 0) {
            return MODULO_DIVISION_BY_ZERO;
        }

        if (dividends[i] == INT_MIN && divisors[i] == -1) {
            return MODULO_ARITHMETIC_ERROR;
        }
    }

    for (i = 0U; i < dividend_count; ++i) {
        results[i] = dividends[i] % divisors[i];
    }

    return MODULO_SUCCESS;
}

int main(void)
{
    const int dividends[] = {17, 25, 36, 49, 81};
    const int divisors[] = {5, 7, 8, 6, 10};
    int results[sizeof(dividends) / sizeof(dividends[0])];
    const size_t count = sizeof(dividends) / sizeof(dividends[0]);
    ModuloStatus status;
    size_t i;

    status = modulo_lists(
        dividends,
        count,
        divisors,
        sizeof(divisors) / sizeof(divisors[0]),
        results,
        sizeof(results) / sizeof(results[0]));

    if (status != MODULO_SUCCESS) {
        if (fprintf(stderr, "Modulo operation failed with status %d\n", status) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (printf("%d%s", results[i], (i + 1U < count) ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}