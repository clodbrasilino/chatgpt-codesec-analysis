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

static int value_to_long_double(const Value *value, long double *result)
{
    if (value == NULL || result == NULL) {
        return -1;
    }

    switch (value->type) {
        case VALUE_INT:
            *result = (long double)value->data.i;
            return 0;
        case VALUE_LONG:
            *result = (long double)value->data.l;
            return 0;
        case VALUE_FLOAT:
            if (isnan(value->data.f)) {
                return -1;
            }
            *result = (long double)value->data.f;
            return 0;
        case VALUE_DOUBLE:
            if (isnan(value->data.d)) {
                return -1;
            }
            *result = (long double)value->data.d;
            return 0;
        default:
            return -1;
    }
}

static int find_maximum(const Value *values, size_t count, long double *maximum)
{
    long double current;
    size_t i;

    if (values == NULL || maximum == NULL || count == 0U) {
        return -1;
    }

    if (value_to_long_double(&values[0], maximum) != 0) {
        return -1;
    }

    for (i = 1U; i < count; ++i) {
        if (value_to_long_double(&values[i], &current) != 0) {
            return -1;
        }

        if (current > *maximum) {
            *maximum = current;
        }
    }

    return 0;
}

int main(void)
{
    const Value values[] = {
        { .type = VALUE_INT, .data.i = 42 },
        { .type = VALUE_LONG, .data.l = 100000L },
        { .type = VALUE_FLOAT, .data.f = 83.5F },
        { .type = VALUE_DOUBLE, .data.d = 250000.75 }
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    long double maximum;

    errno = 0;

    if (find_maximum(values, count, &maximum) != 0) {
        if (fputs("Unable to determine the maximum value.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Maximum value: %Lg\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}