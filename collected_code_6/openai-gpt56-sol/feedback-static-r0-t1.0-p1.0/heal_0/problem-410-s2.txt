#include <errno.h>
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    VALUE_INT,
    VALUE_LONG,
    VALUE_FLOAT,
    VALUE_DOUBLE
} ValueType;

typedef struct {
    ValueType type;
    union {
        int i;
        long l;
        float f;
        double d;
    } data;
} Value;

static int value_to_double(const Value *value, double *result)
{
    if (value == NULL || result == NULL) {
        return 0;
    }

    switch (value->type) {
        case VALUE_INT:
            *result = (double)value->data.i;
            return 1;
        case VALUE_LONG:
            *result = (double)value->data.l;
            return 1;
        case VALUE_FLOAT:
            *result = (double)value->data.f;
            return isfinite(*result);
        case VALUE_DOUBLE:
            *result = value->data.d;
            return isfinite(*result);
        default:
            return 0;
    }
}

static int find_minimum(const Value *values, size_t count, double *minimum)
{
    double current_minimum;
    size_t i;

    if (values == NULL || minimum == NULL || count == 0U) {
        return 0;
    }

    if (!value_to_double(&values[0], &current_minimum)) {
        return 0;
    }

    for (i = 1U; i < count; ++i) {
        double current_value;

        if (!value_to_double(&values[i], &current_value)) {
            return 0;
        }

        if (current_value < current_minimum) {
            current_minimum = current_value;
        }
    }

    *minimum = current_minimum;
    return 1;
}

int main(void)
{
    const Value values[] = {
        { .type = VALUE_INT, .data.i = 42 },
        { .type = VALUE_DOUBLE, .data.d = -7.25 },
        { .type = VALUE_LONG, .data.l = 1000L },
        { .type = VALUE_FLOAT, .data.f = 3.5F }
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    double minimum;

    errno = 0;

    if (!find_minimum(values, count, &minimum)) {
        if (fprintf(stderr, "Unable to determine the minimum value.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Minimum: %.17g\n", minimum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}