#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        double d;
        char c;
    } value;
} HeteroElement;

int find_max_value(const HeteroElement *list, size_t size, double *result) {
    double max_val;
    size_t i;
    double current;

    if (list == NULL || result == NULL || size == 0) {
        return -1;
    }

    switch (list[0].type) {
        case TYPE_INT:
            max_val = (double)list[0].value.i;
            break;
        case TYPE_FLOAT:
            max_val = (double)list[0].value.f;
            break;
        case TYPE_DOUBLE:
            max_val = list[0].value.d;
            break;
        case TYPE_CHAR:
            max_val = (double)list[0].value.c;
            break;
        default:
            return -1;
    }

    for (i = 1; i < size; i++) {
        switch (list[i].type) {
            case TYPE_INT:
                current = (double)list[i].value.i;
                break;
            case TYPE_FLOAT:
                current = (double)list[i].value.f;
                break;
            case TYPE_DOUBLE:
                current = list[i].value.d;
                break;
            case TYPE_CHAR:
                current = (double)list[i].value.c;
                break;
            default:
                return -1;
        }

        if (current > max_val) {
            max_val = current;
        }
    }

    *result = max_val;
    return 0;
}

int main(void) {
    HeteroElement list[5];
    double max_result;
    int status;

    list[0].type = TYPE_INT;
    list[0].value.i = 42;

    list[1].type = TYPE_FLOAT;
    list[1].value.f = 3.14f;

    list[2].type = TYPE_DOUBLE;
    list[2].value.d = 99.99;

    list[3].type = TYPE_CHAR;
    list[3].value.c = 'A';

    list[4].type = TYPE_INT;
    list[4].value.i = -10;

    status = find_max_value(list, 5, &max_result);

    if (status == 0) {
        printf("Maximum value: %f\n", max_result);
    } else {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}