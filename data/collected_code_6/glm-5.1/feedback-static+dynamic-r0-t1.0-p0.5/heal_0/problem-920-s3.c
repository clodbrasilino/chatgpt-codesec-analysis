#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int val1;
    int val2;
    int val3;
    int is_none1;
    int is_none2;
    int is_none3;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleList;

TupleList tuple_list_create(size_t capacity) {
    TupleList list;
    list.data = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (list.data == NULL) {
        exit(EXIT_FAILURE);
    }
    list.size = 0;
    list.capacity = capacity;
    return list;
}

void tuple_list_push(TupleList *list, Tuple t) {
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 1 : list->capacity * 2;
        Tuple *new_data = (Tuple *)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            free(list->data);
            exit(EXIT_FAILURE);
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size++] = t;
}

void tuple_list_destroy(TupleList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

TupleList remove_all_none_tuples(TupleList *list) {
    TupleList result = tuple_list_create(list->size > 0 ? list->size : 1);
    for (size_t i = 0; i < list->size; i++) {
        if (!(list->data[i].is_none1 && list->data[i].is_none2 && list->data[i].is_none3)) {
            tuple_list_push(&result, list->data[i]);
        }
    }
    return result;
}

int main(void) {
    TupleList list = tuple_list_create(4);

    Tuple t1 = {1, 2, 3, 0, 0, 0};
    Tuple t2 = {0, 0, 0, 1, 1, 1};
    Tuple t3 = {4, 0, 5, 0, 1, 0};
    Tuple t4 = {0, 0, 0, 1, 1, 1};

    tuple_list_push(&list, t1);
    tuple_list_push(&list, t2);
    tuple_list_push(&list, t3);
    tuple_list_push(&list, t4);

    TupleList filtered = remove_all_none_tuples(&list);

    for (size_t i = 0; i < filtered.size; i++) {
        printf("Tuple %zu: val1=%d, val2=%d, val3=%d\n", i, filtered.data[i].val1, filtered.data[i].val2, filtered.data[i].val3);
    }

    tuple_list_destroy(&list);
    tuple_list_destroy(&filtered);

    return 0;
}