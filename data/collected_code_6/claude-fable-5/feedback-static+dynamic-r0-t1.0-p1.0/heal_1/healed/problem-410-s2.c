#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    } value;
} HeterogeneousItem;

static double item_as_double(const HeterogeneousItem *item)
{
    double result = 0.0;

    switch (item->type) {
    case TYPE_INT:
        result = (double)item->value.i;
        break;
    case TYPE_FLOAT:
        result = (double)item->value.f;
        break;
    case TYPE_DOUBLE:
        result = item->value.d;
        break;
    default:
        result = 0.0;
        break;
    }

    return result;
}

bool find_minimum(const HeterogeneousItem *list, size_t count, double *out_min)
{
    size_t idx;
    double minimum;

    if ((list == NULL) || (out_min == NULL) || (count == 0U)) {
        return false;
    }

    minimum = item_as_double(&list[0]);

    for (idx = 1U; idx < count; idx++) {
        const double current = item_as_double(&list[idx]);
        if (current < minimum) {
            minimum = current;
        }
    }

    *out_min = minimum;
    return true;
}

int main(void)
{
    HeterogeneousItem list[5];
    double minimum = 0.0;
    size_t count = 5U;

    list[0].type = TYPE_INT;
    list[0].value.i = 42;

    list[1].type = TYPE_FLOAT;
    list[1].value.f = 3.14f;

    list[2].type = TYPE_DOUBLE;
    list[2].value.d = -7.5;

    list[3].type = TYPE_INT;
    list[3].value.i = -2;

    list[4].type = TYPE_DOUBLE;
    list[4].value.d = 100.25;

    if (find_minimum(list, count, &minimum)) {
        if (printf("Minimum value: %f\n", minimum) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "Error: could not compute minimum\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}