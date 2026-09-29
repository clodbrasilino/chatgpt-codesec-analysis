#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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
} ListNode;

double get_value(const ListNode *node) {
    if (!node) {
        return 0.0;
    }
    switch (node->type) {
        case TYPE_INT:
            return (double)node->data.i_val;
        case TYPE_FLOAT:
            return (double)node->data.f_val;
        case TYPE_DOUBLE:
            return node->data.d_val;
        default:
            return 0.0;
    }
}

int find_maximum(const ListNode *list, size_t length, double *max_val) {
    if (list == NULL || length == 0 || max_val == NULL) {
        return -1;
    }

    *max_val = get_value(&list[0]);

    for (size_t i = 1; i < length; i++) {
        double current_val = get_value(&list[i]);
        if (current_val > *max_val) {
            *max_val = current_val;
        }
    }

    return 0;
}

int main(void) {
    ListNode list[4];

    list[0].type = TYPE_INT;
    list[0].data.i_val = 42;

    list[1].type = TYPE_FLOAT;
    list[1].data.f_val = 3.14f;

    list[2].type = TYPE_DOUBLE;
    list[2].data.d_val = -100.5;

    list[3].type = TYPE_INT;
    list[3].data.i_val = 55;

    double max_value = 0.0;
    if (find_maximum(list, 4, &max_value) == 0) {
        printf("Maximum value: %f\n", max_value);
    } else {
        printf("Failed to find maximum value.\n");
    }

    return 0;
}