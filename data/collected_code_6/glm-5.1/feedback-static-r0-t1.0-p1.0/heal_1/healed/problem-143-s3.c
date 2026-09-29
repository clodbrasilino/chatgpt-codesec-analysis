#include <stdlib.h>
#include <stdio.h>

typedef enum {
    TYPE_INT,
    TYPE_LIST
} ElementType;

typedef struct {
    ElementType type;
    void *data;
} TupleItem;

typedef struct {
    int *items;
    size_t count;
} List;

typedef struct {
    TupleItem *items;
    size_t count;
} Tuple;

size_t count_lists_in_tuple(const Tuple *tuple) {
    if (tuple == NULL) {
        return 0;
    }

    size_t list_count = 0;
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->items[i].type == TYPE_LIST) {
            list_count++;
        }
    }
    return list_count;
}

int main(void) {
    TupleItem items[4];

    items[0].type = TYPE_INT;
    int val1 = 10;
    items[0].data = &val1;

    items[1].type = TYPE_LIST;
    int list1_items[] = {1, 2, 3};
    List list1 = { list1_items, 3 };
    items[1].data = &list1;

    items[2].type = TYPE_INT;
    int val2 = 20;
    items[2].data = &val2;

    items[3].type = TYPE_LIST;
    int list2_items[] = {4, 5, 6};
    List list2 = { list2_items, 3 };
    items[3].data = &list2;

    Tuple tuple = { items, 4 };

    size_t result = count_lists_in_tuple(&tuple);
    printf("%zu\n", result);

    return 0;
}