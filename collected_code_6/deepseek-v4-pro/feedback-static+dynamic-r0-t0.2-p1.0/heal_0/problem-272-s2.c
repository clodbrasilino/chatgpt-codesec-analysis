#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    void **elements;
    size_t size;
} Tuple;

typedef struct TupleList {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

TupleList *create_tuple_list(size_t initial_capacity) {
    TupleList *list = (TupleList *)malloc(sizeof(TupleList));
    if (list == NULL) {
        return NULL;
    }
    
    list->tuples = (Tuple *)malloc(initial_capacity * sizeof(Tuple));
    if (list->tuples == NULL) {
        free(list);
        return NULL;
    }
    
    list->count = 0;
    list->capacity = initial_capacity;
    return list;
}

int add_tuple(TupleList *list, void **elements, size_t size) {
    if (list == NULL || elements == NULL || size == 0) {
        return -1;
    }
    
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Tuple *new_tuples = (Tuple *)realloc(list->tuples, new_capacity * sizeof(Tuple));
        if (new_tuples == NULL) {
            return -1;
        }
        list->tuples = new_tuples;
        list->capacity = new_capacity;
    }
    
    list->tuples[list->count].elements = (void **)malloc(size * sizeof(void *));
    if (list->tuples[list->count].elements == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < size; i++) {
        list->tuples[list->count].elements[i] = elements[i];
    }
    
    list->tuples[list->count].size = size;
    list->count++;
    return 0;
}

void *extract_rear_element(TupleList *list, size_t tuple_index) {
    if (list == NULL || tuple_index >= list->count) {
        return NULL;
    }
    
    Tuple *tuple = &list->tuples[tuple_index];
    if (tuple->size == 0 || tuple->elements == NULL) {
        return NULL;
    }
    
    return tuple->elements[tuple->size - 1];
}

void destroy_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    
    for (size_t i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
    }
    
    free(list->tuples);
    free(list);
}

int main(void) {
    TupleList *list = create_tuple_list(4);
    if (list == NULL) {
        return 1;
    }
    
    int a = 10, b = 20, c = 30;
    void *tuple1[] = {&a, &b, &c};
    add_tuple(list, tuple1, 3);
    
    int d = 40, e = 50;
    void *tuple2[] = {&d, &e};
    add_tuple(list, tuple2, 2);
    
    int f = 60;
    void *tuple3[] = {&f};
    add_tuple(list, tuple3, 1);
    
    int *rear1 = (int *)extract_rear_element(list, 0);
    int *rear2 = (int *)extract_rear_element(list, 1);
    int *rear3 = (int *)extract_rear_element(list, 2);
    
    if (rear1 != NULL) {
        printf("%d\n", *rear1);
    }
    if (rear2 != NULL) {
        printf("%d\n", *rear2);
    }
    if (rear3 != NULL) {
        printf("%d\n", *rear3);
    }
    
    destroy_tuple_list(list);
    return 0;
}