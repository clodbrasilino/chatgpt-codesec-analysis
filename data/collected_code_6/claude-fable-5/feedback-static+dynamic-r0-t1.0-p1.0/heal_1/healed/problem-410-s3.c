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
        break;
    }

    return result;
}

int find_minimum(const HeterogeneousItem *list, size_t count, double *min_out)
{
    size_t idx;
    double minimum;

    if (list == NULL || min_out == NULL || count == 0U) {
        return -1;
    }

    minimum = item_as_double(&list[0]);

    for (idx = 1U; idx < count; idx++) {
        const double current = item_as_double(&list[idx]);
        if (current < minimum) {
            minimum = current;
        }
    }

    *min_out = minimum;
    return 0;
}

int main(void)
{
    HeterogeneousItem items[5];
    double minimum = 0.0;
    int status;

    items[0].type = TYPE_INT;
    items[0].value.i = 42;

    items[1].type = TYPE_FLOAT;
    items[1].value.f = 3.14f;

    items[2].type = TYPE_DOUBLE;
    items[2].value.d = -7.5;

    items[3].type = TYPE_INT;
    items[3].value.i = -2;

    items[4].type = TYPE_DOUBLE;
    items[4].value.d = 100.25;

    status = find_minimum(items, sizeof(items) / sizeof(items[0]), &minimum);

    if (status != 0) {
        fprintf(stderr, "Error: could not compute minimum\n");
        return EXIT_FAILURE;
    }

    printf("Minimum value: %f\n", minimum);

    return EXIT_SUCCESS;
}