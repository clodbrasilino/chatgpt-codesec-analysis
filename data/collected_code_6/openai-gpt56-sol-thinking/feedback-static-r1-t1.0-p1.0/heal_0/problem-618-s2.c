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

DivideStatus divide_lists(const double *numerators,
                          size_t numerator_count,
                          const double *denominators,
                          size_t denominator_count,
                          double **result,
                          size_t *result_count)
{
    double *values;
    size_t i;

    if (result == NULL || result_count == NULL) {
        return DIVIDE_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0;

    if (numerator_count != denominator_count) {
        return DIVIDE_LENGTH_MISMATCH;
    }

    if (numerator_count == 0) {
        return DIVIDE_SUCCESS;
    }

    if (numerators == NULL || denominators == NULL) {
        return DIVIDE_INVALID_ARGUMENT;
    }

    if (numerator_count > SIZE_MAX / sizeof(*values)) {
        return DIVIDE_ALLOCATION_FAILURE;
    }

    values = malloc(numerator_count * sizeof(*values));
    if (values == NULL) {
        return DIVIDE_ALLOCATION_FAILURE;
    }

    for (i = 0; i < numerator_count; ++i) {
        if (!isfinite(numerators[i]) || !isfinite(denominators[i])) {
            free(values);
            return DIVIDE_NONFINITE_VALUE;
        }

        if (denominators[i] == 0.0) {
            free(values);
            return DIVIDE_BY_ZERO;
        }

        values[i] = numerators[i] / denominators[i];

        if (!isfinite(values[i])) {
            free(values);
            return DIVIDE_NONFINITE_VALUE;
        }
    }

    *result = values;
    *result_count = numerator_count;
    return DIVIDE_SUCCESS;
}

const char *divide_status_string(DivideStatus status)
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
            return "non-finite value";
        case DIVIDE_ALLOCATION_FAILURE:
            return "allocation failure";
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
    size_t result_count = 0;
    size_t i;
    DivideStatus status;

    status = divide_lists(numerators,
                          numerator_count,
                          denominators,
                          denominator_count,
                          &result,
                          &result_count);

    if (status != DIVIDE_SUCCESS) {
        fprintf(stderr, "Division failed: %s\n", divide_status_string(status));
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; ++i) {
        if (printf("%.17g%s",
                   result[i],
                   i + 1 < result_count ? " " : "\n") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}