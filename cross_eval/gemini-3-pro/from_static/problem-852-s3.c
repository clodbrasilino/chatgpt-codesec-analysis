#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntList;

IntList* create_list(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    IntList *list = (IntList*)malloc(sizeof(IntList));
    if (!list) {
        return NULL;
    }
    list->data = (int*)malloc(capacity * sizeof(int));
    if (!list->data) {
        free(list);
        return NULL;
    }
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void free_list(IntList *list) {
    if (list) {
        free(list->data);
        free(list);
    }
}

int add_to_list(IntList *list, int value) {
    if (!list) {
        return -1;
    }
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        int *new_data = (int*)realloc(list->data, new_capacity * sizeof(int));
        if (!new_data) {
            return -1;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size++] = value;
    return 0;
}

void remove_negatives(IntList *list) {
    if (!list || !list->data) {
        return;
    }
    size_t write_idx = 0;
    for (size_t read_idx = 0; read_idx < list->size; ++read_idx) {
        if (list->data[read_idx] >= 0) {
            list->data[write_idx++] = list->data[read_idx];
        }
    }
    list->size = write_idx;
}

void print_list(const IntList *list) {
    if (!list) {
        return;
    }
    for (size_t i = 0; i < list->size; ++i) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int main(void) {
    IntList *list = create_list(10);
    if (!list) {
        return 1;
    }

    int initial_values[] = {5, -3, 8, -1, 0, 12, -7, 4};
    size_t num_values = sizeof(initial_values) / sizeof(initial_values[0]);

    for (size_t i = 0; i < num_values; ++i) {
        if (add_to_list(list, initial_values[i]) != 0) {
            free_list(list);
            return 1;
        }
    }

    remove_negatives(list);
    print_list(list);
    free_list(list);

    return 0;
}