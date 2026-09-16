#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE
} DataType;

typedef struct {
    DataType type;
    union {
        int int_val;
        double double_val;
    } data;
} HeteroValue;

int find_minimum(const HeteroValue *list, size_t size, double *result) {
    if (list == NULL || result == NULL || size == 0) {
        return -1;
    }

    double min_val;
    int min_found = 0;

    for (size_t i = 0; i < size; i++) {
        double current_val;

        switch (list[i].type) {
            case TYPE_INT:
                current_val = (double)list[i].data.int_val;
                break;
            case TYPE_DOUBLE:
                current_val = list[i].data.double_val;
                break;
            default:
                return -1;
        }

        if (!min_found || current_val < min_val) {
            min_val = current_val;
            min_found = 1;
        }
    }

    if (!min_found) {
        return -1;
    }

    *result = min_val;
    return 0;
}

int main(void) {
    HeteroValue list[] = {
        {.type = TYPE_INT, .data.int_val = 42},
        {.type = TYPE_DOUBLE, .data.double_val = 3.14},
        {.type = TYPE_INT, .data.int_val = -7},
        {.type = TYPE_DOUBLE, .data.double_val = 2.71},
        {.type = TYPE_INT, .data.int_val = 100}
    };

    size_t size = sizeof(list) / sizeof(list[0]);
    double min_value;

    if (find_minimum(list, size, &min_value) == 0) {
        printf("Minimum value: %f\n", min_value);
    } else {
        printf("Error: Could not find minimum value\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}