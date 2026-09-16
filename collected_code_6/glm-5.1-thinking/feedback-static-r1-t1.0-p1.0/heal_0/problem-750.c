#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    size_t count;
    size_t capacity;
} TupleList;

int tuple_list_init(TupleList *list, size_t initial_capacity) {
    if (list == NULL) {
        return -1;
    }
    if (initial_capacity == 0) {
        initial_capacity = 4;
    }
    list->data = (Tuple *)malloc(initial_capacity * sizeof(Tuple));
    if (list->data == NULL) {
        return -1;
    }
    list->count = 0;
    list->capacity = initial_capacity;
    return 0;
}

int tuple_list_add(TupleList *list, Tuple tuple) {
    if (list == NULL || list->data == NULL) {
        return -1;
    }
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        if (new_capacity < list->capacity) {
            return -1;
        }
        Tuple *new_data = (Tuple *)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return -1;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->count] = tuple;
    list->count++;
    return 0;
}

void tuple_list_free(TupleList *list) {
    if (list == NULL) {
        return;
    }
    free(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

int main(void) {
    TupleList list;
    if (tuple_list_init(&list, 2) != 0) {
        fprintf(stderr, "Failed to initialize list\n");
        return 1;
    }

    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};

    if (tuple_list_add(&list, t1) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        tuple_list_free(&list);
        return 1;
    }
    if (tuple_list_add(&list, t2) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        tuple_list_free(&list);
        return 1;
    }
    if (tuple_list_add(&list, t3) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        tuple_list_free(&list);
        return 1;
    }

    for (size_t i = 0; i < list.count; i++) {
        printf("(%d, %d)\n", list.data[i].first, list.data[i].second);
    }

    tuple_list_free(&list);
    return 0;
}