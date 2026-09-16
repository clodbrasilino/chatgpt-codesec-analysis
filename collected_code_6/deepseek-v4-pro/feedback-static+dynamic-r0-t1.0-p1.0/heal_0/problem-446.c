#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} List;

typedef struct {
    int *data;
    int size;
} Tuple;

void list_init(List *list) {
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

void list_push_back(List *list, int value) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity == 0 ? 1 : list->capacity * 2;
        int *new_data = (int *)realloc(list->data, list->capacity * sizeof(int));
        if (new_data == NULL) {
            free(list->data);
            list->data = NULL;
            list->size = 0;
            list->capacity = 0;
            return;
        }
        list->data = new_data;
    }
    list->data[list->size++] = value;
}

void tuple_init(Tuple *tuple) {
    tuple->data = NULL;
    tuple->size = 0;
}

void tuple_set_data(Tuple *tuple, int *data, int size) {
    tuple->data = data;
    tuple->size = size;
}

int count_occurrences(Tuple *tuple, List *list, int *counts) {
    if (tuple == NULL || list == NULL || counts == NULL) {
        return -1;
    }
    if (list->size <= 0) {
        return 0;
    }
    if (tuple->size <= 0) {
        for (int i = 0; i < list->size; i++) {
            counts[i] = 0;
        }
        return 0;
    }

    for (int i = 0; i < list->size; i++) {
        counts[i] = 0;
        for (int j = 0; j < tuple->size; j++) {
            if (tuple->data[j] == list->data[i]) {
                counts[i]++;
            }
        }
    }

    return 0;
}

int main(void) {
    List list;
    Tuple tuple;
    int tuple_data[] = {1, 2, 2, 3, 3, 3, 4};
    int *counts = NULL;

    list_init(&list);
    tuple_init(&tuple);

    list_push_back(&list, 1);
    list_push_back(&list, 2);
    list_push_back(&list, 3);
    list_push_back(&list, 5);

    tuple_set_data(&tuple, tuple_data, sizeof(tuple_data) / sizeof(tuple_data[0]));

    if (list.data == NULL && list.size > 0) {
        printf("Memory allocation failed\n");
        return 1;
    }

    counts = (int *)malloc(list.size * sizeof(int));
    if (counts == NULL) {
        free(list.data);
        return 1;
    }

    if (count_occurrences(&tuple, &list, counts) != 0) {
        free(counts);
        free(list.data);
        return 1;
    }

    for (int i = 0; i < list.size; i++) {
        printf("%d occurs %d time(s)\n", list.data[i], counts[i]);
    }

    free(counts);
    free(list.data);
    return 0;
}