#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} List;

int list_init(List *list, size_t initial_capacity) {
    if (list == NULL) {
        return -1;
    }
    if (initial_capacity == 0) {
        initial_capacity = 4;
    }
    if (initial_capacity > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }
    list->data = (Tuple *)malloc(initial_capacity * sizeof(Tuple));
    if (list->data == NULL) {
        return -1;
    }
    list->size = 0;
    list->capacity = initial_capacity;
    return 0;
}

int list_add(List *list, Tuple tuple) {
    if (list == NULL || list->data == NULL) {
        return -1;
    }
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        if (new_capacity < list->capacity) {
            return -1;
        }
        if (new_capacity > SIZE_MAX / sizeof(Tuple)) {
            return -1;
        }
        Tuple *new_data = (Tuple *)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return -1;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size] = tuple;
    list->size++;
    return 0;
}

void list_free(List *list) {
    if (list == NULL) {
        return;
    }
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int main(void) {
    List list;
    if (list_init(&list, 2) != 0) {
        fprintf(stderr, "Failed to initialize list\n");
        return 1;
    }

    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};
    Tuple t4 = {7, 8};
    Tuple t5 = {9, 10};

    if (list_add(&list, t1) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        list_free(&list);
        return 1;
    }
    if (list_add(&list, t2) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        list_free(&list);
        return 1;
    }
    if (list_add(&list, t3) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        list_free(&list);
        return 1;
    }
    if (list_add(&list, t4) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        list_free(&list);
        return 1;
    }
    if (list_add(&list, t5) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        list_free(&list);
        return 1;
    }

    for (size_t i = 0; i < list.size; i++) {
        printf("(%d, %d)\n", list.data[i].first, list.data[i].second);
    }

    list_free(&list);
    return 0;
}