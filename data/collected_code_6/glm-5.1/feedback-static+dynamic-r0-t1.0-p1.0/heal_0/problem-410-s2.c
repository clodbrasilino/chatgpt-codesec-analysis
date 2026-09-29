#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE
} ItemType;

typedef struct {
    ItemType type;
    union {
        int int_val;
        float float_val;
        double double_val;
    } data;
} ListItem;

typedef struct {
    ListItem *items;
    size_t count;
} List;

double find_minimum(List *list) {
    if (list == NULL || list->count == 0 || list->items == NULL) {
        return 0.0;
    }

    double min_val = (double) INT_MAX;

    for (size_t i = 0; i < list->count; i++) {
        double current_val;

        switch (list->items[i].type) {
            case TYPE_INT:
                current_val = (double) list->items[i].data.int_val;
                break;
            case TYPE_FLOAT:
                current_val = (double) list->items[i].data.float_val;
                break;
            case TYPE_DOUBLE:
                current_val = list->items[i].data.double_val;
                break;
            default:
                current_val = min_val;
                break;
        }

        if (current_val < min_val) {
            min_val = current_val;
        }
    }

    return min_val;
}

int main(void) {
    List list;
    list.count = 5;
    list.items = (ListItem *)malloc(list.count * sizeof(ListItem));

    if (list.items == NULL) {
        return EXIT_FAILURE;
    }

    list.items[0].type = TYPE_INT;
    list.items[0].data.int_val = 10;

    list.items[1].type = TYPE_FLOAT;
    list.items[1].data.float_val = -5.25f;

    list.items[2].type = TYPE_DOUBLE;
    list.items[2].data.double_val = 3.14159;

    list.items[3].type = TYPE_INT;
    list.items[3].data.int_val = -20;

    list.items[4].type = TYPE_FLOAT;
    list.items[4].data.float_val = 0.0f;

    double minimum = find_minimum(&list);

    printf("%f\n", minimum);

    free(list.items);
    list.items = NULL;

    return EXIT_SUCCESS;
}