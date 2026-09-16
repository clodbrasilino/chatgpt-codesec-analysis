#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} TupleItemType;

typedef struct {
    TupleItemType type;
    union {
        int i;
        float f;
        char *s;
    } data;
} TupleItem;

typedef struct {
    size_t size;
    TupleItem *items;
} Tuple;

int get_tuple_item(const Tuple *tuple, size_t index, TupleItem *out_item) {
    if (tuple == NULL || tuple->items == NULL || out_item == NULL) {
        return -1;
    }

    if (index >= tuple->size) {
        return -1;
    }

    *out_item = tuple->items[index];
    return 0;
}

int main(void) {
    TupleItem items[3];
    items[0].type = TYPE_INT;
    items[0].data.i = 42;

    items[1].type = TYPE_FLOAT;
    items[1].data.f = 3.14f;

    items[2].type = TYPE_STRING;
    items[2].data.s = "Hello";

    Tuple tuple = {3, items};

    TupleItem retrieved_item;
    
    if (get_tuple_item(&tuple, 1, &retrieved_item) == 0) {
        if (retrieved_item.type == TYPE_FLOAT) {
            printf("Item 1 is float: %f\n", retrieved_item.data.f);
        }
    } else {
        printf("Failed to retrieve item.\n");
    }

    if (get_tuple_item(&tuple, 5, &retrieved_item) != 0) {
        printf("Out of bounds index successfully caught.\n");
    }

    return 0;
}