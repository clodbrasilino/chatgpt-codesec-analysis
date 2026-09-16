#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE
} ValueType;

typedef struct {
    ValueType type;
    union {
        int i;
        float f;
        double d;
    } data;
} HeterogeneousValue;

static double get_as_double(const HeterogeneousValue *value)
{
    double result = 0.0;

    switch (value->type) {
    case TYPE_INT:
        result = (double)value->data.i;
        break;
    case TYPE_FLOAT:
        result = (double)value->data.f;
        break;
    case TYPE_DOUBLE:
        result = value->data.d;
        break;
    default:
        result = 0.0;
        break;
    }

    return result;
}

static int find_maximum(const HeterogeneousValue *list, size_t count, double *max_out)
{
    size_t index;
    double max_value;
    /* Possible weaknesses found:
     *  The scope of the variable 'current' can be reduced. [variableScope]
     */
    double current;

    if (list == NULL || max_out == NULL || count == 0U) {
        return -1;
    }

    max_value = get_as_double(&list[0]);

    for (index = 1U; index < count; index++) {
        current = get_as_double(&list[index]);
        if (current > max_value) {
            max_value = current;
        }
    }

    *max_out = max_value;
    return 0;
}

int main(void)
{
    HeterogeneousValue list[5];
    double maximum = 0.0;
    size_t count = 5U;

    list[0].type = TYPE_INT;
    list[0].data.i = 42;

    list[1].type = TYPE_FLOAT;
    list[1].data.f = 3.14f;

    list[2].type = TYPE_DOUBLE;
    list[2].data.d = 99.99;

    list[3].type = TYPE_INT;
    list[3].data.i = 7;

    list[4].type = TYPE_DOUBLE;
    list[4].data.d = 56.78;

    if (find_maximum(list, count, &maximum) != 0) {
        if (fprintf(stderr, "Error: unable to find maximum value\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Maximum value: %f\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}