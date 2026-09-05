#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Sublist;

typedef struct {
    Sublist *items;
    int count;
    int capacity;
} SublistArray;

int add_sublist(SublistArray *arr, int *list, int start, int end) {
    if (arr->count >= arr->capacity) {
        int new_capacity = arr->capacity == 0 ? 1 : arr->capacity * 2;
        Sublist *new_items = (Sublist *)realloc(arr->items, new_capacity * sizeof(Sublist));
        if (new_items == NULL) {
            return 0;
        }
        arr->items = new_items;
        arr->capacity = new_capacity;
    }
    int size = end - start + 1;
    int *data = (int *)malloc(size * sizeof(int));
    if (data == NULL) {
        return 0;
    }
    for (int i = 0; i < size; i++) {
        data[i] = list[start + i];
    }
    arr->items[arr->count].data = data;
    arr->items[arr->count].size = size;
    arr->count++;
    return 1;
}

void free_sublists(SublistArray *arr) {
    if (arr != NULL && arr->items != NULL) {
        for (int i = 0; i < arr->count; i++) {
            free(arr->items[i].data);
        }
        free(arr->items);
        arr->items = NULL;
        arr->count = 0;
        arr->capacity = 0;
    }
}

int generate_sublists(int *list, int size, SublistArray *result) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (!add_sublist(result, list, i, j)) {
                free_sublists(result);
                return 0;
            }
        }
    }
    return 1;
}

void print_sublists(SublistArray *arr) {
    for (int i = 0; i < arr->count; i++) {
        printf("[");
        for (int j = 0; j < arr->items[i].size; j++) {
            printf("%d", arr->items[i].data[j]);
            if (j < arr->items[i].size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void) {
    int list[] = {1, 2, 3};
    int size = sizeof(list) / sizeof(list[0]);
    SublistArray result = {NULL, 0, 0};
    
    if (!generate_sublists(list, size, &result)) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    print_sublists(&result);
    free_sublists(&result);
    
    return 0;
}