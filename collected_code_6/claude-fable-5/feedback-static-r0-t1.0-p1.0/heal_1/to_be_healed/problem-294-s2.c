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
    } data;
} HeteroValue;

static double value_as_double(const HeteroValue *value)
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

static bool find_max(const HeteroValue *list, size_t count, double *max_out)
{
    size_t idx;
    double max_val;
    /* Possible weaknesses found:
     *  The scope of the variable 'current' can be reduced. [variableScope]
     */
    double current;

    if (list == NULL || max_out == NULL || count == 0U) {
        return false;
    }

    max_val = value_as_double(&list[0]);

    for (idx = 1U; idx < count; idx++) {
        current = value_as_double(&list[idx]);
        if (current > max_val) {
            max_val = current;
        }
    }

    *max_out = max_val;
    return true;
}

int main(void)
{
    HeteroValue *list;
    size_t count = 5U;
    double max_val = 0.0;
    int exit_code = EXIT_SUCCESS;

    list = malloc(count * sizeof(*list));
    if (list == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    list[0].type = TYPE_INT;
    list[0].data.i = 42;
    list[1].type = TYPE_FLOAT;
    list[1].data.f = 3.14f;
    list[2].type = TYPE_DOUBLE;
    list[2].data.d = 99.99;
    list[3].type = TYPE_INT;
    list[3].data.i = 7;
    list[4].type = TYPE_DOUBLE;
    list[4].data.d = 56.5;

    if (find_max(list, count, &max_val)) {
        if (printf("Maximum value: %f\n", max_val) < 0) {
            exit_code = EXIT_FAILURE;
        }
    } else {
        (void)fprintf(stderr, "Failed to find maximum value\n");
        exit_code = EXIT_FAILURE;
    }

    free(list);
    list = NULL;

    return exit_code;
}