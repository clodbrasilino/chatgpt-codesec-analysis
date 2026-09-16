#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MODULO_SUCCESS = 0,
    MODULO_INVALID_ARGUMENT,
    MODULO_LENGTH_MISMATCH,
    MODULO_INSUFFICIENT_CAPACITY,
    MODULO_DIVISION_BY_ZERO
} ModuloStatus;

static ModuloStatus modulo_lists(
    const int *dividends,
    size_t dividend_count,
    const int *divisors,
    size_t divisor_count,
    int *remainders,
    size_t remainder_capacity
) {
    size_t i;

    if (dividend_count != divisor_count) {
        return MODULO_LENGTH_MISMATCH;
    }

    if (dividend_count > remainder_capacity) {
        return MODULO_INSUFFICIENT_CAPACITY;
    }

    if (dividend_count > 0 &&
        (dividends == NULL || divisors == NULL || remainders == NULL)) {
        return MODULO_INVALID_ARGUMENT;
    }

    for (i = 0; i < dividend_count; ++i) {
        if (divisors[i] == 0) {
            return MODULO_DIVISION_BY_ZERO;
        }
    }

    for (i = 0; i < dividend_count; ++i) {
        if (dividends[i] == INT_MIN && divisors[i] == -1) {
            remainders[i] = 0;
        } else {
            remainders[i] = dividends[i] % divisors[i];
        }
    }

    return MODULO_SUCCESS;
}

static const char *modulo_status_message(ModuloStatus status) {
    switch (status) {
        case MODULO_SUCCESS:
            return "success";
        case MODULO_INVALID_ARGUMENT:
            return "invalid argument";
        case MODULO_LENGTH_MISMATCH:
            return "list length mismatch";
        case MODULO_INSUFFICIENT_CAPACITY:
            return "insufficient result capacity";
        case MODULO_DIVISION_BY_ZERO:
            return "division by zero";
        default:
            return "unknown error";
    }
}

int main(void) {
    const int dividends[] = {10, 21, 32, 43, 54};
    const int divisors[] = {3, 4, 5, 6, 7};
    int remainders[sizeof(dividends) / sizeof(dividends[0])];
    const size_t dividend_count = sizeof(dividends) / sizeof(dividends[0]);
    const size_t divisor_count = sizeof(divisors) / sizeof(divisors[0]);
    const size_t remainder_capacity =
        sizeof(remainders) / sizeof(remainders[0]);
    ModuloStatus status;
    size_t i;

    status = modulo_lists(
        dividends,
        dividend_count,
        divisors,
        divisor_count,
        remainders,
        remainder_capacity
    );

    if (status != MODULO_SUCCESS) {
        if (fprintf(stderr, "Error: %s\n", modulo_status_message(status)) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (putchar('[') == EOF) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < dividend_count; ++i) {
        if (printf("%s%d", i == 0 ? "" : ", ", remainders[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (puts("]") == EOF || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}