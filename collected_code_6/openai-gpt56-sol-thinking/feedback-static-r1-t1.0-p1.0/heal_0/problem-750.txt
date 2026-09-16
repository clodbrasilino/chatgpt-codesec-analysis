#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *items;
    size_t length;
    size_t capacity;
} TupleList;

bool tuple_list_add(TupleList *list, Tuple tuple)
{
    Tuple *resized_items;
    size_t new_capacity;
    const size_t max_capacity = SIZE_MAX / sizeof(*list->items);

    if (list == NULL ||
        list->length > list->capacity ||
        (list->capacity > 0 && list->items == NULL) ||
        list->capacity > max_capacity) {
        return false;
    }

    if (list->length == list->capacity) {
        if (list->capacity >= max_capacity) {
            return false;
        }

        if (list->capacity == 0) {
            new_capacity = max_capacity < 4 ? max_capacity : 4;
        } else if (list->capacity > max_capacity / 2) {
            new_capacity = max_capacity;
        } else {
            new_capacity = list->capacity * 2;
        }

        resized_items = realloc(list->items,
                                new_capacity * sizeof(*list->items));
        if (resized_items == NULL) {
            return false;
        }

        list->items = resized_items;
        list->capacity = new_capacity;
    }

    list->items[list->length] = tuple;
    ++list->length;

    return true;
}

void tuple_list_destroy(TupleList *list)
{
    if (list != NULL) {
        free(list->items);
        list->items = NULL;
        list->length = 0;
        list->capacity = 0;
    }
}

int main(void)
{
    TupleList list = {NULL, 0, 0};
    const Tuple tuple = {10, 20};

    if (!tuple_list_add(&list, tuple)) {
        if (fputs("Failed to add tuple\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("(%d, %d)\n", list.items[0].first,
               list.items[0].second) < 0) {
        tuple_list_destroy(&list);
        return EXIT_FAILURE;
    }

    tuple_list_destroy(&list);
    return EXIT_SUCCESS;
}