#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_LONG
} ValueType;

typedef struct {
    ValueType type;
    union {
        int i;
        double d;
        long l;
    } value;
} ListItem;

static bool get_numeric_value(const ListItem *item, double *result) {
    if (item == NULL || result == NULL) {
        return false;
    }
    
    switch (item->type) {
        case TYPE_INT:
            *result = (double)item->value.i;
            return true;
        case TYPE_DOUBLE:
            *result = item->value.d;
            return true;
        case TYPE_LONG:
            *result = (double)item->value.l;
            return true;
        default:
            return false;
    }
}

static bool find_minimum(const ListItem *list, size_t count, double *min_value) {
    if (list == NULL || min_value == NULL || count == 0) {
        return false;
    }
    
    double current_min;
    if (!get_numeric_value(&list[0], &current_min)) {
        return false;
    }
    
    for (size_t i = 1; i < count; i++) {
        double val;
        if (!get_numeric_value(&list[i], &val)) {
            return false;
        }
        if (val < current_min) {
            current_min = val;
        }
    }
    
    *min_value = current_min;
    return true;
}

int main(void) {
    ListItem items[] = {
        {.type = TYPE_INT, .value.i = 42},
        {.type = TYPE_DOUBLE, .value.d = 3.14},
        {.type = TYPE_LONG, .value.l = -100L},
        {.type = TYPE_INT, .value.i = 7},
        {.type = TYPE_DOUBLE, .value.d = -2.5}
    };
    
    size_t count = sizeof(items) / sizeof(items[0]);
    double min_val;
    
    if (find_minimum(items, count, &min_val)) {
        printf("Minimum value: %.2f\n", min_val);
        return EXIT_SUCCESS;
    }
    
    fprintf(stderr, "Error: Could not determine minimum value\n");
    return EXIT_FAILURE;
}