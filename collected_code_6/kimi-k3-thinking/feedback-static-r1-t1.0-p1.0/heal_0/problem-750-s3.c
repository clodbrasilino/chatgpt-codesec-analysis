#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleList;

int init_list(TupleList *list, size_t capacity)
{
    if (list == NULL || capacity == 0 || capacity > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }
    list->data = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (list->data == NULL) {
        list->size = 0;
        list->capacity = 0;
        return -1;
    }
    list->size = 0;
    list->capacity = capacity;
    return 0;
}

int add_tuple(TupleList *list, Tuple t)
{
    if (list == NULL || list->data == NULL) {
        return -1;
    }
    if (list->size >= list->capacity) {
        size_t new_capacity;
        Tuple *new_data;

        if (list->capacity > SIZE_MAX / 2) {
            return -1;
        }
        new_capacity = list->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(Tuple)) {
            return -1;
        }
        new_data = (Tuple *)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return -1;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size] = t;
    list->size++;
    return 0;
}

void free_list(TupleList *list)
{
    if (list == NULL) {
        return;
    }
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int main(void)
{
    TupleList list;
    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};
    Tuple t4 = {7, 8};
    size_t i;

    if (init_list(&list, 2) != 0) {
        fprintf(stderr, "Error: failed to initialize list\n");
        return EXIT_FAILURE;
    }

    if (add_tuple(&list, t1) != 0 ||
        add_tuple(&list, t2) != 0 ||
        add_tuple(&list, t3) != 0 ||
        add_tuple(&list, t4) != 0) {
        fprintf(stderr, "Error: failed to add tuple\n");
        free_list(&list);
        return EXIT_FAILURE;
    }

    for (i = 0; i < list.size; i++) {
        printf("(%d, %d)\n", list.data[i].first, list.data[i].second);
    }

    free_list(&list);
    return EXIT_SUCCESS;
}