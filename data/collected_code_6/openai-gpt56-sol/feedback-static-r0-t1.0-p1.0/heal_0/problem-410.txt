#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    VALUE_CHAR,
    VALUE_INT,
    VALUE_LONG,
    VALUE_FLOAT,
    VALUE_DOUBLE
} ValueType;

typedef struct {
    ValueType type;
    union {
        char as_char;
        int as_int;
        long as_long;
        float as_float;
        double as_double;
    } data;
} Value;

static bool value_to_long_double(const Value *value, long double *result)
{
    if (value == NULL || result == NULL) {
        return false;
    }

    switch (value->type) {
        case VALUE_CHAR:
            *result = (long double)value->data.as_char;
            return true;
        case VALUE_INT:
            *result = (long double)value->data.as_int;
            return true;
        case VALUE_LONG:
            *result = (long double)value->data.as_long;
            return true;
        case VALUE_FLOAT:
            if (!isfinite(value->data.as_float)) {
                return false;
            }
            *result = (long double)value->data.as_float;
            return true;
        case VALUE_DOUBLE:
            if (!isfinite(value->data.as_double)) {
                return false;
            }
            *result = (long double)value->data.as_double;
            return true;
        default:
            return false;
    }
}

static bool find_minimum(const Value *values, size_t count, long double *minimum)
{
    long double current;
    size_t i;

    if (values == NULL || minimum == NULL || count == 0U) {
        return false;
    }

    if (!value_to_long_double(&values[0], minimum)) {
        return false;
    }

    for (i = 1U; i < count; ++i) {
        if (!value_to_long_double(&values[i], &current)) {
            return false;
        }

        if (current < *minimum) {
            *minimum = current;
        }
    }

    return true;
}

int main(void)
{
    const Value values[] = {
        { .type = VALUE_INT, .data.as_int = 42 },
        { .type = VALUE_DOUBLE, .data.as_double = -7.25 },
        { .type = VALUE_CHAR, .data.as_char = 3 },
        { .type = VALUE_LONG, .data.as_long = 1000L },
        { .type = VALUE_FLOAT, .data.as_float = -2.5F }
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    long double minimum;

    if (!find_minimum(values, count, &minimum)) {
        fputs("Unable to determine the minimum value.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Minimum: %Lg\n", minimum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}