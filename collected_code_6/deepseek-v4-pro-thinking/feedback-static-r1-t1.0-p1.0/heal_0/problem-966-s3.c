#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *data;
    size_t length;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

int tuple_list_init(TupleList *list, size_t capacity) {
    if (!list) {
        return -1;
    }
    if (capacity == 0) {
        capacity = 4;
    }
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
    Tuple *items = malloc(capacity * sizeof(Tuple));
    if (!items) {
        return -1;
    }
    list->items = items;
    list->capacity = capacity;
    return 0;
}

void tuple_list_free(TupleList *list) {
    if (!list) {
        return;
    }
    for (size_t i = 0; i < list->count; ++i) {
        free(list->items[i].data);
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

int tuple_list_add(TupleList *list, void *data, size_t length) {
    if (!list) {
        return -1;
    }
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        if (new_capacity == 0) {
            new_capacity = 4;
        }
        Tuple *new_items = realloc(list->items, new_capacity * sizeof(Tuple));
        if (!new_items) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count].data = data;
    list->items[list->count].length = length;
    ++list->count;
    return 0;
}

size_t remove_empty_tuples(TupleList *list) {
    if (!list) {
        return 0;
    }
    size_t write = 0;
    size_t removed = 0;
    for (size_t read = 0; read < list->count; ++read) {
        if (list->items[read].length == 0) {
            free(list->items[read].data);
            list->items[read].data = NULL;
            ++removed;
        } else {
            if (write != read) {
                list->items[write] = list->items[read];
            }
            ++write;
        }
    }
    list->count = write;
    return removed;
}

int main(void) {
    TupleList list;
    if (tuple_list_init(&list, 4) != 0) {
        return EXIT_FAILURE;
    }

    int *data1 = malloc(3 * sizeof(int));
    if (!data1) {
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }
    data1[0] = 1;
    data1[1] = 2;
    data1[2] = 3;
    if (tuple_list_add(&list, data1, 3) != 0) {
        free(data1);
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }

    if (tuple_list_add(&list, NULL, 0) != 0) {
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }

    int *data2 = malloc(2 * sizeof(int));
    if (!data2) {
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }
    data2[0] = 4;
    data2[1] = 5;
    if (tuple_list_add(&list, data2, 2) != 0) {
        free(data2);
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }

    remove_empty_tuples(&list);

    for (size_t i = 0; i < list.count; ++i) {
        int *values = (int *)list.items[i].data;
        printf("Tuple %zu: ", i);
        for (size_t j = 0; j < list.items[i].length; ++j) {
            if (j > 0) {
                printf(" ");
            }
            printf("%d", values[j]);
        }
        printf("\n");
    }

    tuple_list_free(&list);
    return EXIT_SUCCESS;
}