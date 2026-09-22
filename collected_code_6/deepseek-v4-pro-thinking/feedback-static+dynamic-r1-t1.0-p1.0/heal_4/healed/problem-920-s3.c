#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **values;
    size_t size;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

int tuple_init(Tuple *tuple, size_t size, void **values) {
    if (!tuple) return 0;
    tuple->size = 0;
    tuple->values = NULL;
    if (size == 0) return 1;
    if (size > SIZE_MAX / sizeof(void *)) return 0;
    tuple->values = malloc(size * sizeof(void *));
    if (!tuple->values) return 0;
    for (size_t i = 0; i < size; ++i) {
        tuple->values[i] = values ? values[i] : NULL;
    }
    tuple->size = size;
    return 1;
}

void tuple_destroy(Tuple *tuple) {
    if (!tuple) return;
    free(tuple->values);
    tuple->values = NULL;
    tuple->size = 0;
}

int tuple_list_init(TupleList *list, size_t capacity) {
    if (!list) return 0;
    if (capacity == 0) {
        list->items = NULL;
        list->count = 0;
        list->capacity = 0;
        return 1;
    }
    if (capacity > SIZE_MAX / sizeof(Tuple)) return 0;
    list->items = malloc(capacity * sizeof(Tuple));
    if (!list->items) {
        list->count = 0;
        list->capacity = 0;
        return 0;
    }
    list->count = 0;
    list->capacity = capacity;
    return 1;
}

void tuple_list_destroy(TupleList *list) {
    if (!list) return;
    for (size_t i = 0; i < list->count; ++i) {
        tuple_destroy(&list->items[i]);
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

int tuple_list_add(TupleList *list, Tuple *tuple) {
    if (!list || !tuple) return 0;
    if (list->count == list->capacity) {
        size_t new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(Tuple)) return 0;
        Tuple *new_items = realloc(list->items, new_capacity * sizeof(Tuple));
        if (!new_items) return 0;
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count] = *tuple;
    tuple->values = NULL;
    tuple->size = 0;
    list->count++;
    return 1;
}

size_t remove_all_none_tuples(TupleList *list) {
    if (!list || !list->items) return 0;
    if (list->count > list->capacity) {
        list->count = list->capacity;
    }
    size_t write = 0;
    for (size_t read = 0; read < list->count; ++read) {
        Tuple *tuple = &list->items[read];
        int all_none = 1;
        if (tuple->values == NULL) {
            all_none = 1;
        } else {
            for (size_t i = 0; i < tuple->size; ++i) {
                if (tuple->values[i] != NULL) {
                    all_none = 0;
                    break;
                }
            }
        }
        if (all_none) {
            tuple_destroy(tuple);
        } else {
            if (write != read) {
                list->items[write] = *tuple;
                tuple->values = NULL;
                tuple->size = 0;
            }
            ++write;
        }
    }
    list->count = write;
    return write;
}

int main(void) {
    TupleList list;
    if (!tuple_list_init(&list, 0)) {
        return 1;
    }

    Tuple t0;
    void *v0[] = { NULL, NULL };
    if (!tuple_init(&t0, 2, v0)) {
        tuple_list_destroy(&list);
        return 1;
    }
    if (!tuple_list_add(&list, &t0)) {
        tuple_destroy(&t0);
        tuple_list_destroy(&list);
        return 1;
    }

    Tuple t1;
    void *v1[] = { (void *)"a", NULL };
    if (!tuple_init(&t1, 2, v1)) {
        tuple_list_destroy(&list);
        return 1;
    }
    if (!tuple_list_add(&list, &t1)) {
        tuple_destroy(&t1);
        tuple_list_destroy(&list);
        return 1;
    }

    Tuple t2;
    void *v2[] = { NULL, NULL };
    if (!tuple_init(&t2, 2, v2)) {
        tuple_list_destroy(&list);
        return 1;
    }
    if (!tuple_list_add(&list, &t2)) {
        tuple_destroy(&t2);
        tuple_list_destroy(&list);
        return 1;
    }

    Tuple t3;
    void *v3[] = { (void *)"b", (void *)"c" };
    if (!tuple_init(&t3, 2, v3)) {
        tuple_list_destroy(&list);
        return 1;
    }
    if (!tuple_list_add(&list, &t3)) {
        tuple_destroy(&t3);
        tuple_list_destroy(&list);
        return 1;
    }

    size_t new_count = remove_all_none_tuples(&list);

    for (size_t i = 0; i < new_count; ++i) {
        printf("(");
        for (size_t j = 0; j < list.items[i].size; ++j) {
            if (list.items[i].values[j] != NULL) {
                printf("%s", (char *)list.items[i].values[j]);
            } else {
                printf("NULL");
            }
            if (j + 1 < list.items[i].size) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    tuple_list_destroy(&list);
    return 0;
}