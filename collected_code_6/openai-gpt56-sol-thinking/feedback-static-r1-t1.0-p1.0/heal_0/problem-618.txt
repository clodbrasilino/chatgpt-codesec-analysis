#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    DIVIDE_SUCCESS = 0,
    DIVIDE_INVALID_ARGUMENT,
    DIVIDE_LENGTH_MISMATCH,
    DIVIDE_BY_ZERO,
    DIVIDE_NONFINITE_VALUE,
    DIVIDE_ALLOCATION_FAILURE
} DivideStatus;

DivideStatus divide_lists(
    const double *numerators,
    size_t numerator_count,
    const double *denominators,
    size_t denominator_count,
    double *results)
{
    double *temporary_results;
    size_t index;

    if (numerator_count != denominator_count) {
        return DIVIDE_LENGTH_MISMATCH;
    }

    if (numerator_count == 0U) {
        return DIVIDE_SUCCESS;
    }

    if (numerators == NULL || denominators == NULL || results == NULL) {
        return DIVIDE_INVALID_ARGUMENT;
    }

    if (numerator_count > SIZE_MAX / sizeof(*temporary_results)) {
        return DIVIDE_ALLOCATION_FAILURE;
    }

    for (index = 0U; index < numerator_count; ++index) {
        if (!isfinite(numerators[index]) || !isfinite(denominators[index])) {
            return DIVIDE_NONFINITE_VALUE;
        }

        if (denominators[index] == 0.0) {
            return DIVIDE_BY_ZERO;
        }
    }

    temporary_results = malloc(numerator_count * sizeof(*temporary_results));
    if (temporary_results == NULL) {
        return DIVIDE_ALLOCATION_FAILURE;
    }

    for (index = 0U; index < numerator_count; ++index) {
        temporary_results[index] = numerators[index] / denominators[index];

        if (!isfinite(temporary_results[index])) {
            free(temporary_results);
            return DIVIDE_NONFINITE_VALUE;
        }
    }

    for (index = 0U; index < numerator_count; ++index) {
        results[index] = temporary_results[index];
    }

    free(temporary_results);
    return DIVIDE_SUCCESS;
}

const char *divide_status_message(DivideStatus status)
{
    switch (status) {
        case DIVIDE_SUCCESS:
            return "success";
        case DIVIDE_INVALID_ARGUMENT:
            return "invalid argument";
        case DIVIDE_LENGTH_MISMATCH:
            return "list length mismatch";
        case DIVIDE_BY_ZERO:
            return "division by zero";
        case DIVIDE_NONFINITE_VALUE:
            return "non-finite value or result";
        case DIVIDE_ALLOCATION_FAILURE:
            return "memory allocation failure";
        default:
            return "unknown error";
    }
}

int main(void)
{
    const double numerators[] = {10.0, 20.0, 30.0, 40.0};
    const double denominators[] = {2.0, 4.0, 5.0, 8.0};
    double results[sizeof(numerators) / sizeof(numerators[0])];
    const size_t numerator_count = sizeof(numerators) / sizeof(numerators[0]);
    const size_t denominator_count = sizeof(denominators) / sizeof(denominators[0]);
    DivideStatus status;
    size_t index;

    status = divide_lists(
        numerators,
        numerator_count,
        denominators,
        denominator_count,
        results);

    if (status != DIVIDE_SUCCESS) {
        if (fprintf(stderr, "Division failed: %s\n",
                    divide_status_message(status)) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (index = 0U; index < numerator_count; ++index) {
        if (printf("%.6g%s",
                   results[index],
                   index + 1U == numerator_count ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}