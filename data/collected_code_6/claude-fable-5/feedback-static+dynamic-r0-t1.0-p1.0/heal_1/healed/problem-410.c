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
} Element;

static double element_as_double(const Element *elem)
{
    double result = 0.0;

    switch (elem->type) {
    case TYPE_INT:
        result = (double)elem->data.i;
        break;
    case TYPE_FLOAT:
        result = (double)elem->data.f;
        break;
    case TYPE_DOUBLE:
        result = elem->data.d;
        break;
    default:
        result = 0.0;
        break;
    }

    return result;
}

static int find_minimum(const Element *list, size_t count, double *min_out)
{
    size_t idx;
    double minimum;

    if ((list == NULL) || (min_out == NULL) || (count == 0U)) {
        return -1;
    }

    minimum = element_as_double(&list[0]);

    for (idx = 1U; idx < count; idx++) {
        double current = element_as_double(&list[idx]);
        if (current < minimum) {
            minimum = current;
        }
    }

    *min_out = minimum;
    return 0;
}

int main(void)
{
    Element *list;
    size_t count = 5U;
    double minimum = 0.0;
    int status;

    list = malloc(count * sizeof(Element));
    if (list == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    list[0].type = TYPE_INT;
    list[0].data.i = 42;

    list[1].type = TYPE_FLOAT;
    list[1].data.f = 3.14f;

    list[2].type = TYPE_DOUBLE;
    list[2].data.d = -7.5;

    list[3].type = TYPE_INT;
    list[3].data.i = 100;

    list[4].type = TYPE_DOUBLE;
    list[4].data.d = 0.001;

    status = find_minimum(list, count, &minimum);
    if (status != 0) {
        (void)fprintf(stderr, "Failed to find minimum\n");
        free(list);
        return EXIT_FAILURE;
    }

    if (printf("Minimum value: %f\n", minimum) < 0) {
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}