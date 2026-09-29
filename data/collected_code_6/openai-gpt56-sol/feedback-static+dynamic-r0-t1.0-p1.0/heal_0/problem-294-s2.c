#include <float.h>
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
            if (!isfinite(value->data.f)) {
                return false;
            }
            *result = (long double)value->data.f;
            return true;
        case VALUE_DOUBLE:
            if (!isfinite(value->data.d)) {
                return false;
            }
            *result = (long double)value->data.d;
            return true;
        default:
            return false;
    }
}

static bool find_maximum(const Value *values, size_t count, long double *maximum)
{
    long double current;
    size_t i;

    if (values == NULL || maximum == NULL || count == 0U) {
        return false;
    }

    if (!value_to_long_double(&values[0], maximum)) {
        return false;
    }

    for (i = 1U; i < count; ++i) {
        if (!value_to_long_double(&values[i], &current)) {
            return false;
        }

        if (current > *maximum) {
            *maximum = current;
        }
    }

    return true;
}

int main(void)
{
    const Value values[] = {
        { .type = VALUE_INT, .data.i = 42 },
        { .type = VALUE_LONG, .data.l = 900000L },
        { .type = VALUE_FLOAT, .data.f = 17.5F },
        { .type = VALUE_DOUBLE, .data.d = 1234567.89 }
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    long double maximum;

    if (!find_maximum(values, count, &maximum)) {
        fputs("Unable to find the maximum value.\n", stderr);
        return 1;
    }

    if (printf("Maximum: %.*Lg\n", LDBL_DECIMAL_DIG, maximum) < 0) {
        return 1;
    }

    return 0;
}