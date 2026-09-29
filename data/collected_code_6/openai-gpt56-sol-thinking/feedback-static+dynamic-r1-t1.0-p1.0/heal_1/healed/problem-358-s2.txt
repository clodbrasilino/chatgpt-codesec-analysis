#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MODULO_SUCCESS,
    MODULO_INVALID_ARGUMENT,
    MODULO_LENGTH_MISMATCH,
    MODULO_DIVISION_BY_ZERO
} ModuloStatus;

static ModuloStatus modulo_lists(
    const int *dividends,
    size_t dividend_count,
    const int *divisors,
    size_t divisor_count,
    int *remainders,
    size_t remainder_capacity,
    size_t *error_index)
{
    size_t i;

    if (error_index != NULL) {
        *error_index = 0;
    }

    if (dividend_count != divisor_count ||
        remainder_capacity < dividend_count) {
        return MODULO_LENGTH_MISMATCH;
    }

    if (dividend_count > 0 &&
        (dividends == NULL || divisors == NULL || remainders == NULL)) {
        return MODULO_INVALID_ARGUMENT;
    }

    for (i = 0; i < dividend_count; ++i) {
        if (divisors[i] == 0) {
            if (error_index != NULL) {
                *error_index = i;
            }
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

static int print_list(const int *list, size_t count)
{
    size_t i;

    if (list == NULL && count > 0) {
        return -1;
    }

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (printf("%d", list[i]) < 0) {
            return -1;
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const int dividends[] = {10, 21, -17, INT_MIN};
    const int divisors[] = {3, 4, 5, -1};
    int remainders[sizeof(dividends) / sizeof(dividends[0])];
    const size_t count = sizeof(dividends) / sizeof(dividends[0]);
    size_t error_index = 0;
    ModuloStatus status;

    status = modulo_lists(
        dividends,
        count,
        divisors,
        sizeof(divisors) / sizeof(divisors[0]),
        remainders,
        sizeof(remainders) / sizeof(remainders[0]),
        &error_index);

    if (status != MODULO_SUCCESS) {
        switch (status) {
            case MODULO_DIVISION_BY_ZERO:
                (void)fprintf(
                    stderr,
                    "Division by zero at index %zu\n",
                    error_index);
                break;

            case MODULO_LENGTH_MISMATCH:
                (void)fputs("List length mismatch\n", stderr);
                break;

            case MODULO_INVALID_ARGUMENT:
                (void)fputs("Invalid argument\n", stderr);
                break;

            default:
                (void)fputs("Unknown error\n", stderr);
                break;
        }

        return EXIT_FAILURE;
    }

    if (print_list(remainders, count) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}