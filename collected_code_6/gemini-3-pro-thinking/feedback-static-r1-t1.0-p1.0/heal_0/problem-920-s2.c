#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *val1;
    void *val2;
    void *val3;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

int remove_empty_tuples(TupleList *list) {
    if (list == NULL || list->items == NULL) {
        return -1;
    }

    size_t keep_index = 0;
    
    for (size_t i = 0; i < list->count; i++) {
        if (list->items[i].val1 != NULL || 
            list->items[i].val2 != NULL || 
            list->items[i].val3 != NULL) {
            
            list->items[keep_index] = list->items[i];
            keep_index++;
        }
    }
    
    list->count = keep_index;

    if (list->count > 0) {
        Tuple *resized_items = realloc(list->items, list->count * sizeof(Tuple));
        if (resized_items != NULL) {
            list->items = resized_items;
            list->capacity = list->count;
        }
    } else {
        free(list->items);
        list->items = NULL;
        list->capacity = 0;
    }

    return 0;
}

int main(void) {
    TupleList list = {0};
    list.capacity = 5;
    list.count = 5;
    
    list.items = malloc(list.capacity * sizeof(Tuple));
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }

    list.items[0].val1 = NULL;
    list.items[0].val2 = NULL;
    list.items[0].val3 = NULL;

    list.items[1].val1 = "Data1";
    list.items[1].val2 = NULL;
    list.items[1].val3 = NULL;

    list.items[2].val1 = NULL;
    list.items[2].val2 = NULL;
    list.items[2].val3 = NULL;

    list.items[3].val1 = "Data2";
    list.items[3].val2 = "Data3";
    list.items[3].val3 = NULL;

    list.items[4].val1 = NULL;
    list.items[4].val2 = NULL;
    list.items[4].val3 = NULL;

    if (remove_empty_tuples(&list) != 0) {
        free(list.items);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.count; i++) {
        printf("%s %s %s\n", 
            list.items[i].val1 ? (char *)list.items[i].val1 : "None",
            list.items[i].val2 ? (char *)list.items[i].val2 : "None",
            list.items[i].val3 ? (char *)list.items[i].val3 : "None");
    }

    if (list.items != NULL) {
        free(list.items);
        list.items = NULL;
    }

    return EXIT_SUCCESS;
}