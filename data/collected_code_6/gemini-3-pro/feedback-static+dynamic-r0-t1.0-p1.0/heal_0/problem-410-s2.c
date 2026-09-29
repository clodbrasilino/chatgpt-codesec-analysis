#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE
} ElementType;

typedef struct {
    ElementType type;
    union {
        int i_val;
        float f_val;
        double d_val;
    } data;
} HeterogeneousElement;

typedef struct {
    HeterogeneousElement *elements;
    size_t size;
} HeterogeneousList;

double get_min_value(const HeterogeneousList *list, int *status) {
    if (list == NULL || list->elements == NULL || list->size == 0) {
        if (status != NULL) {
            *status = -1;
        }
        return 0.0;
    }

    double min_val = DBL_MAX;
    int found = 0;

    for (size_t i = 0; i < list->size; i++) {
        double current_val = 0.0;
        switch (list->elements[i].type) {
            case TYPE_INT:
                current_val = (double)list->elements[i].data.i_val;
                break;
            case TYPE_FLOAT:
                current_val = (double)list->elements[i].data.f_val;
                break;
            case TYPE_DOUBLE:
                current_val = list->elements[i].data.d_val;
                break;
            default:
                continue;
        }

        if (!found || current_val < min_val) {
            min_val = current_val;
            found = 1;
        }
    }

    if (!found) {
        if (status != NULL) {
            *status = -1;
        }
        return 0.0;
    }

    if (status != NULL) {
        *status = 0;
    }
    return min_val;
}

int main(void) {
    HeterogeneousList list;
    list.size = 4;
    list.elements = (HeterogeneousElement *)malloc(list.size * sizeof(HeterogeneousElement));

    if (list.elements == NULL) {
        return 1;
    }

    list.elements[0].type = TYPE_INT;
    list.elements[0].data.i_val = 10;

    list.elements[1].type = TYPE_FLOAT;
    list.elements[1].data.f_val = 3.14f;

    list.elements[2].type = TYPE_DOUBLE;
    list.elements[2].data.d_val = -2.5;

    list.elements[3].type = TYPE_INT;
    list.elements[3].data.i_val = 7;

    int status = 0;
    double min_val = get_min_value(&list, &status);

    if (status == 0) {
        printf("Minimum value: %f\n", min_val);
    } else {
        printf("Failed to find minimum value.\n");
    }

    free(list.elements);
    list.elements = NULL;

    return 0;
}