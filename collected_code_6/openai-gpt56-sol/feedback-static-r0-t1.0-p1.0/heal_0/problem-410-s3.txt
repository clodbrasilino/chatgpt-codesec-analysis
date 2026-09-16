#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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

static bool value_to_long_double(const Value *value, long double *result)
{
    if (value == NULL || result == NULL) {
        return false;
    }

    switch (value->type) {
        case VALUE_INT:
            *result = (long double)value->data.i;
            return true;
        case VALUE_LONG:
            *result = (long double)value->data.l;
            return true;
        case VALUE_FLOAT:
            *result = (long double)value->data.f;
            return isfinite(*result);
        case VALUE_DOUBLE:
            *result = (long double)value->data.d;
            return isfinite(*result);
        default:
            return false;
    }
}

static bool find_minimum(const Value *values, size_t count, long double *minimum)
{
    long double current_minimum;

    if (values == NULL || minimum == NULL || count == 0U) {
        return false;
    }

    if (!value_to_long_double(&values[0], &current_minimum)) {
        return false;
    }

    for (size_t i = 1U; i < count; ++i) {
        long double current_value;

        if (!value_to_long_double(&values[i], &current_value)) {
            return false;
        }

        if (current_value < current_minimum) {
            current_minimum = current_value;
        }
    }

    *minimum = current_minimum;
    return true;
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
    long double minimum;

    if (!find_minimum(values, count, &minimum)) {
        fputs("Unable to find the minimum value.\n", stderr);
        return 1;
    }

    errno = 0;
    if (printf("Minimum: %Lg\n", minimum) < 0 || errno != 0) {
        fputs("Unable to write the result.\n", stderr);
        return 1;
    }

    return 0;
}