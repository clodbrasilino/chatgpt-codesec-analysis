#include <float.h>
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
    DIVIDE_OUT_OF_RANGE,
    DIVIDE_ALLOCATION_FAILURE
} DivideStatus;

DivideStatus divide_lists(const double *numerators,
                          size_t numerator_count,
                          const double *denominators,
                          size_t denominator_count,
                          double **result)
{
    double *values;
    size_t i;

    if (result == NULL) {
        return DIVIDE_INVALID_ARGUMENT;
    }

    *result = NULL;

    if (numerator_count != denominator_count) {
        return DIVIDE_LENGTH_MISMATCH;
    }

    if (numerator_count == 0U) {
        return DIVIDE_SUCCESS;
    }

    if (numerators == NULL || denominators == NULL) {
        return DIVIDE_INVALID_ARGUMENT;
    }

    if (numerator_count > SIZE_MAX / sizeof(*values)) {
        return DIVIDE_OUT_OF_RANGE;
    }

    values = malloc(numerator_count * sizeof(*values));
    if (values == NULL) {
        return DIVIDE_ALLOCATION_FAILURE;
    }

    for (i = 0U; i < numerator_count; ++i) {
        long double quotient;

        if (!isfinite(numerators[i]) || !isfinite(denominators[i])) {
            free(values);
            return DIVIDE_NONFINITE_VALUE;
        }

        if (denominators[i] == 0.0) {
            free(values);
            return DIVIDE_BY_ZERO;
        }

        quotient = (long double)numerators[i] / (long double)denominators[i];

        if (!isfinite(quotient) ||
            quotient > (long double)DBL_MAX ||
            quotient < -(long double)DBL_MAX) {
            free(values);
            return DIVIDE_OUT_OF_RANGE;
        }

        values[i] = (double)quotient;
    }

    *result = values;
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
            return "non-finite input value";
        case DIVIDE_OUT_OF_RANGE:
            return "result out of range";
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
    const size_t numerator_count =
        sizeof(numerators) / sizeof(numerators[0]);
    const size_t denominator_count =
        sizeof(denominators) / sizeof(denominators[0]);
    double *result = NULL;
    DivideStatus status;
    size_t i;

    status = divide_lists(numerators,
                          numerator_count,
                          denominators,
                          denominator_count,
                          &result);

    if (status != DIVIDE_SUCCESS) {
        fprintf(stderr, "Division failed: %s\n",
                divide_status_message(status));
        return EXIT_FAILURE;
    }

    for (i = 0U; i < numerator_count; ++i) {
        printf("%.17g\n", result[i]);
    }

    free(result);
    return EXIT_SUCCESS;
}