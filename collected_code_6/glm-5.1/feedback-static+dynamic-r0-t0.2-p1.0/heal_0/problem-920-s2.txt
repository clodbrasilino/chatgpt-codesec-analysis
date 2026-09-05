#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val1;
    int val2;
    int val3;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleList;

TupleList tuple_list_create(size_t initial_capacity) {
    TupleList list;
    list.data = (Tuple *)malloc(initial_capacity * sizeof(Tuple));
    if (list.data == NULL) {
        exit(EXIT_FAILURE);
    }
    list.size = 0;
    list.capacity = initial_capacity;
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

TupleList remove_all_none_tuples(TupleList *list) {
    TupleList result = tuple_list_create(list->size > 0 ? list->size : 1);
    for (size_t i = 0; i < list->size; ++i) {
        if (list->data[i].val1 != 0 || list->data[i].val2 != 0 || list->data[i].val3 != 0) {
            tuple_list_push(&result, list->data[i]);
        }
    }
    return result;
}

void tuple_list_free(TupleList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int main(void) {
    TupleList list = tuple_list_create(4);
    
    tuple_list_push(&list, (Tuple){0, 0, 0});
    tuple_list_push(&list, (Tuple){1, 0, 0});
    tuple_list_push(&list, (Tuple){0, 2, 0});
    tuple_list_push(&list, (Tuple){0, 0, 0});
    tuple_list_push(&list, (Tuple){3, 4, 5});
    tuple_list_push(&list, (Tuple){0, 0, 0});

    TupleList filtered = remove_all_none_tuples(&list);

    for (size_t i = 0; i < filtered.size; ++i) {
        printf("(%d, %d, %d)\n", filtered.data[i].val1, filtered.data[i].val2, filtered.data[i].val3);
    }

    tuple_list_free(&list);
    tuple_list_free(&filtered);

    return 0;
}