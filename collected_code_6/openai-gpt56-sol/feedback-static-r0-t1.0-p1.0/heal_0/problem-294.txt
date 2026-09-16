#include <float.h>
#include <math.h>
#include <stdbool.h>
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

static bool value_to_double(const Value *value, double *result)
{
    if (value == NULL || result == NULL) {
        return false;
    }

    switch (value->type) {
        case VALUE_INT:
            *result = (double)value->data.i;
            return true;
        case VALUE_LONG:
            *result = (double)value->data.l;
            return true;
        case VALUE_FLOAT:
            *result = (double)value->data.f;
            return true;
        case VALUE_DOUBLE:
            *result = value->data.d;
            return true;
        default:
            return false;
    }
}

static bool find_maximum(const Value *values, size_t count, double *maximum)
{
    double current;
    bool found = false;

    if (values == NULL || maximum == NULL || count == 0U) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (!value_to_double(&values[i], &current)) {
            return false;
        }

        if (isnan(current)) {
            continue;
        }

        if (!found || current > *maximum) {
            *maximum = current;
            found = true;
        }
    }

    return found;
}

int main(void)
{
    const Value values[] = {
        { .type = VALUE_INT, .data.i = 42 },
        { .type = VALUE_LONG, .data.l = 1000000L },
        { .type = VALUE_FLOAT, .data.f = 3.5F },
        { .type = VALUE_DOUBLE, .data.d = DBL_MAX }
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    double maximum;

    if (!find_maximum(values, count, &maximum)) {
        fputs("Unable to determine the maximum value.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Maximum: %.17g\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}