#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE
} ElementType;

typedef struct {
    ElementType type;
    union {
        int i;
        float f;
        double d;
    } data;
} ListElement;

double find_max_value(const ListElement* list, size_t size) {
    if (list == NULL || size == 0) {
        fprintf(stderr, "Invalid input to find_max_value\n");
        return -1.0; 
    }

    double max_val = -DBL_MAX;

    for (size_t i = 0; i < size; ++i) {
        double current_val = 0.0;
        switch (list[i].type) {
            case TYPE_INT:
                current_val = (double)list[i].data.i;
                break;
            case TYPE_FLOAT:
                current_val = (double)list[i].data.f;
                break;
            case TYPE_DOUBLE:
                current_val = list[i].data.d;
                break;
            default:
                fprintf(stderr, "Unknown element type at index %zu\n", i);
                return -1.0; 
        }

        if (current_val > max_val) {
            max_val = current_val;
        }
    }

    return max_val;
}

int main(void) {
    ListElement list[] = {
        {TYPE_INT, .data.i = 42},
        {TYPE_FLOAT, .data.f = 3.14f},
        {TYPE_DOUBLE, .data.d = 99.99},
        {TYPE_INT, .data.i = -10}
    };

    size_t size = sizeof(list) / sizeof(list[0]);

    double max_value = find_max_value(list, size);

    printf("The maximum value is: %f\n", max_value);

    return 0;
}